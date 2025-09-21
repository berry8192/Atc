#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <tuple>
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

// 8方向の移動 (上, 下, 左, 右, 斜め4方向)
int dr8[] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dc8[] = {0, 0, -1, 1, -1, 1, -1, 1};

// 視界制限のためのトレント配置判定距離
const int VISION_LIMIT_DISTANCE = 2;

// 渦巻きの最大ステップ数
const int MAX_SPIRAL_STEPS = 30;

// 渦巻き試行回数
const int SPIRAL_TRIALS = 1000;

// 評価値の重み
const int PATH_LENGTH_WEIGHT = 2;
const int UNREACHABLE_PENALTY = 1;
const int DISTANCE_TO_FLOWER_WEIGHT = 5;

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

// 8近傍隣接チェック用DSU
class WallDSU {
  public:
    vector<int> parent, size;
    int boundary_node; // 外周木用の超頂点

    WallDSU(int n) : parent(n + 1), size(n + 1, 1) {
        for (int i = 0; i <= n; i++)
            parent[i] = i;
        boundary_node = n; // 最後のノードを外周用に使用
    }

    int leader(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = leader(parent[x]);
    }

    bool same(int x, int y) { return leader(x) == leader(y); }

    void merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y)
            return;
        if (size[x] < size[y])
            swap(x, y);
        parent[y] = x;
        size[x] += size[y];
    }

    bool is_connected_to_boundary(int x) { return same(x, boundary_node); }
};

// 座標を1次元のインデックスに変換
int coord_to_index(int r, int c) { return r * N + c; }
// 座標を1次元のインデックスに変換（8近傍DSU用）
int coord_to_wall_index(int r, int c) { return r * N + c; }

// 外周かどうかチェック
bool is_boundary(int r, int c) {
    return r == 0 || r == N - 1 || c == 0 || c == N - 1;
}

// 8近傍で隣接するかチェック
bool is_adjacent_8(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) <= 1 && abs(c1 - c2) <= 1 && !(r1 == r2 && c1 == c2);
}

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

// 到達不能地点の数を計算する
int count_unreachable_cells(const vector<string> &maze, int start_r,
                            int start_c) {
    vector<vector<bool>> reachable(N, vector<bool>(N, false));
    queue<pair<int, int>> q;

    if (maze[start_r][start_c] != '.')
        return N * N; // スタート地点が無効

    reachable[start_r][start_c] = true;
    q.push({start_r, start_c});

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        int r = curr.first;
        int c = curr.second;

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < N && !reachable[nr][nc] &&
                maze[nr][nc] == '.') {
                reachable[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }

    int unreachable_count = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (maze[i][j] == '.' && !reachable[i][j]) {
                unreachable_count++;
            }
        }
    }

    return unreachable_count;
}

// 経路中のマスの花からのマンハッタン距離の平均を計算する
double calculate_average_distance_to_flower(int pi, int pj,
                                            const vector<string> &maze) {
    vector<vector<int>> dist(N, vector<int>(N, -1));
    queue<pair<int, int>> q;
    vector<pair<int, int>> path;

    if (maze[pi][pj] == 'T' || maze[pi][pj] == 't')
        return 1e9; // 到達不能

    dist[pi][pj] = 0;
    q.push({pi, pj});

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        int r = curr.first;
        int c = curr.second;

        if (r == ti && c == tj) {
            // 経路を逆算して構築
            int cr = ti, cc = tj;
            while (!(cr == pi && cc == pj)) {
                path.push_back({cr, cc});
                // 隣接するマスの中で距離が1少ないマスを探す
                for (int i = 0; i < 4; i++) {
                    int nr = cr + dr[i];
                    int nc = cc + dc[i];
                    if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                        dist[nr][nc] == dist[cr][cc] - 1) {
                        cr = nr;
                        cc = nc;
                        break;
                    }
                }
            }
            path.push_back({pi, pj});
            break;
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

    if (path.empty())
        return 1e9; // 到達不能

    // 経路中の各マスの花からのマンハッタン距離を計算
    double total_distance = 0.0;
    for (const auto &pos : path) {
        int manhattan_dist = abs(pos.first - ti) + abs(pos.second - tj);
        total_distance += manhattan_dist;
    }

    return total_distance / path.size();
}

// 方向を左回り/右回りに回転させる
int rotate_direction(int dir, int rotation) {
    // rotation: 0=左回り, 1=右回り
    if (rotation == 0) {      // 左回り
        return (dir + 3) % 4; // -1を+3で代用
    } else {                  // 右回り
        return (dir + 1) % 4;
    }
}

