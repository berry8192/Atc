#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>

using namespace std;

// グローバル変数
int N, ti, tj;
vector<string> current_maze;
vector<vector<bool>> confirmed;
vector<pair<int, int>> placed_treants; // 配置済みトレントのリスト

// 4方向の移動
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// 花の周辺渦巻きの試行回数
const int FLOWER_SPIRAL_TRIALS = 100;
const int MAX_SPIRAL_STEPS = 30;
const int SIMULATION_DEPTH = 3;  // シミュレーションの深さ

// 道を管理する構造体
struct Path {
    vector<pair<int, int>> cells;  // 道のマスリスト
    int last_dir;  // 最後に進んだ方向
    bool active;  // この道がアクティブか

    Path() : last_dir(-1), active(true) {}

    pair<int, int> head() const {
        if (cells.empty()) return {-1, -1};
        return cells.back();
    }

    void add_cell(int r, int c, int dir) {
        cells.push_back({r, c});
        last_dir = dir;
    }
};

// 時間計測用
chrono::high_resolution_clock::time_point start_time;
const double TIME_LIMIT = 1800.0;

bool check_time_limit(double usage_ratio = 1.0) {
    auto current_time = chrono::high_resolution_clock::now();
    double elapsed =
        chrono::duration_cast<chrono::milliseconds>(current_time - start_time)
            .count();
    return elapsed >= TIME_LIMIT * usage_ratio;
}

// 2点間の最短経路長を計算
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
    return -1;
}

// 到達不能地点の数を計算
int count_unreachable_cells(const vector<string> &maze, int start_r,
                            int start_c) {
    vector<vector<bool>> reachable(N, vector<bool>(N, false));
    queue<pair<int, int>> q;

    if (maze[start_r][start_c] != '.')
        return N * N;

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

// 経路中のマスの花からのマンハッタン距離の平均を計算
double calculate_average_distance_to_flower(int pi, int pj,
                                            const vector<string> &maze) {
    vector<vector<int>> dist(N, vector<int>(N, -1));
    queue<pair<int, int>> q;
    vector<pair<int, int>> path;

    if (maze[pi][pj] == 'T' || maze[pi][pj] == 't')
        return 1e9;

    dist[pi][pj] = 0;
    q.push({pi, pj});

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        int r = curr.first;
        int c = curr.second;

        if (r == ti && c == tj) {
            int cr = ti, cc = tj;
            while (!(cr == pi && cc == pj)) {
                path.push_back({cr, cc});
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
        return 1e9;

    double total_distance = 0.0;
    for (const auto &pos : path) {
        int manhattan_dist = abs(pos.first - ti) + abs(pos.second - tj);
        total_distance += manhattan_dist;
    }

    return total_distance / path.size();
}

// 分岐点を探す（周囲3マスが空きマスの場所）
pair<int, int> find_branch_point(int pi, int pj) {
    vector<vector<int>> dist(N, vector<int>(N, -1));
    queue<pair<int, int>> q;

    dist[pi][pj] = 0;
    q.push({pi, pj});

    pair<int, int> best_point = {-1, -1};
    int min_distance = 1e9;

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        int r = curr.first;
        int c = curr.second;

        // 周囲の空きマスをカウント
        int empty_count = 0;
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                current_maze[nr][nc] == '.') {
                empty_count++;
            }
        }

        // 周囲3マスが空きマスで、最も近い場所を選択
        if (empty_count >= 3 && dist[r][c] > 0 && dist[r][c] < min_distance) {
            min_distance = dist[r][c];
            best_point = {r, c};
        }

        // BFS続行
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < N && dist[nr][nc] == -1 &&
                current_maze[nr][nc] == '.') {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    return best_point;
}

// スタート地点からの到達可能性をチェック（全ての空きマスが到達可能か確認）
bool check_reachability_after_placing(const vector<string> &maze, int treant_r,
                                      int treant_c) {
    vector<string> test_maze = maze;
    test_maze[treant_r][treant_c] = 'T';

    // スタート地点から花への到達可能性をチェック
    if (calculate_path_length(0, N / 2, ti, tj, test_maze) == -1) {
        return false;
    }

    // 全ての空きマスが到達可能かチェック
    vector<vector<bool>> reachable(N, vector<bool>(N, false));
    queue<pair<int, int>> q;

    reachable[0][N/2] = true;
    q.push({0, N/2});

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                !reachable[nr][nc] && test_maze[nr][nc] == '.') {
                reachable[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }

    // 到達不能な空きマスがあるかチェック
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (test_maze[i][j] == '.' && !reachable[i][j]) {
                return false;  // 到達不能な空きマスがある
            }
        }
    }

    return true;
}

