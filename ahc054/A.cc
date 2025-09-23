#include <algorithm>
#include <chrono>
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
const int SPIRAL_TRIALS = 100;

// 評価値の重み
const int PATH_LENGTH_WEIGHT = 2;
const int UNREACHABLE_PENALTY = 1;
const int DISTANCE_TO_FLOWER_WEIGHT = 5;

// 機械的配置モード用の定数
const int MECHANICAL_PLACEMENT_INTERVAL = 3; // デフォルトのトレント配置間隔
const double TREE_DENSITY_THRESHOLD = 0.15;  // 木の密度閾値

// 焼きなまし用の定数
const int ANNEALING_ITERATIONS = 10000;   // 焼きなまし反復回数
const double INITIAL_TEMPERATURE = 100.0; // 初期温度
const double FINAL_TEMPERATURE = 1.0;     // 最終温度

// サイクル履歴を記録する構造体
struct CycleHistory {
    vector<pair<int, int>> treants;   // そのサイクルで配置されたトレント
    vector<pair<int, int>> corridors; // そのサイクルで確保された通路
};

// 時間管理
auto start_time = chrono::high_resolution_clock::now();
const double TIME_LIMIT = 2000.0; // 制限時間（ミリ秒）

// 経過時間を取得
double get_elapsed_time() {
    auto now = chrono::high_resolution_clock::now();
    auto duration =
        chrono::duration_cast<chrono::microseconds>(now - start_time);
    return duration.count() / 1000.0; // ミリ秒単位で返す
}

// 時間制限チェック
bool check_time_limit(double threshold_ratio = 0.95) {
    return get_elapsed_time() >= TIME_LIMIT * threshold_ratio;
}

// デバッグ用：サイクル履歴を表示する関数
void debug_print_cycle_history(const vector<CycleHistory> &cycle_history) {

    for (int i = 0; i < cycle_history.size(); ++i) {

        for (const auto &treant : cycle_history[i].treants) {
        }

        for (const auto &corridor : cycle_history[i].corridors) {
        }
    }
}

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

// 到達不能マスの座標を取得する
set<pair<int, int>> get_unreachable_cells(const vector<string> &maze,
                                          int start_r, int start_c) {
    vector<vector<bool>> reachable(N, vector<bool>(N, false));
    queue<pair<int, int>> q;
    set<pair<int, int>> unreachable;

    if (maze[start_r][start_c] != '.') {
        return unreachable; // スタート地点が無効
    }

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

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (maze[i][j] == '.' && !reachable[i][j]) {
                unreachable.insert({i, j});
            }
        }
    }

    return unreachable;
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

// 木の密度を計算する関数
double calculate_tree_density() {
    int tree_count = 0;
    int total_cells = N * N;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (current_maze[i][j] == 'T') {
                tree_count++;
            }
        }
    }

    double density = (double)tree_count / total_cells;
    return density;
}