// トレント引き寄せ渦巻きアルゴリズム（1回の試行）
vector<pair<int, int>> create_single_spiral_trial(int pi, int pj, int open_dir,
                                                  mt19937 &gen) {
    vector<pair<int, int>> treants_to_place;
    vector<string> original_maze = current_maze;

    // 冒険者の初期位置（森の入口）
    int adventurer_start_r = 0;
    int adventurer_start_c = N / 2;

    // 設置済みトレントのリスト（優先度付き：早く設置したほど高優先度）
    vector<pair<pair<int, int>, int>> placed_treants; // ((r, c), priority)

    // 花の周りの3方向を最初に塞ぐ（最高優先度）
    for (int i = 0; i < 4; ++i) {
        if (i == open_dir)
            continue;
        int nr = ti + dr[i];
        int nc = tj + dc[i];
        if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
            original_maze[nr][nc] == '.' &&
            !(nr == adventurer_start_r && nc == adventurer_start_c)) {
            current_maze[nr][nc] = 't';
            treants_to_place.push_back({nr, nc});
            placed_treants.push_back({{nr, nc}, 100}); // 最高優先度
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

    // トレント引き寄せ経路構築（最大30ステップ）
    for (int step = 0; step < MAX_SPIRAL_STEPS; ++step) {
        vector<pair<int, int>> candidates;

        // 候補となる次の位置を収集
        for (int j = 0; j < 4; ++j) {
            int nr = current_r + dr[j];
            int nc = current_c + dc[j];

            if (nr == prev_r && nc == prev_c)
                continue; // 戻る経路は考慮しない

            if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                current_maze[nr][nc] == '.') {
                candidates.push_back({nr, nc});
            }
        }

        if (candidates.empty())
            break; // 次に進むマスがない

        // 最高優先度のトレントとのユークリッド距離が最も近い候補を選択
        vector<int> best_candidates;
        double min_distance_sq = 1e9;

        for (int i = 0; i < candidates.size(); ++i) {
            int nr = candidates[i].first;
            int nc = candidates[i].second;

            // 最高優先度のトレント（優先度100）との距離の二乗を計算
            double min_dist_sq_to_high_priority = 1e9;
            for (const auto &treant_info : placed_treants) {
                if (treant_info.second == 100) { // 最高優先度のみ
                    int tr = treant_info.first.first;
                    int tc = treant_info.first.second;
                    double dist_sq = pow(nr - tr, 2) + pow(nc - tc, 2);
                    min_dist_sq_to_high_priority =
                        min(min_dist_sq_to_high_priority, dist_sq);
                }
            }

            if (min_dist_sq_to_high_priority < min_distance_sq) {
                min_distance_sq = min_dist_sq_to_high_priority;
                best_candidates.clear();
                best_candidates.push_back(i);
            } else if (abs(min_dist_sq_to_high_priority - min_distance_sq) <
                       1e-9) {
                best_candidates.push_back(i);
            }
        }

        // 同じ距離の候補が複数ある場合はランダム選択
        uniform_int_distribution<> candidate_dist(0,
                                                  best_candidates.size() - 1);
        int selected_idx = candidate_dist(gen);
        int best_candidate = best_candidates[selected_idx];

        int next_r = candidates[best_candidate].first;
        int next_c = candidates[best_candidate].second;

        // 前の現在地から見た4近傍のうち、経路以外のマスにトレントを配置
        for (int j = 0; j < 4; ++j) {
            int tr = prev_r + dr[j];
            int tc = prev_c + dc[j];
            if (tr >= 0 && tr < N && tc >= 0 && tc < N &&
                current_maze[tr][tc] == '.' &&
                (tr != current_r || tc != current_c) &&
                (tr != next_r || tc != next_c) &&
                !(tr == adventurer_start_r && tc == adventurer_start_c)) {

                current_maze[tr][tc] = 't';
                if (calculate_path_length(pi, pj, ti, tj, current_maze) != -1) {
                    treants_to_place.push_back({tr, tc});
                    // 新しく設置したトレントを記録（優先度は段階的に下げる）
                    int new_priority = max(10, 100 - step * 5);
                    placed_treants.push_back({{tr, tc}, new_priority});
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

// 新しい確率的渦巻きアルゴリズム
vector<pair<int, int>> create_strategic_treants(int pi, int pj, int open_dir,
                                                int rotation_dir) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> open_dir_dist(0, 3);

    vector<pair<int, int>> best_treants;
    int best_score = -1e9;

    for (int trial = 0; trial < SPIRAL_TRIALS; ++trial) {
        // ランダムに開放方向を選択
        int random_open_dir = open_dir_dist(gen);

        vector<pair<int, int>> treants =
            create_single_spiral_trial(pi, pj, random_open_dir, gen);

        if (treants.empty())
            continue;

        // 評価値計算のための仮迷路構築
        vector<string> temp_maze = current_maze;
        for (const auto &p : treants) {
            temp_maze[p.first][p.second] = 't';
        }

        int path_length = calculate_path_length(pi, pj, ti, tj, temp_maze);
        if (path_length == -1)
            continue; // 到達不能な場合はスキップ

        int unreachable_count = count_unreachable_cells(temp_maze, 0, N / 2);
        double avg_distance_to_flower =
            calculate_average_distance_to_flower(pi, pj, temp_maze);

        // 評価値計算: 経路長*2 - 到達不能*1 + 花からの平均距離*2
        int score = path_length * PATH_LENGTH_WEIGHT -
                    unreachable_count * UNREACHABLE_PENALTY +
                    (int)(avg_distance_to_flower * DISTANCE_TO_FLOWER_WEIGHT);

        if (score > best_score) {
            best_score = score;
            best_treants = treants;
        }
    }

    return best_treants;
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

// 視界制限のための追加トレント配置
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

        // 上下左右のどの方向にも指定距離以内に木やトレントがない場合のみ
        if (!has_tree_within_4_squares_in_any_direction(i, j, temp_maze)) {
            // トレント配置を試す
            temp_maze[i][j] = 't';

            // 連結性をチェック（DSUを使用）
            if (check_connectivity(temp_maze) &&
                calculate_path_length(pi, pj, ti, tj, temp_maze) != -1) {
                additional_treants.push_back({i, j});
            } else {
                temp_maze[i][j] =
                    '.'; // 連結性が失われるか経路が途絶えるので元に戻す
            }
        }
    }

    return additional_treants;
}

// 8近傍隣接DSUを初期化
WallDSU initialize_wall_dsu(const vector<string> &maze,
                            const vector<pair<int, int>> &existing_treants) {
    WallDSU wall_dsu(N * N);
    vector<string> temp_maze = maze;

    // 既存トレントを仮配置
    for (const auto &p : existing_treants) {
        temp_maze[p.first][p.second] = 't';
    }

    // 外周の木を超頂点に接続
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (is_boundary(i, j) &&
                (temp_maze[i][j] == 'T' || temp_maze[i][j] == 't')) {
                wall_dsu.merge(coord_to_wall_index(i, j),
                               wall_dsu.boundary_node);
            }
        }
    }

    // 8近傍で隣接する木/トレント同士を接続
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (temp_maze[i][j] == 'T' || temp_maze[i][j] == 't') {
                for (int d = 0; d < 8; ++d) {
                    int ni = i + dr8[d];
                    int nj = j + dc8[d];
                    if (ni >= 0 && ni < N && nj >= 0 && nj < N &&
                        (temp_maze[ni][nj] == 'T' ||
                         temp_maze[ni][nj] == 't')) {
                        wall_dsu.merge(coord_to_wall_index(i, j),
                                       coord_to_wall_index(ni, nj));
                    }
                }
            }
        }
    }

    return wall_dsu;
}