// 花の周辺に渦巻きトレントを配置（1回の試行）
vector<pair<int, int>> create_flower_spiral_trial(const vector<string> &maze,
                                                  int pi, int pj, int open_dir,
                                                  mt19937 &gen) {
    vector<pair<int, int>> treants_to_place;
    vector<string> working_maze = maze;

    int adventurer_start_r = 0;
    int adventurer_start_c = N / 2;

    vector<pair<pair<int, int>, int>> placed_treants_with_priority;

    // 花の周りの3方向を最初に塞ぐ
    for (int i = 0; i < 4; ++i) {
        if (i == open_dir)
            continue;
        int nr = ti + dr[i];
        int nc = tj + dc[i];
        if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
            working_maze[nr][nc] == '.' &&
            !(nr == adventurer_start_r && nc == adventurer_start_c)) {
            working_maze[nr][nc] = 't';
            treants_to_place.push_back({nr, nc});
            placed_treants_with_priority.push_back({{nr, nc}, 100});
        }
    }

    int current_r = ti + dr[open_dir];
    int current_c = tj + dc[open_dir];
    int prev_r = ti;
    int prev_c = tj;

    if (current_r < 0 || current_r >= N || current_c < 0 || current_c >= N ||
        working_maze[current_r][current_c] != '.') {
        return {};
    }

    // トレント引き寄せ経路構築
    for (int step = 0; step < MAX_SPIRAL_STEPS; ++step) {
        vector<pair<int, int>> candidates;

        for (int j = 0; j < 4; ++j) {
            int nr = current_r + dr[j];
            int nc = current_c + dc[j];

            if (nr == prev_r && nc == prev_c)
                continue;

            if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                working_maze[nr][nc] == '.') {
                candidates.push_back({nr, nc});
            }
        }

        if (candidates.empty())
            break;

        vector<int> best_candidates;
        double min_distance_sq = 1e9;

        for (int i = 0; i < candidates.size(); ++i) {
            int nr = candidates[i].first;
            int nc = candidates[i].second;

            double min_dist_sq_to_high_priority = 1e9;
            for (const auto &treant_info : placed_treants_with_priority) {
                if (treant_info.second == 100) {
                    int tr = treant_info.first.first;
                    int tc = treant_info.first.second;
                    double dist_sq =
                        (nr - tr) * (nr - tr) + (nc - tc) * (nc - tc);
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

        uniform_int_distribution<> candidate_dist(0,
                                                  best_candidates.size() - 1);
        int selected_idx = candidate_dist(gen);
        int best_candidate = best_candidates[selected_idx];

        int next_r = candidates[best_candidate].first;
        int next_c = candidates[best_candidate].second;

        for (int j = 0; j < 4; ++j) {
            int tr = prev_r + dr[j];
            int tc = prev_c + dc[j];
            if (tr >= 0 && tr < N && tc >= 0 && tc < N &&
                working_maze[tr][tc] == '.' &&
                (tr != current_r || tc != current_c) &&
                (tr != next_r || tc != next_c) &&
                !(tr == adventurer_start_r && tc == adventurer_start_c)) {

                working_maze[tr][tc] = 't';
                if (calculate_path_length(pi, pj, ti, tj, working_maze) != -1) {
                    treants_to_place.push_back({tr, tc});
                    int new_priority = max(10, 100 - step * 5);
                    placed_treants_with_priority.push_back(
                        {{tr, tc}, new_priority});
                } else {
                    working_maze[tr][tc] = '.';
                }
            }
        }

        prev_r = current_r;
        prev_c = current_c;
        current_r = next_r;
        current_c = next_c;
    }

    return treants_to_place;
}

// 花の周辺に渦巻きトレントを配置（最良を選択）
vector<pair<int, int>> create_flower_spiral(const vector<string> &maze, int pi,
                                            int pj) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> open_dir_dist(0, 3);

    vector<pair<int, int>> best_treants;
    int best_score = -1e9;

    for (int trial = 0; trial < FLOWER_SPIRAL_TRIALS; trial++) {
        int random_open_dir = open_dir_dist(gen);

        vector<pair<int, int>> treants =
            create_flower_spiral_trial(maze, pi, pj, random_open_dir, gen);

        if (treants.empty())
            continue;

        vector<string> temp_maze = maze;
        for (const auto &p : treants) {
            temp_maze[p.first][p.second] = 't';
        }

        int path_length = calculate_path_length(pi, pj, ti, tj, temp_maze);
        if (path_length == -1)
            continue;

        int unreachable_count = count_unreachable_cells(temp_maze, 0, N / 2);
        double avg_distance_to_flower =
            calculate_average_distance_to_flower(pi, pj, temp_maze);

        int score = path_length * 2 - unreachable_count * 1 +
                    (int)(avg_distance_to_flower * 5);

        if (score > best_score) {
            best_score = score;
            best_treants = treants;
        }

        if (check_time_limit(0.95))
            break;
    }

    return best_treants;
}