// 機械的な固定パターンでトレント配置を行う関数（斜め線状）
vector<pair<int, int>>
place_mechanical_treants(int pi, int pj,
                         const vector<pair<int, int>> &existing_treants,
                         int placement_interval) {
    vector<pair<int, int>> placed_treants;
    vector<string> temp_maze = current_maze;

    // 冒険者の初期位置（森の入口）
    int adventurer_start_r = 0;
    int adventurer_start_c = N / 2;

    // 既存のトレントを迷路に反映
    for (const auto &p : existing_treants) {
        temp_maze[p.first][p.second] = 't';
    }

    // DSUを初期化
    WallDSU wall_dsu = initialize_wall_dsu(current_maze, existing_treants);

    // 斜め線状に配置（左上から右下へ）
    for (int diag = 1; diag < N + N - 2; diag += placement_interval) {
        for (int r = 1; r < N - 1; ++r) {
            int c = diag - r + 1;

            // 範囲チェック
            if (c <= 0 || c >= N - 1)
                continue;

            // 既にトレントが配置されている場合はスキップ
            if (temp_maze[r][c] != '.') {

                continue;
            }

            // 冒険者の初期位置は避ける
            if (r == adventurer_start_r && c == adventurer_start_c) {

                continue;
            }

            // 外周の木との8近傍隣接チェック
            bool adjacent_to_boundary = false;
            for (int d = 0; d < 8; ++d) {
                int nr = r + dr8[d];
                int nc = c + dc8[d];
                if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                    (temp_maze[nr][nc] == 'T' || temp_maze[nr][nc] == 't')) {
                    if (wall_dsu.is_connected_to_boundary(
                            coord_to_wall_index(nr, nc))) {
                        adjacent_to_boundary = true;
                        break;
                    }
                }
            }

            if (adjacent_to_boundary) {

                continue;
            }

            // 到達不能エリア増加チェック
            if (increases_unreachable_area(r, c, temp_maze)) {

                continue;
            }

            // トレント配置を試す
            temp_maze[r][c] = 't';

            // 経路が確保されているかチェック
            if (calculate_path_length(pi, pj, ti, tj, temp_maze) != -1) {
                placed_treants.push_back({r, c});

                // DSUに新しいトレントを追加
                int new_idx = coord_to_wall_index(r, c);
                for (int d = 0; d < 8; ++d) {
                    int nr = r + dr8[d];
                    int nc = c + dc8[d];
                    if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                        (temp_maze[nr][nc] == 'T' ||
                         temp_maze[nr][nc] == 't')) {
                        wall_dsu.merge(new_idx, coord_to_wall_index(nr, nc));
                    }
                }

            } else {
                // 経路が途絶える場合は元に戻す
                temp_maze[r][c] = '.';
            }
        }
    }

    return placed_treants;
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

