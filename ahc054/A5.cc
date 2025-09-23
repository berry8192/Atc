#include <algorithm>
#include <chrono>
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

// 渦巻きの最大ステップ数
const int MAX_SPIRAL_STEPS = 30;
const int SPIRAL_TRIALS = 100;

// 評価値の重み
const int PATH_LENGTH_WEIGHT = 2;
const int UNREACHABLE_PENALTY = 1;
const int DISTANCE_TO_FLOWER_WEIGHT = 5;

// 時間計測用
chrono::high_resolution_clock::time_point start_time;
const double TIME_LIMIT = 1800.0;

bool check_time_limit(double usage_ratio = 1.0) {
    auto current_time = chrono::high_resolution_clock::now();
    double elapsed = chrono::duration_cast<chrono::milliseconds>(current_time - start_time).count();
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

            if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                dist[nr][nc] == -1 && maze[nr][nc] != 'T' && maze[nr][nc] != 't') {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    return -1;
}

// 到達不能地点の数を計算
int count_unreachable_cells(const vector<string> &maze, int start_r, int start_c) {
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

            if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                !reachable[nr][nc] && maze[nr][nc] == '.') {
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
double calculate_average_distance_to_flower(int pi, int pj, const vector<string> &maze) {
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

            if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                dist[nr][nc] == -1 && maze[nr][nc] != 'T' && maze[nr][nc] != 't') {
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

// 渦巻きアルゴリズム（1回の試行）
vector<pair<int, int>> create_single_spiral_trial(int pi, int pj, int open_dir, mt19937 &gen) {
    vector<pair<int, int>> treants_to_place;
    vector<string> original_maze = current_maze;

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
            original_maze[nr][nc] == '.' &&
            !(nr == adventurer_start_r && nc == adventurer_start_c)) {
            current_maze[nr][nc] = 't';
            treants_to_place.push_back({nr, nc});
            placed_treants_with_priority.push_back({{nr, nc}, 100});
        }
    }

    int current_r = ti + dr[open_dir];
    int current_c = tj + dc[open_dir];
    int prev_r = ti;
    int prev_c = tj;

    if (current_r < 0 || current_r >= N || current_c < 0 || current_c >= N ||
        current_maze[current_r][current_c] != '.') {
        current_maze = original_maze;
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
                current_maze[nr][nc] == '.') {
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
                    double dist_sq = (nr - tr) * (nr - tr) + (nc - tc) * (nc - tc);
                    min_dist_sq_to_high_priority = min(min_dist_sq_to_high_priority, dist_sq);
                }
            }

            if (min_dist_sq_to_high_priority < min_distance_sq) {
                min_distance_sq = min_dist_sq_to_high_priority;
                best_candidates.clear();
                best_candidates.push_back(i);
            } else if (abs(min_dist_sq_to_high_priority - min_distance_sq) < 1e-9) {
                best_candidates.push_back(i);
            }
        }

        uniform_int_distribution<> candidate_dist(0, best_candidates.size() - 1);
        int selected_idx = candidate_dist(gen);
        int best_candidate = best_candidates[selected_idx];

        int next_r = candidates[best_candidate].first;
        int next_c = candidates[best_candidate].second;

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
                    int new_priority = max(10, 100 - step * 5);
                    placed_treants_with_priority.push_back({{tr, tc}, new_priority});
                } else {
                    current_maze[tr][tc] = '.';
                }
            }
        }

        prev_r = current_r;
        prev_c = current_c;
        current_r = next_r;
        current_c = next_c;
    }

    current_maze = original_maze;
    return treants_to_place;
}

// 確率的渦巻きアルゴリズム
vector<pair<int, int>> create_strategic_treants(int pi, int pj) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> open_dir_dist(0, 3);

    vector<pair<int, int>> best_treants;
    int best_score = -1e9;

    for (int trial = 0; trial < SPIRAL_TRIALS; ++trial) {
        int random_open_dir = open_dir_dist(gen);

        vector<pair<int, int>> treants = create_single_spiral_trial(pi, pj, random_open_dir, gen);

        if (treants.empty())
            continue;

        vector<string> temp_maze = current_maze;
        for (const auto &p : treants) {
            temp_maze[p.first][p.second] = 't';
        }

        int path_length = calculate_path_length(pi, pj, ti, tj, temp_maze);
        if (path_length == -1)
            continue;

        int unreachable_count = count_unreachable_cells(temp_maze, 0, N / 2);
        double avg_distance_to_flower = calculate_average_distance_to_flower(pi, pj, temp_maze);

        int score = path_length * PATH_LENGTH_WEIGHT -
                    unreachable_count * UNREACHABLE_PENALTY +
                    (int)(avg_distance_to_flower * DISTANCE_TO_FLOWER_WEIGHT);

        if (score > best_score) {
            best_score = score;
            best_treants = treants;
        }

        if (check_time_limit(0.95))
            break;
    }

    return best_treants;
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

        // 初回のみ渦巻きトレントを配置
        if (placed_treants.empty()) {
            vector<pair<int, int>> spiral_treants = create_strategic_treants(pi, pj);

            cout << spiral_treants.size();
            for (const auto &p : spiral_treants) {
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