// 3手先までシミュレーションして詰みをチェック
bool simulate_path_viability(const vector<string> &maze, int start_r, int start_c,
                            int depth, set<pair<int, int>> &visited) {
    if (depth == 0) return true;

    visited.insert({start_r, start_c});

    int valid_moves = 0;
    for (int i = 0; i < 4; i++) {
        int nr = start_r + dr[i];
        int nc = start_c + dc[i];

        if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
            maze[nr][nc] == '.' && visited.find({nr, nc}) == visited.end()) {
            set<pair<int, int>> new_visited = visited;
            if (simulate_path_viability(maze, nr, nc, depth - 1, new_visited)) {
                valid_moves++;
            }
        }
    }

    return valid_moves > 0;
}

// 周囲の空きマス数をカウント
int count_empty_neighbors(const vector<string> &maze, int r, int c) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr >= 0 && nr < N && nc >= 0 && nc < N && maze[nr][nc] == '.') {
            count++;
        }
    }
    return count;
}

// 木構造のように分岐する道を作成
vector<pair<int, int>> create_branching_paths(int pi, int pj) {
    vector<pair<int, int>> treants_to_place;
    vector<string> working_maze = current_maze;

    // まず花の周辺に渦巻きトレントを配置
    vector<pair<int, int>> flower_treants =
        create_flower_spiral(working_maze, pi, pj);
    for (const auto &t : flower_treants) {
        working_maze[t.first][t.second] = 'T';
        treants_to_place.push_back(t);
    }

    // 最初の分岐点を探す
    pair<int, int> initial_branch = find_branch_point(pi, pj);
    if (initial_branch.first == -1 || initial_branch.second == -1) {
        return treants_to_place;
    }

    int br = initial_branch.first;
    int bc = initial_branch.second;

    // 冒険者のスタート位置から分岐点までの経路を計算
    vector<vector<int>> dist(N, vector<int>(N, -1));
    vector<vector<pair<int, int>>> parent(N,
                                          vector<pair<int, int>>(N, {-1, -1}));
    queue<pair<int, int>> q;
    dist[pi][pj] = 0;
    q.push({pi, pj});

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < N && nc >= 0 && nc < N && dist[nr][nc] == -1 &&
                working_maze[nr][nc] == '.') {
                dist[nr][nc] = dist[r][c] + 1;
                parent[nr][nc] = {r, c};
                q.push({nr, nc});
            }
        }
    }

    // 分岐点から開始点への経路を復元
    vector<pair<int, int>> path_to_branch;
    int curr_r = br, curr_c = bc;
    while (curr_r != pi || curr_c != pj) {
        path_to_branch.push_back({curr_r, curr_c});
        auto [pr, pc] = parent[curr_r][curr_c];
        curr_r = pr;
        curr_c = pc;
    }
    path_to_branch.push_back({pi, pj});

    // 冒険者の初期位置周辺にトレントを配置（分岐点への道以外を塞ぐ）
    set<pair<int, int>> path_set(path_to_branch.begin(), path_to_branch.end());

    // 分岐点までの経路の各マスの4近傍にトレントを配置（経路以外）
    // 経路を逆順に処理（分岐点から開始点へ）
    for (int idx = 0; idx < path_to_branch.size(); idx++) {
        int pr = path_to_branch[idx].first;
        int pc = path_to_branch[idx].second;

        // 分岐点は処理をスキップ
        if (pr == br && pc == bc) continue;

        for (int i = 0; i < 4; i++) {
            int nr = pr + dr[i];
            int nc = pc + dc[i];

            // 範囲内で、空きマスで、経路上でない場合
            if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                working_maze[nr][nc] == '.' &&
                path_set.find({nr, nc}) == path_set.end()) {

                // このマスにトレントを置いても到達可能性が保たれるか確認
                if (check_reachability_after_placing(working_maze, nr, nc)) {
                    working_maze[nr][nc] = 'T';
                    treants_to_place.push_back({nr, nc});
                }
            }
        }
    }

    // 冒険者がきた方向を特定
    int came_from_dir = -1;
    for (int i = 0; i < 4; i++) {
        int pr = br + dr[i];
        int pc = bc + dc[i];
        if (pr >= 0 && pr < N && pc >= 0 && pc < N &&
            dist[pr][pc] == dist[br][bc] - 1) {
            came_from_dir = i;
            break;
        }
    }

    // 全ての利用可能な方向（冒険者が来た方向以外）を取得
    vector<Path> paths;
    set<pair<int, int>> adventurer_path;
    adventurer_path.insert({br, bc});

    // 初期分岐の全方向に道を作成
    for (int i = 0; i < 4; i++) {
        if (i != came_from_dir) {
            int nr = br + dr[i];
            int nc = bc + dc[i];
            if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                working_maze[nr][nc] == '.') {
                Path new_path;
                new_path.add_cell(nr, nc, i);
                paths.push_back(new_path);
                adventurer_path.insert({nr, nc});
            }
        }
    }

    if (paths.empty()) {
        return treants_to_place;
    }

    // 道を成長させていく
    int iterations = 0;
    while (!paths.empty() && iterations < 200) { // 安全のため最大200回
        iterations++;

        // 新しい分岐道を一時的に保存
        vector<Path> new_paths;

        // アクティブな道を順番に処理
        for (auto& path : paths) {
            if (!path.active) continue;

            auto [curr_r, curr_c] = path.head();

            // 現在地が新たな分岐点になるかチェック
            int empty_neighbors = count_empty_neighbors(working_maze, curr_r, curr_c);

            // 3方向以上空いていれば分岐を生成
            if (empty_neighbors >= 3) {
                vector<int> available_dirs;
                for (int i = 0; i < 4; i++) {
                    int nr = curr_r + dr[i];
                    int nc = curr_c + dc[i];
                    if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                        working_maze[nr][nc] == '.' &&
                        adventurer_path.find({nr, nc}) == adventurer_path.end()) {

                        // 3手先までシミュレーション
                        set<pair<int, int>> visited;
                        if (simulate_path_viability(working_maze, nr, nc, SIMULATION_DEPTH, visited)) {
                            available_dirs.push_back(i);
                        }
                    }
                }

                // 複数方向に分岐
                if (available_dirs.size() >= 2) {
                    path.active = false; // 現在の道を非アクティブ化

                    for (int dir : available_dirs) {
                        Path branch_path;
                        branch_path.cells = path.cells; // 親の道を引き継ぐ
                        int nr = curr_r + dr[dir];
                        int nc = curr_c + dc[dir];
                        branch_path.add_cell(nr, nc, dir);
                        new_paths.push_back(branch_path);
                        adventurer_path.insert({nr, nc});
                    }
                    continue;
                }
            }

            // 通常の道の延長
            int best_r = -1, best_c = -1;
            int best_dir = -1;
            double max_score = -1e9;

            for (int i = 0; i < 4; i++) {
                int nr = curr_r + dr[i];
                int nc = curr_c + dc[i];

                if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                    working_maze[nr][nc] == '.' &&
                    adventurer_path.find({nr, nc}) == adventurer_path.end()) {

                    // 3手先までシミュレーション
                    set<pair<int, int>> visited;
                    if (!simulate_path_viability(working_maze, nr, nc, SIMULATION_DEPTH, visited)) {
                        continue;
                    }

                    // 他の道の先頭との距離を計算
                    double min_dist_to_others = 1e9;
                    for (const auto& other : paths) {
                        if (&other != &path && other.active) {
                            auto [or_, oc] = other.head();
                            double dist = sqrt((nr - or_) * (nr - or_) + (nc - oc) * (nc - oc));
                            min_dist_to_others = min(min_dist_to_others, dist);
                        }
                    }

                    double score = min_dist_to_others;

                    // 同じ方向への連続移動にペナルティ
                    if (i == path.last_dir) {
                        score -= 15;
                    }

                    // 花からの距離も考慮
                    score += sqrt((nr - ti) * (nr - ti) + (nc - tj) * (nc - tj)) * 0.5;

                    if (score > max_score) {
                        max_score = score;
                        best_r = nr;
                        best_c = nc;
                        best_dir = i;
                    }
                }
            }

            if (best_r == -1) {
                path.active = false; // 道が行き止まり
                continue;
            }

            // トレントを配置（冒険者の道以外の空きマス）
            for (int i = 0; i < 4; i++) {
                int tr = curr_r + dr[i];
                int tc = curr_c + dc[i];

                if (tr >= 0 && tr < N && tc >= 0 && tc < N &&
                    working_maze[tr][tc] == '.' &&
                    (tr != best_r || tc != best_c) &&
                    adventurer_path.find({tr, tc}) == adventurer_path.end()) {

                    // 到達可能性チェック
                    if (check_reachability_after_placing(working_maze, tr, tc)) {
                        working_maze[tr][tc] = 'T';
                        treants_to_place.push_back({tr, tc});
                    }
                }
            }

            // 道を延長
            path.add_cell(best_r, best_c, best_dir);
            adventurer_path.insert({best_r, best_c});
        }

        // 新しい分岐道を追加
        for (const auto& new_path : new_paths) {
            paths.push_back(new_path);
        }

        // 全ての道が非アクティブになったら終了
        bool all_inactive = true;
        for (const auto& path : paths) {
            if (path.active) {
                all_inactive = false;
                break;
            }
        }
        if (all_inactive) break;

        // メモリ対策：道が多すぎる場合は制限
        if (paths.size() > 50) {
            // アクティブな道のみ残す
            vector<Path> active_paths;
            for (const auto& path : paths) {
                if (path.active) {
                    active_paths.push_back(path);
                }
            }
            paths = active_paths;
        }
    }

    return treants_to_place;
}

