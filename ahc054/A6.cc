#include <algorithm>
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

const int SIMULATION_DEPTH = 3; // シミュレーションの深さ

// 道を管理する構造体
struct Path {
    vector<pair<int, int>> cells; // 道のマスリスト
    int last_dir;                 // 最後に進んだ方向
    bool active;                  // この道がアクティブか
    int start_r, start_c;         // 道の開始位置

    Path(int sr, int sc)
        : start_r(sr), start_c(sc), last_dir(-1), active(true) {
        cells.push_back({sr, sc});
    }

    pair<int, int> head() const {
        if (cells.empty())
            return {-1, -1};
        return cells.back();
    }

    void add_cell(int r, int c, int dir) {
        cells.push_back({r, c});
        last_dir = dir;
    }

    void deactivate() { active = false; }
};

// 森と道の状態を管理する構造体
struct Forest {
    vector<string> maze;                 // 現在の迷路
    vector<Path> paths;                  // 道のリスト
    set<pair<int, int>> adventurer_path; // 冒険者が通る道
    vector<pair<int, int>> treants;      // 配置するトレントのリスト
    int N, ti, tj;                       // 迷路のサイズと花の位置

    Forest(int n, int flower_i, int flower_j,
           const vector<string> &initial_maze)
        : N(n), ti(flower_i), tj(flower_j), maze(initial_maze) {}

    // 3手先までシミュレーションして詰みをチェック
    bool simulate_path_viability(int start_r, int start_c, int depth,
                                 set<pair<int, int>> &visited) {
        if (depth == 0)
            return true;

        visited.insert({start_r, start_c});

        int valid_moves = 0;
        for (int i = 0; i < 4; i++) {
            int nr = start_r + dr[i];
            int nc = start_c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < N && maze[nr][nc] == '.' &&
                visited.find({nr, nc}) == visited.end()) {
                set<pair<int, int>> new_visited = visited;
                if (simulate_path_viability(nr, nc, depth - 1, new_visited)) {
                    valid_moves++;
                }
            }
        }

        return valid_moves > 0;
    }

    // 道を生成
    void generate_paths(int start_r, int start_c) {
        // cerr << "=== Starting Forest path generation ===" << endl;
        // cerr << "Start position: (" << start_r << ", " << start_c << ")"
        //      << endl;
        // cerr << "Flower position: (" << ti << ", " << tj << ")" << endl;
        // cerr << "Maze size: " << N << "x" << N << endl;

        // 最初の道を作成
        Path initial_path(start_r, start_c);
        paths.push_back(initial_path);
        adventurer_path.insert({start_r, start_c});

        int iteration = 0;
        // 全ての道が詰むまで続ける
        while (true) {
            iteration++;

            vector<Path> new_paths;
            bool any_extended = false;

            // アクティブな道を処理
            for (auto &path : paths) {
                if (!path.active)
                    continue;

                auto [curr_r, curr_c] = path.head();

                // 利用可能な方向を探す
                vector<int> available_dirs;
                for (int i = 0; i < 4; i++) {
                    int nr = curr_r + dr[i];
                    int nc = curr_c + dc[i];

                    if (nr < 0 || nr >= N || nc < 0 || nc >= N) {
                        continue;
                    }
                    if (maze[nr][nc] != '.') {
                        continue;
                    }
                    if (adventurer_path.find({nr, nc}) !=
                        adventurer_path.end()) {
                        continue;
                    }

                    // 3手先までシミュレーション
                    set<pair<int, int>> visited;
                    if (simulate_path_viability(nr, nc, SIMULATION_DEPTH,
                                                visited)) {
                        available_dirs.push_back(i);
                    }
                }

                // 分岐可能な場合（3方向以上のみ分岐）
                if (available_dirs.size() >= 3) {
                    path.deactivate();

                    // 最大2方向のみ分岐し、残りにトレントを配置
                    for (int i = 0; i < min(2, (int)available_dirs.size()); i++) {
                        int dir = available_dirs[i];
                        int nr = curr_r + dr[dir];
                        int nc = curr_c + dc[dir];

                        Path branch_path(curr_r, curr_c);
                        branch_path.add_cell(nr, nc, dir);
                        new_paths.push_back(branch_path);
                        adventurer_path.insert({nr, nc});
                    }

                    // 使わなかった方向にトレントを配置
                    for (int i = 2; i < available_dirs.size(); i++) {
                        int dir = available_dirs[i];
                        int tr = curr_r + dr[dir];
                        int tc = curr_c + dc[dir];

                        // 花の位置にはトレントを配置しない
                        if (tr == ti && tc == tj) {
                            continue;
                        }

                        maze[tr][tc] = 'T';
                        treants.push_back({tr, tc});
                    }
                }
                // 1-2方向の場合は道を延長
                else if (available_dirs.size() > 0) {
                    int dir = available_dirs[0];
                    int nr = curr_r + dr[dir];
                    int nc = curr_c + dc[dir];


                    // 道を延長
                    path.add_cell(nr, nc, dir);
                    adventurer_path.insert({nr, nc});

                    // 他の方向にトレントを配置
                    for (int i = 0; i < 4; i++) {
                        if (i != dir) {
                            int tr = curr_r + dr[i];
                            int tc = curr_c + dc[i];

                            if (tr >= 0 && tr < N && tc >= 0 && tc < N &&
                                maze[tr][tc] == '.' &&
                                adventurer_path.find({tr, tc}) ==
                                    adventurer_path.end()) {

                                // 花の位置にはトレントを配置しない
                                if (tr == ti && tc == tj) {
                                            continue;
                                }

                                maze[tr][tc] = 'T';
                                treants.push_back({tr, tc});
                            }
                        }
                    }
                    any_extended = true;
                }
                // 行き止まりの場合
                else {
                    path.deactivate();
                }
            }

            // 新しい分岐道を追加
            for (const auto &new_path : new_paths) {
                paths.push_back(new_path);
            }

            // 全ての道が詰んだら終了
            if (!any_extended && new_paths.empty()) {
                bool all_inactive = true;
                for (const auto &path : paths) {
                    if (path.active) {
                        all_inactive = false;
                        break;
                    }
                }
                if (all_inactive) {
                    break;
                }
            }

            // メモリ対策：道が多すぎる場合は制限
            if (paths.size() > 50) {
                vector<Path> active_paths;
                for (const auto &path : paths) {
                    if (path.active) {
                        active_paths.push_back(path);
                        if (active_paths.size() >= 30)
                            break;
                    }
                }
                paths = active_paths;
            }
        }
    }

    // トレントのリストを取得
    vector<pair<int, int>> get_treants() const { return treants; }
};

int main() {
    cin >> N >> ti >> tj;
    current_maze.resize(N);
    confirmed.assign(N, vector<bool>(N, false));

    for (int i = 0; i < N; ++i) {
        cin >> current_maze[i];
    }

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
            // Forest構造体を使って道を生成
            Forest forest(N, ti, tj, current_maze);
            forest.generate_paths(pi, pj);
            vector<pair<int, int>> branch_treants = forest.get_treants();

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