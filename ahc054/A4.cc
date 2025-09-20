#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <vector>

using namespace std;

// 迷路のサイズ
int N;
// ゴールの座標
int ti, tj;
// 現在の迷路の状態
vector<string> current_maze;
// 冒険者が確認済みのマス
vector<vector<bool>> confirmed;

// 4方向の移動 (上, 下, 左, 右)
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// 視界制限のためのトレント配置判定距離
const int VISION_LIMIT_DISTANCE = 2;

// DSU (Disjoint Set Union) クラス
class DSU {
  public:
    vector<int> parent, size;

    DSU(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int leader(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = leader(parent[x]);
    }

    bool same(int x, int y) { return leader(x) == leader(y); }

    int merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y)
            return x;
        if (size[x] < size[y])
            swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        return x;
    }

    int get_size(int x) { return size[leader(x)]; }
};

// 座標を1次元のインデックスに変換
int coord_to_index(int r, int c) { return r * N + c; }

// 空きマスの連結性をチェックする関数
bool check_connectivity(const vector<string> &maze) {
    DSU dsu(N * N);

    // 空きマス同士を連結
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (maze[i][j] == '.') {
                for (int d = 0; d < 4; d++) {
                    int ni = i + dr[d];
                    int nj = j + dc[d];
                    if (ni >= 0 && ni < N && nj >= 0 && nj < N &&
                        maze[ni][nj] == '.') {
                        dsu.merge(coord_to_index(i, j), coord_to_index(ni, nj));
                    }
                }
            }
        }
    }

    // 冒険者の初期位置と花の位置が同じ連結成分にあるかチェック
    int adventurer_start_r = 0;
    int adventurer_start_c = N / 2;

    if (maze[adventurer_start_r][adventurer_start_c] != '.' ||
        maze[ti][tj] != '.') {
        return false;
    }

    return dsu.same(coord_to_index(adventurer_start_r, adventurer_start_c),
                    coord_to_index(ti, tj));
}

// 2点間の最短経路長を計算する
int calculate_path_length(int start_r, int start_c, int end_r, int end_c,
                          const vector<string> &maze) {
    vector<vector<int>> dist(N, vector<int>(N, -1));
    queue<pair<int, int>> q;

    if (maze[start_r][start_c] == 'T' || maze[start_r][start_c] == 't')
        return -1;

    dist[start_r][start_c] = 0;
    q.push({start_r, start_c});

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        int r = curr.first;
        int c = curr.second;

        if (r == end_r && c == end_c) {
            return dist[r][c];
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < N && dist[nr][nc] == -1 &&
                maze[nr][nc] != 'T' && maze[nr][nc] != 't') {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    return -1; // 到達不能
}

// チェスのナイトの8方向の移動パターン
int knight_dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int knight_dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

// 指定マスからナイトの位置にトレントがあるかチェック
bool has_knight_pattern_treants(int r, int c, const vector<string> &maze) {
    for (int i = 0; i < 8; ++i) {
        int nr = r + knight_dr[i];
        int nc = c + knight_dc[i];
        if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
            if (maze[nr][nc] == 'T' || maze[nr][nc] == 't') {
                return true; // ナイトの位置にトレントがある
            }
        }
    }
    return false; // ナイトの位置にトレントがない
}