int main() {
    cin >> N >> ti >> tj;
    current_maze.resize(N);
    confirmed.assign(N, vector<bool>(N, false));

    for (int i = 0; i < N; ++i) {
        cin >> current_maze[i];
    }

    start_time = chrono::high_resolution_clock::now();

    // 初期状態で渦巻きトレント配置
    int pi = 0;
    int pj = N / 2;

    // 初期確認済みマス設定
    confirmed[pi][pj] = true;

    while (true) {
        cin >> pi >> pj;
        int n;
        cin >> n;

        if (pi == ti && pj == tj) {
            return 0;
        }

        vector<pair<int, int>> newly_confirmed(n);
        for (int k = 0; k < n; ++k) {
            cin >> newly_confirmed[k].first >> newly_confirmed[k].second;
        }

        for (const auto &p : newly_confirmed) {
            confirmed[p.first][p.second] = true;
        }

        // 初回のみ分岐道を配置
        if (placed_treants.empty()) {
            vector<pair<int, int>> branch_treants =
                create_branching_paths(pi, pj);

            cout << branch_treants.size();
            for (const auto &p : branch_treants) {
                cout << " " << p.first << " " << p.second;
                current_maze[p.first][p.second] = 'T';
                placed_treants.push_back(p);
            }
            cout << endl;

            // 打ち切り出力
            cout << -1 << endl;
            return 0;
        } else {
            cout << 0 << endl;
        }
    }

    return 0;
}