// トレント設置処理
bool place_treant_next_to_corridor(vector<pair<int, int>> &corridor_cells,
                                   vector<string> &temp_maze,
                                   vector<pair<int, int>> &additional_treants,
                                   WallDSU &wall_dsu, int pi, int pj,
                                   vector<CycleHistory> &cycle_history) {
    // 冒険者の初期位置（森の入口）
    int adventurer_start_r = 0;
    int adventurer_start_c = N / 2;

    vector<pair<int, int>> new_corridors;
    vector<pair<int, int>> new_treants;
    bool placed_any_treant = false;

    // 前のサイクルのトレント位置を取得
    vector<pair<int, int>> previous_treants;
    if (!cycle_history.empty()) {
        previous_treants = cycle_history.back().treants;
    }

    // すべての通路マスに対してトレント設置を試行
    for (const auto &corridor : corridor_cells) {
        int corridor_r = corridor.first;
        int corridor_c = corridor.second;

        // 通路マスの右と下、さらに右のマスにトレント設置を試行
        vector<pair<int, int>> treant_offsets = {
            {0, 1}, // 右
            {1, 0}, // 下
            {0, 2}  // さらに右（設置失敗時の代替位置）
        };

        for (const auto &offset : treant_offsets) {
            int treant_r = corridor_r + offset.first;
            int treant_c = corridor_c + offset.second;

            // 範囲チェック
            if (treant_r >= N - 1 || treant_c >= N - 1 || treant_r <= 0 ||
                treant_c <= 0)
                continue;

            // 既にトレントが配置されている場合はスキップ
            if (temp_maze[treant_r][treant_c] != '.')
                continue;

            // 冒険者の初期位置は避ける
            if (treant_r == adventurer_start_r &&
                treant_c == adventurer_start_c)
                continue;

            // 通路マスにはトレントを設置しない（全履歴をチェック）
            bool is_corridor_cell = false;
            for (const auto &cycle : cycle_history) {
                for (const auto &corridor_pos : cycle.corridors) {
                    if (corridor_pos.first == treant_r &&
                        corridor_pos.second == treant_c) {
                        is_corridor_cell = true;
                        break;
                    }
                }
                if (is_corridor_cell)
                    break;
            }
            // 現在のサイクルの通路もチェック
            for (const auto &corridor_pos : corridor_cells) {
                if (corridor_pos.first == treant_r &&
                    corridor_pos.second == treant_c) {
                    is_corridor_cell = true;
                    break;
                }
            }
            if (is_corridor_cell)
                continue;

            // 前のサイクルのトレントとの8近傍隣接チェック
            bool adjacent_to_previous_treant = false;
            for (const auto &prev_treant : previous_treants) {
                for (int d = 0; d < 8; ++d) {
                    int check_r = prev_treant.first + dr8[d];
                    int check_c = prev_treant.second + dc8[d];
                    if (check_r == treant_r && check_c == treant_c) {
                        adjacent_to_previous_treant = true;
                        break;
                    }
                }
                if (adjacent_to_previous_treant)
                    break;
            }
            if (adjacent_to_previous_treant) {
                continue;
            }

            // 外周の木との8近傍隣接チェック
            bool adjacent_to_boundary = false;
            for (int d = 0; d < 8; ++d) {
                int nr = treant_r + dr8[d];
                int nc = treant_c + dc8[d];
                if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                    (temp_maze[nr][nc] == 'T' || temp_maze[nr][nc] == 't')) {
                    if (wall_dsu.is_connected_to_boundary(
                            coord_to_wall_index(nr, nc))) {
                        adjacent_to_boundary = true;
                        break;
                    }
                }
            }

            // 外周に隣接する場合はスキップ
            if (adjacent_to_boundary)
                continue;

            // 到達不能エリア増加チェック
            if (increases_unreachable_area(treant_r, treant_c, temp_maze))
                continue;

            // トレント配置を試す
            temp_maze[treant_r][treant_c] = 't';

            // 経路が確保されているかチェック
            if (calculate_path_length(pi, pj, ti, tj, temp_maze) != -1) {
                additional_treants.push_back({treant_r, treant_c});
                new_treants.push_back({treant_r, treant_c});
                placed_any_treant = true;

                // DSUに新しいトレントを追加
                int new_idx = coord_to_wall_index(treant_r, treant_c);
                for (int d = 0; d < 8; ++d) {
                    int nr = treant_r + dr8[d];
                    int nc = treant_c + dc8[d];
                    if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                        (temp_maze[nr][nc] == 'T' ||
                         temp_maze[nr][nc] == 't')) {
                        wall_dsu.merge(new_idx, coord_to_wall_index(nr, nc));
                    }
                }

                // 新たに配置したトレントの周囲に通路を追加
                add_corridor_cells(treant_r, treant_c, new_corridors,
                                   temp_maze);

                // 一つのトレント設置に成功したら、この通路マスからの設置は完了
                break;

            } else {
                // 経路が途絶える場合は元に戻す
                temp_maze[treant_r][treant_c] = '.';
            }
        }
    }

    // 新しい通路をリストに追加
    corridor_cells.insert(corridor_cells.end(), new_corridors.begin(),
                          new_corridors.end());

    // サイクル履歴に記録
    if (placed_any_treant || !new_corridors.empty()) {
        CycleHistory current_cycle;
        current_cycle.treants = new_treants;
        current_cycle.corridors = new_corridors;
        cycle_history.push_back(current_cycle);

        // デバッグ出力
    }

    return placed_any_treant;
}