// 新しい渦巻きアルゴリズム（スタート地点から遠ざかる戦略）
vector<pair<int, int>> create_strategic_treants(int pi, int pj, int open_dir,
                                                int rotation_dir) {
    vector<pair<int, int>> treants_to_place;

    // 現在の迷路状態をバックアップ
    vector<string> original_maze = current_maze;

    // 冒険者の初期位置（森の入口）
    int adventurer_start_r = 0;
    int adventurer_start_c = N / 2;

    // 花の周りの3方向を最初に塞ぐ
    for (int i = 0; i < 4; ++i) {
        if (i == open_dir)
            continue;
        int nr = ti + dr[i];
        int nc = tj + dc[i];
        if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
            original_maze[nr][nc] == '.' &&
            !(nr == adventurer_start_r &&
              nc == adventurer_start_c)) { // 冒険者の初期位置を除外
            current_maze[nr][nc] = 't';
            treants_to_place.push_back({nr, nc});
        }
    }

    // 経路探索の現在地と過去の現在地
    int current_r = ti + dr[open_dir];
    int current_c = tj + dc[open_dir];
    int prev_r = ti;
    int prev_c = tj;

    // 経路確保のための仮チェック
    if (current_r < 0 || current_r >= N || current_c < 0 || current_c >= N ||
        current_maze[current_r][current_c] != '.') {
        current_maze = original_maze;
        return {};
    }

    // スタート地点から遠ざかる戦略：スタート地点に到達するまで続ける
    while (true) {
        // スタート地点に到達した場合は終了
        if (current_r == adventurer_start_r &&
            current_c == adventurer_start_c) {
            break;
        }

        int next_r = -1, next_c = -1;
        int max_manhattan_dist = -1;

        // まず、スタート地点からの距離が最も大きくなる移動先を探す
        for (int j = 0; j < 4; ++j) {
            int nr = current_r + dr[j];
            int nc = current_c + dc[j];

            if (nr == prev_r && nc == prev_c)
                continue; // 戻る経路は考慮しない

            if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                current_maze[nr][nc] == '.') {
                // スタート地点からのマンハッタン距離を計算
                int manhattan_dist_from_start =
                    abs(nr - adventurer_start_r) + abs(nc - adventurer_start_c);

                if (manhattan_dist_from_start > max_manhattan_dist) {
                    max_manhattan_dist = manhattan_dist_from_start;
                    next_r = nr;
                    next_c = nc;
                }
            }
        }

        // 距離最大化で候補が見つからない場合、花からより遠い場所を選ぶ
        if (next_r == -1) {
            double max_dist_from_goal = -1;
            for (int j = 0; j < 4; ++j) {
                int nr = current_r + dr[j];
                int nc = current_c + dc[j];

                if (nr == prev_r && nc == prev_c)
                    continue;

                if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                    current_maze[nr][nc] == '.') {
                    double dist_from_goal =
                        sqrt((nr - ti) * (nr - ti) + (nc - tj) * (nc - tj));

                    if (dist_from_goal > max_dist_from_goal) {
                        max_dist_from_goal = dist_from_goal;
                        next_r = nr;
                        next_c = nc;
                    }
                }
            }
        }

        // それでも候補が見つからない場合、任意の空きマスを選ぶ
        if (next_r == -1) {
            for (int j = 0; j < 4; ++j) {
                int nr = current_r + dr[j];
                int nc = current_c + dc[j];

                if (nr == prev_r && nc == prev_c)
                    continue;

                if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                    current_maze[nr][nc] == '.') {
                    next_r = nr;
                    next_c = nc;
                    break;
                }
            }
        }

        // 完全に行き詰まった場合のみ終了
        if (next_r == -1) {
            break;
        }

        // 現在地から見た4近傍のうち、前と次の現在地以外のマスにトレントを配置
        for (int j = 0; j < 4; ++j) {
            int tr = current_r + dr[j];
            int tc = current_c + dc[j];
            if (tr >= 0 && tr < N && tc >= 0 && tc < N &&
                current_maze[tr][tc] == '.' && (tr != prev_r || tc != prev_c) &&
                (tr != next_r || tc != next_c) &&
                !(tr == adventurer_start_r &&
                  tc == adventurer_start_c)) { // 冒険者の初期位置を除外

                current_maze[tr][tc] = 't';
                if (calculate_path_length(pi, pj, ti, tj, current_maze) != -1) {
                    treants_to_place.push_back({tr, tc});
                } else {
                    current_maze[tr][tc] = '.'; // 経路が途絶えるので元に戻す
                }
            }
        }

        // 現在地を更新
        prev_r = current_r;
        prev_c = current_c;
        current_r = next_r;
        current_c = next_c;
    }

    current_maze = original_maze;
    return treants_to_place;
}

// 指定マスから上下左右それぞれの方向に指定距離以内に木（トレントを含む）があるかチェック
bool has_tree_within_4_squares_in_any_direction(int r, int c,
                                                const vector<string> &maze) {
    for (int dir = 0; dir < 4; ++dir) {
        for (int dist = 1; dist <= VISION_LIMIT_DISTANCE; ++dist) {
            int nr = r + dr[dir] * dist;
            int nc = c + dc[dir] * dist;
            if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                if (maze[nr][nc] == 'T' || maze[nr][nc] == 't') {
                    return true; // この方向に木が見つかった
                }
            }
            // 範囲外（マップの端）は木がないものとして扱う
        }
    }
    return false; // 全方向に指定距離以内に木がない
}