// 8近傍で既存のトレントに隣接しているかチェック
bool is_adjacent_to_existing_treant(int r, int c, const vector<string> &maze) {
    for (int d = 0; d < 8; ++d) {
        int nr = r + dr8[d];
        int nc = c + dc8[d];
        if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
            (maze[nr][nc] == 'T' || maze[nr][nc] == 't')) {
            return true;
        }
    }
    return false;
}

// 到達不能エリアの増加をチェック
bool increases_unreachable_area(int r, int c, const vector<string> &maze) {
    int adventurer_start_r = 0;
    int adventurer_start_c = N / 2;

    // 配置前の到達不能エリア数
    int before_unreachable =
        count_unreachable_cells(maze, adventurer_start_r, adventurer_start_c);

    // 配置後の到達不能エリア数
    vector<string> temp_maze = maze;
    temp_maze[r][c] = 't';
    int after_unreachable = count_unreachable_cells(
        temp_maze, adventurer_start_r, adventurer_start_c);

    return after_unreachable > before_unreachable;
}

// 通路確保処理
void add_corridor_cells(int treant_r, int treant_c,
                        vector<pair<int, int>> &corridor_cells,
                        const vector<string> &temp_maze) {
    // 右、右下、下の方向に通路を確保
    vector<pair<int, int>> corridor_offsets = {
        {0, 1}, // 右
        {1, 1}, // 右下
        {1, 0}  // 下
    };

    for (const auto &offset : corridor_offsets) {
        int corridor_r = treant_r + offset.first;
        int corridor_c = treant_c + offset.second;
        if (corridor_r > 0 && corridor_r < N - 1 && corridor_c > 0 &&
            corridor_c < N - 1 && temp_maze[corridor_r][corridor_c] == '.') {

            // 既に通路リストに含まれていない場合のみ追加
            bool already_exists = false;
            for (const auto &existing : corridor_cells) {
                if (existing.first == corridor_r &&
                    existing.second == corridor_c) {
                    already_exists = true;
                    break;
                }
            }
            if (!already_exists) {
                corridor_cells.push_back({corridor_r, corridor_c});
            }
        }
    }
}