// 斜め通路を確保するための追加トレント配置（焼きなまし版）
vector<pair<int, int>> place_diagonal_corridor_treants(
    int pi, int pj, const vector<pair<int, int>> &existing_treants) {
    vector<pair<int, int>> current_treants = existing_treants;
    vector<string> temp_maze = current_maze;

    // 冒険者の初期位置（森の入口）
    int adventurer_start_r = 0;
    int adventurer_start_c = N / 2;

    // 既存のトレントを仮配置
    for (const auto &p : current_treants) {
        temp_maze[p.first][p.second] = 't';
    }

    // 初期状態での到達不能マスを記録
    set<pair<int, int>> initial_unreachable = get_unreachable_cells(
        temp_maze, adventurer_start_r, adventurer_start_c);

    // 渦巻きで確保された通路マスを特定（花の周囲と渦巻き経路）
    set<pair<int, int>> protected_cells;
    // 花の位置と花の周囲を保護
    protected_cells.insert({ti, tj});
    for (int d = 0; d < 4; ++d) {
        int nr = ti + dr[d];
        int nc = tj + dc[d];
        if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
            if (temp_maze[nr][nc] == '.') {
                protected_cells.insert({nr, nc});
            }
        }
    }

    // 乱数生成器
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> pos_dist(1, N - 2); // 外周を避ける
    uniform_real_distribution<> prob_dist(0.0, 1.0);

    // 焼きなまし操作を繰り返す
    const int MAX_OPERATIONS = 100; // 操作回数の上限
    int operations = 0;
    vector<pair<int, int>> new_treants;

    while (operations < MAX_OPERATIONS && !check_time_limit(0.98)) {
        operations++;

        // ランダムなマスを選択（外周を避ける）
        int r = pos_dist(gen);
        int c = pos_dist(gen);

        // 冒険者の初期位置をスキップ
        if (r == adventurer_start_r && c == adventurer_start_c) {
            continue;
        }

        // 保護されたマス（渦巻きの通路）をスキップ
        if (protected_cells.count({r, c})) {
            continue;
        }

        // 8近傍のトレント/木の数を数える
        int adjacent_count = 0;
        for (int d = 0; d < 8; ++d) {
            int nr = r + dr8[d];
            int nc = c + dc8[d];
            if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                (temp_maze[nr][nc] == 'T' || temp_maze[nr][nc] == 't')) {
                adjacent_count++;
            }
        }

        bool operation_performed = false;

        // 操作1: トレントがいる場合、周囲に3個以上あれば削除
        if (temp_maze[r][c] == 't' && adjacent_count >= 3) {
            // トレントを削除してみる
            temp_maze[r][c] = '.';

            // 連結性チェック（新たな到達不能マスが発生しないことを確認）
            // 初期状態の到達不能マス以外に新たな到達不能マスが発生していないか確認
            set<pair<int, int>> current_unreachable = get_unreachable_cells(
                temp_maze, adventurer_start_r, adventurer_start_c);
            bool no_new_unreachable = true;
            for (const auto &cell : current_unreachable) {
                if (initial_unreachable.find(cell) ==
                    initial_unreachable.end()) {
                    no_new_unreachable = false;
                    break;
                }
            }

            if (check_connectivity(temp_maze) &&
                calculate_path_length(pi, pj, ti, tj, temp_maze) != -1 &&
                no_new_unreachable) {
                // 削除を確定
                // current_treants から削除
                auto it = find(current_treants.begin(), current_treants.end(),
                               make_pair(r, c));
                if (it != current_treants.end()) {
                    current_treants.erase(it);
                }
                operation_performed = true;
            } else {
                // 削除を取り消し
                temp_maze[r][c] = 't';
            }
        }
        // 操作2: 空きマスの場合、周囲に2個以下ならトレント追加
        else if (temp_maze[r][c] == '.' && adjacent_count <= 2) {
            // トレントを追加してみる
            temp_maze[r][c] = 't';

            // 連結性チェック（新たな到達不能マスが発生しないことを確認）
            // 初期状態の到達不能マス以外に新たな到達不能マスが発生していないか確認
            set<pair<int, int>> current_unreachable = get_unreachable_cells(
                temp_maze, adventurer_start_r, adventurer_start_c);
            bool no_new_unreachable = true;
            for (const auto &cell : current_unreachable) {
                if (initial_unreachable.find(cell) ==
                    initial_unreachable.end()) {
                    no_new_unreachable = false;
                    break;
                }
            }

            if (check_connectivity(temp_maze) &&
                calculate_path_length(pi, pj, ti, tj, temp_maze) != -1 &&
                no_new_unreachable) {
                // 追加を確定
                current_treants.push_back({r, c});
                new_treants.push_back({r, c});
                operation_performed = true;
            } else {
                // 追加を取り消し
                temp_maze[r][c] = '.';
            }
        }

        // 操作が成功した場合のみカウント
        if (!operation_performed) {
            operations--; // 失敗した操作はカウントしない
        }
    }

    return new_treants;
}