// 視界制限のための追加トレント配置（統合版）
vector<pair<int, int>> place_additional_vision_limiting_treants(
    int pi, int pj, const vector<pair<int, int>> &existing_treants) {
    vector<pair<int, int>> additional_treants;
    vector<string> temp_maze = current_maze;

    // 冒険者の初期位置（森の入口）
    int adventurer_start_r = 0;
    int adventurer_start_c = N / 2;

    // 既存のトレントを仮配置
    for (const auto &p : existing_treants) {
        temp_maze[p.first][p.second] = 't';
    }

    // 全ての空きマスを列挙（冒険者の初期位置を除外）
    vector<pair<int, int>> empty_spaces;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (temp_maze[i][j] == '.' &&
                !(i == adventurer_start_r && j == adventurer_start_c)) {
                empty_spaces.push_back({i, j});
            }
        }
    }

    // 空きマスの順番をシャッフル
    random_device rd;
    mt19937 g(rd());
    shuffle(empty_spaces.begin(), empty_spaces.end(), g);

    // シャッフルされた順序で各マスを確認
    for (const auto &pos : empty_spaces) {
        int i = pos.first;
        int j = pos.second;

        // 複数の条件をチェック（OR条件）
        bool should_place = false;

        // 条件1: 上下左右のどの方向にも指定距離以内に木やトレントがない
        if (!has_tree_within_4_squares_in_any_direction(i, j, temp_maze)) {
            should_place = true;
        }

        // 条件2: ナイトの位置にトレントがない
        if (!has_knight_pattern_treants(i, j, temp_maze)) {
            should_place = true;
        }

        if (should_place) {
            // トレント配置を試す
            temp_maze[i][j] = 't';

            // 花への経路のみチェック（連結性チェックは削除）
            if (calculate_path_length(pi, pj, ti, tj, temp_maze) != -1) {
                additional_treants.push_back({i, j});
            } else {
                temp_maze[i][j] = '.'; // 経路が途絶えるので元に戻す
            }
        }
    }

    return additional_treants;
}

// 最初のターンの処理
void solve_first_turn(int pi, int pj, int /* n */,
                      const vector<pair<int, int>> &newly_confirmed) {
    for (const auto &p : newly_confirmed) {
        confirmed[p.first][p.second] = true;
    }

    vector<string> original_maze = current_maze;
    vector<pair<int, int>> best_treants;
    int max_path_length = -1;

    // 8通りの戦略をシミュレート (4方向 x 2回転方向)
    for (int open_dir = 0; open_dir < 4; ++open_dir) {
        // rotation_dirはここでは使わないが、将来的な拡張のために残しておく
        for (int rotation_dir = 0; rotation_dir < 2; ++rotation_dir) {
            current_maze = original_maze;
            vector<pair<int, int>> treants =
                create_strategic_treants(pi, pj, open_dir, rotation_dir);

            // 評価のため、トレントを仮に配置した迷路を構築
            vector<string> temp_maze = original_maze;
            for (const auto &p : treants)
                temp_maze[p.first][p.second] = 't';

            int current_path_length =
                calculate_path_length(pi, pj, ti, tj, temp_maze);

            if (current_path_length > max_path_length) {
                max_path_length = current_path_length;
                best_treants = treants;
            }
        }
    }

    // 視界制限のための追加トレント配置
    vector<pair<int, int>> additional_treants =
        place_additional_vision_limiting_treants(pi, pj, best_treants);

    // 最終的なトレント配置を結合
    vector<pair<int, int>> final_treants = best_treants;
    final_treants.insert(final_treants.end(), additional_treants.begin(),
                         additional_treants.end());

    // 出力
    cout << final_treants.size();
    for (const auto &p : final_treants) {
        cout << " " << p.first << " " << p.second;
        current_maze[p.first][p.second] = 'T'; // 確定
    }
    cout << endl;
}

// 最初のターン以外の処理（何もしない）
void solve_other_turns(int /* pi */, int /* pj */, int /* n */,
                       const vector<pair<int, int>> &newly_confirmed) {
    for (const auto &p : newly_confirmed) {
        confirmed[p.first][p.second] = true;
    }
    cout << 0 << endl;
}

int main() {
    cin >> N >> ti >> tj;
    current_maze.resize(N);
    confirmed.assign(N, vector<bool>(N, false));
    for (int i = 0; i < N; ++i) {
        cin >> current_maze[i];
    }

    bool first_turn = true;
    long long turn_limit = 10LL * N * N;
    long long current_turn = 0;

    while (true) {
        int pi, pj, n;
        cin >> pi >> pj >> n;
        // cerr << pi << " " << pj << " " << n << endl;
        if (pi == ti && pj == tj) {
            return 0;
        }

        vector<pair<int, int>> newly_confirmed(n);
        for (int k = 0; k < n; ++k) {
            cin >> newly_confirmed[k].first >> newly_confirmed[k].second;
        }

        if (first_turn) {
            solve_first_turn(pi, pj, n, newly_confirmed);
            first_turn = false;
        } else {
            solve_other_turns(pi, pj, n, newly_confirmed);
        }

        current_turn++;
        if (current_turn > turn_limit) {
            return 0;
        }
    }

    return 0;
}