// トレント設置処理（未実装）
bool place_treant_next_to_corridor(const vector<pair<int, int>> &corridor_cells,
                                   vector<string> &temp_maze,
                                   vector<pair<int, int>> &additional_treants,
                                   WallDSU &wall_dsu, int pi, int pj) {
    // TODO: 実装予定
    // 通路リストを右上から順にソートし、各通路の右にトレント設置を試行
    return false;
}

// 斜め通路を確保するための追加トレント配置
vector<pair<int, int>> place_diagonal_corridor_treants(
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

    // 8近傍隣接DSUを初期化
    WallDSU wall_dsu = initialize_wall_dsu(current_maze, existing_treants);

    // 通路として確保するマスのリスト
    vector<pair<int, int>> corridor_cells;

    // ステップ1: (1,1)にトレント設置（1回目のトレント設置処理）
    int start_r = 1, start_c = 1;
    if (start_r < N - 1 && start_c < N - 1 &&
        temp_maze[start_r][start_c] == '.' &&
        !(start_r == adventurer_start_r && start_c == adventurer_start_c)) {

        // 外周との8近傍隣接チェック
        bool adjacent_to_boundary = false;
        for (int d = 0; d < 8; ++d) {
            int nr = start_r + dr8[d];
            int nc = start_c + dc8[d];
            if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                (temp_maze[nr][nc] == 'T' || temp_maze[nr][nc] == 't')) {
                if (wall_dsu.is_connected_to_boundary(
                        coord_to_wall_index(nr, nc))) {
                    adjacent_to_boundary = true;
                    break;
                }
            }
        }

        if (!adjacent_to_boundary &&
            !increases_unreachable_area(start_r, start_c, temp_maze)) {
            temp_maze[start_r][start_c] = 't';
            if (calculate_path_length(pi, pj, ti, tj, temp_maze) != -1) {
                additional_treants.push_back({start_r, start_c});

                // DSUに新しいトレントを追加
                int new_idx = coord_to_wall_index(start_r, start_c);
                for (int d = 0; d < 8; ++d) {
                    int nr = start_r + dr8[d];
                    int nc = start_c + dc8[d];
                    if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                        (temp_maze[nr][nc] == 'T' ||
                         temp_maze[nr][nc] == 't')) {
                        wall_dsu.merge(new_idx, coord_to_wall_index(nr, nc));
                    }
                }

                // ステップ2: 通路確保処理
                add_corridor_cells(start_r, start_c, corridor_cells, temp_maze);

                // ステップ3: 以降のトレント設置処理（未実装）
                int max_iterations = N;
                for (int iteration = 0;
                     iteration < max_iterations && !corridor_cells.empty();
                     ++iteration) {
                    bool placed = place_treant_next_to_corridor(
                        corridor_cells, temp_maze, additional_treants, wall_dsu,
                        pi, pj);
                    if (!placed) {
                        break;
                    }
                }

            } else {
                temp_maze[start_r][start_c] =
                    '.'; // 経路が途絶える場合は元に戻す
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

    // 1回だけ確率的渦巻きを実行（内部で1000回試行）
    current_maze = original_maze;
    best_treants = create_strategic_treants(pi, pj, 0, 0);

    // 斜め通路のための追加トレント配置
    vector<pair<int, int>> additional_treants =
        place_diagonal_corridor_treants(pi, pj, best_treants);

    // 最終的なトレント配置
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

    // 打ち切り出力を行ってプログラム終了
    cout << -1 << endl;
    exit(0);
}

int main() {
    cin >> N >> ti >> tj;
    current_maze.resize(N);
    confirmed.assign(N, vector<bool>(N, false));
    for (int i = 0; i < N; ++i) {
        cin >> current_maze[i];
    }

    bool first_turn = true;

    while (true) {
        int pi, pj, n;
        cin >> pi >> pj >> n;

        if (pi == ti && pj == tj) {
            return 0;
        }

        vector<pair<int, int>> newly_confirmed(n);
        for (int k = 0; k < n; ++k) {
            cin >> newly_confirmed[k].first >> newly_confirmed[k].second;
        }

        if (first_turn) {
            solve_first_turn(pi, pj, n, newly_confirmed);
            // この時点で exit(0) されるので、以下のコードは実行されない
            first_turn = false;
        } else {
            // この部分はもう実行されないが、念のため残しておく
            cout << 0 << endl;
        }
    }

    return 0;
}