// 評価関数：トレント配置の評価値を計算
double evaluate_treant_configuration(const vector<string> &maze) {
    int adventurer_start_r = 0;
    int adventurer_start_c = N / 2;

    // スタート地点から花までの経路長
    int path_length = calculate_path_length(adventurer_start_r,
                                            adventurer_start_c, ti, tj, maze);
    if (path_length == -1)
        return -1e9; // 到達不能は最悪評価

    // 到達不能エリアのペナルティ
    int unreachable_count =
        count_unreachable_cells(maze, adventurer_start_r, adventurer_start_c);

    // 花からの平均距離
    double avg_distance = calculate_average_distance_to_flower(
        adventurer_start_r, adventurer_start_c, maze);

    // トレント数（多いほど複雑な経路を作れる）
    int treant_count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (maze[i][j] == 't' || maze[i][j] == 'T') {
                treant_count++;
            }
        }
    }

    // 評価値計算
    double score = path_length * PATH_LENGTH_WEIGHT -
                   unreachable_count * UNREACHABLE_PENALTY +
                   avg_distance * DISTANCE_TO_FLOWER_WEIGHT +
                   treant_count * 0.1; // トレント数にも小さな重みを付ける

    return score;
}

// 焼きなまし最適化
vector<pair<int, int>> simulated_annealing_optimization(
    const vector<pair<int, int>> &initial_treants) {

    // 初期状態の設定
    vector<pair<int, int>> current_treants = initial_treants;
    vector<string> current_maze = ::current_maze;
    for (const auto &t : current_treants) {
        current_maze[t.first][t.second] = 'T';
    }

    double current_score = evaluate_treant_configuration(current_maze);

    // 最良解の保持
    vector<pair<int, int>> best_treants = current_treants;
    double best_score = current_score;

    // 乱数生成器
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> prob_dist(0.0, 1.0);

    int adventurer_start_r = 0;
    int adventurer_start_c = N / 2;

    // 焼きなまし反復
    int iterations = 0;
    int accepted = 0;
    int improved = 0;

    while (iterations < ANNEALING_ITERATIONS && !check_time_limit(0.95)) {
        iterations++;

        // 温度の計算（線形冷却）
        double progress = (double)iterations / ANNEALING_ITERATIONS;
        double temperature = INITIAL_TEMPERATURE * (1.0 - progress) +
                             FINAL_TEMPERATURE * progress;

        // 隣接解の生成（3つの操作からランダムに選択）
        uniform_int_distribution<> op_dist(0, 2);
        int operation = op_dist(gen);

        vector<pair<int, int>> new_treants = current_treants;
        vector<string> new_maze = ::current_maze;

        bool valid_operation = false;

        if (operation == 0 && !current_treants.empty()) {
            // 操作1: トレントを移動（8近傍）
            uniform_int_distribution<> treant_dist(0,
                                                   current_treants.size() - 1);
            int idx = treant_dist(gen);

            uniform_int_distribution<> dir_dist(0, 7);
            int dir = dir_dist(gen);

            int old_r = current_treants[idx].first;
            int old_c = current_treants[idx].second;
            int new_r = old_r + dr8[dir];
            int new_c = old_c + dc8[dir];

            // 境界チェックと移動可能性チェック
            if (new_r > 0 && new_r < N - 1 && new_c > 0 && new_c < N - 1 &&
                ::current_maze[new_r][new_c] == '.' &&
                !(new_r == adventurer_start_r && new_c == adventurer_start_c) &&
                !(new_r == ti && new_c == tj)) {

                new_treants[idx] = {new_r, new_c};
                valid_operation = true;
            }
        } else if (operation == 1 && !current_treants.empty()) {
            // 操作2: トレントを削除（周囲にトレント/木が3個以上ある場合のみ）
            uniform_int_distribution<> treant_dist(0,
                                                   current_treants.size() - 1);
            int idx = treant_dist(gen);

            int r = current_treants[idx].first;
            int c = current_treants[idx].second;

            // 周囲の木/トレント数を数える
            int adjacent_count = 0;
            for (int d = 0; d < 8; d++) {
                int nr = r + dr8[d];
                int nc = c + dc8[d];
                if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                    (::current_maze[nr][nc] == 'T' ||
                     ::current_maze[nr][nc] == 't')) {
                    adjacent_count++;
                }
            }

            // 周囲に3個以上ある場合のみ削除
            if (adjacent_count >= 3) {
                new_treants.erase(new_treants.begin() + idx);
                valid_operation = true;
            }
        } else {
            // 操作3: トレントを追加（周囲にトレント/木が少ない空きマス）
            uniform_int_distribution<> pos_dist(1, N - 2);
            int r = pos_dist(gen);
            int c = pos_dist(gen);

            if (::current_maze[r][c] == '.' &&
                !(r == adventurer_start_r && c == adventurer_start_c) &&
                !(r == ti && c == tj)) {

                // 周囲の木/トレント数を数える
                int adjacent_count = 0;
                for (int d = 0; d < 8; d++) {
                    int nr = r + dr8[d];
                    int nc = c + dc8[d];
                    if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                        (::current_maze[nr][nc] == 'T' ||
                         ::current_maze[nr][nc] == 't')) {
                        adjacent_count++;
                    }
                }

                // 周囲に2個以下の場合のみ追加
                if (adjacent_count <= 2) {
                    new_treants.push_back({r, c});
                    valid_operation = true;
                }
            }
        }

        if (!valid_operation)
            continue;

        // 新しい迷路を構築
        for (const auto &t : new_treants) {
            new_maze[t.first][t.second] = 'T';
        }

        // 連結性チェック
        if (!check_connectivity(new_maze))
            continue;

        // 新しい解の評価
        double new_score = evaluate_treant_configuration(new_maze);

        // 受理判定
        double delta = new_score - current_score;
        if (delta > 0 || prob_dist(gen) < exp(delta / temperature)) {
            current_treants = new_treants;
            current_maze = new_maze;
            current_score = new_score;
            accepted++;

            // 最良解の更新
            if (new_score > best_score) {
                best_treants = current_treants;
                best_score = new_score;
                improved++;
            }
        }
    }

    return best_treants;
}

// 最初のターンの処理
void solve_first_turn(int pi, int pj, int /* n */,
                      const vector<pair<int, int>> &newly_confirmed) {
    for (const auto &p : newly_confirmed) {
        confirmed[p.first][p.second] = true;
    }

    vector<string> original_maze = current_maze;
    vector<pair<int, int>> valid_treants;
    vector<string> working_maze = original_maze;

    // 時間計測開始
    start_time = chrono::high_resolution_clock::now();

    // 木の密度を計算して配置間隔を決定
    double tree_density = calculate_tree_density();
    int dynamic_interval = (tree_density > TREE_DENSITY_THRESHOLD)
                               ? 4
                               : MECHANICAL_PLACEMENT_INTERVAL;

    // 1. 渦巻きアルゴリズムを固定100回実行
    current_maze = original_maze;
    vector<pair<int, int>> spiral_treants = create_strategic_treants(pi, pj, 0, 0);

    // 渦巻きトレントを一つずつ検証して配置
    for (const auto &p : spiral_treants) {
        working_maze[p.first][p.second] = 't';
        if (check_connectivity(working_maze) &&
            calculate_path_length(pi, pj, ti, tj, working_maze) != -1 &&
            count_unreachable_cells(working_maze, 0, N/2) == 0) {
            valid_treants.push_back(p);
        } else {
            working_maze[p.first][p.second] = '.'; // 連結性が失われる場合は元に戻す
        }
    }

    // 2. 機械的配置（斜め線状）を1度だけ実行
    current_maze = working_maze; // 現在の状態を更新
    vector<pair<int, int>> mechanical_treants =
        place_mechanical_treants(pi, pj, valid_treants, dynamic_interval);

    // 機械的配置トレントを一つずつ検証して配置
    for (const auto &p : mechanical_treants) {
        if (working_maze[p.first][p.second] == '.' &&
            confirmed[p.first][p.second] == false) {
            working_maze[p.first][p.second] = 't';
            if (check_connectivity(working_maze) &&
                calculate_path_length(pi, pj, ti, tj, working_maze) != -1 &&
                count_unreachable_cells(working_maze, 0, N/2) == 0) {
                valid_treants.push_back(p);
            } else {
                working_maze[p.first][p.second] = '.'; // 連結性が失われる場合は元に戻す
            }
        }
    }

    // 3. 残り時間でplace_diagonal_corridor_treantsを繰り返し実行
    while (!check_time_limit(0.90)) {
        current_maze = working_maze; // 現在の状態を更新
        vector<pair<int, int>> additional_treants =
            place_diagonal_corridor_treants(pi, pj, valid_treants);
        if (additional_treants.empty()) {
            break; // これ以上配置できない場合は終了
        }

        // 追加トレントを一つずつ検証して配置
        for (const auto &p : additional_treants) {
            if (working_maze[p.first][p.second] == '.' &&
                confirmed[p.first][p.second] == false) {
                working_maze[p.first][p.second] = 't';
                if (check_connectivity(working_maze) &&
                    calculate_path_length(pi, pj, ti, tj, working_maze) != -1 &&
                    count_unreachable_cells(working_maze, 0, N/2) == 0) {
                    valid_treants.push_back(p);
                } else {
                    working_maze[p.first][p.second] = '.'; // 連結性が失われる場合は元に戻す
                }
            }
        }
    }

    // 最終検証：全トレント配置後の連結性確認
    vector<string> final_maze = original_maze;
    vector<pair<int, int>> final_treants;

    for (const auto &p : valid_treants) {
        if (final_maze[p.first][p.second] == '.' &&
            confirmed[p.first][p.second] == false) {
            final_maze[p.first][p.second] = 't';
            if (check_connectivity(final_maze) &&
                calculate_path_length(pi, pj, ti, tj, final_maze) != -1 &&
                count_unreachable_cells(final_maze, 0, N/2) == 0) {
                final_treants.push_back(p);
            } else {
                final_maze[p.first][p.second] = '.'; // 問題がある場合はスキップ
            }
        }
    }

    // 最終的なトレント配置を出力
    cout << final_treants.size();
    for (const auto &p : final_treants) {
        cout << " " << p.first << " " << p.second;
        current_maze[p.first][p.second] = 'T'; // 確定
    }
    cout << endl << flush; // flushを追加
}

// インタラクティブループ
void solve() {
    // ターン処理を継続
    while (true) {
        int pi, pj, n;
        cin >> pi >> pj >> n;

        // ゴールに到達したら終了
        if (pi == ti && pj == tj) {

            break;
        }

        // 新たに確認されたマスを読み込む
        vector<pair<int, int>> newly_confirmed(n);
        for (int i = 0; i < n; ++i) {
            cin >> newly_confirmed[i].first >> newly_confirmed[i].second;
            confirmed[newly_confirmed[i].first][newly_confirmed[i].second] =
                true;
        }

        // 最初のターンの特別処理
        if (pi == 0 && pj == N / 2) {
            solve_first_turn(pi, pj, n, newly_confirmed);
        } else {
            // 2ターン目以降は打ち切り出力して終了
            cout << -1 << endl << flush;
            break;
        }
    }
}

int main() {
    // 入力
    cin >> N >> ti >> tj;
    current_maze.resize(N);
    confirmed.assign(N, vector<bool>(N, false));

    for (int i = 0; i < N; ++i) {
        cin >> current_maze[i];
    }

    // インタラクティブループ開始
    solve();

    return 0;
}
