#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

// グローバル変数
int N, ti, tj;
vector<string> current_maze;
vector<vector<bool>> confirmed;
vector<pair<int, int>> placed_treants;

// 4方向の移動
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// 道を管理する構造体
struct Path {
    int id;                       // 道のID
    vector<pair<int, int>> cells; // 道のマスリスト
    int last_dir;                 // 最後に進んだ方向
    bool active;                  // この道がアクティブか
    int extension_count;          // 分岐後の延長回数
    bool is_initial;              // 初期の道かどうか

    Path(int path_id, int sr, int sc, bool initial = false)
        : id(path_id), last_dir(-1), active(true), extension_count(0),
          is_initial(initial) {
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
        extension_count++;
    }

    void deactivate() { active = false; }

    bool can_branch() const {
        // 初期の道は即座に分岐可能、それ以外は4マス以上必要
        return is_initial || extension_count >= 4;
    }
};

// 迷路を生成する構造体
struct MazeGenerator {
    vector<string> maze;          // 現在の迷路
    vector<Path> paths;           // 道のリスト
    vector<vector<int>> path_map; // 各マスがどの道に属するか (-1: 未使用)
    vector<pair<int, int>> reserved_cells; // 冒険者の道として予約されたマス
    int N, ti, tj;
    int next_path_id;

    MazeGenerator(int n, int flower_i, int flower_j,
                  const vector<string> &initial_maze)
        : N(n), ti(flower_i), tj(flower_j), maze(initial_maze),
          next_path_id(1) {
        path_map.assign(N, vector<int>(N, -1));
    }

    // 指定したマスが使用可能か（異なる道と隣接しないか）
    bool can_use_cell(int r, int c, int path_id) {
        if (r < 0 || r >= N || c < 0 || c >= N)
            return false;
        if (maze[r][c] != '.')
            return false;
        if (path_map[r][c] != -1)
            return false; // 既に使用されている

        // 4近傍をチェック
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                // 異なる道のマスと隣接している場合は使用不可
                if (path_map[nr][nc] != -1 && path_map[nr][nc] != path_id) {
                    return false;
                }
            }
        }
        return true;
    }

    // 道を生成
    void generate_paths(int start_r, int start_c) {
        // 最初の道を作成（初期道なので即座に分岐可能）
        Path initial_path(next_path_id++, start_r, start_c, true);
        paths.push_back(initial_path);
        path_map[start_r][start_c] = initial_path.id;
        reserved_cells.push_back({start_r, start_c});

        cerr << "Starting path generation from (" << start_r << ", " << start_c
             << ")" << endl;

        int iteration = 0;
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

                    // このマスが使用可能か確認
                    if (can_use_cell(nr, nc, path.id)) {
                        available_dirs.push_back(i);
                    }
                }

                // 分岐可能な場合（2方向以上かつ4マス以上延長済み）
                if (available_dirs.size() >= 2 && path.can_branch()) {
                    path.deactivate();

                    // 各方向に新しい道を作成（最大3方向に制限）
                    int branch_count = min(3, (int)available_dirs.size());
                    for (int i = 0; i < branch_count; i++) {
                        int dir = available_dirs[i];
                        int nr = curr_r + dr[dir];
                        int nc = curr_c + dc[dir];

                        // 新しい道を作成
                        Path branch_path(next_path_id++, curr_r, curr_c);
                        branch_path.add_cell(nr, nc, dir);
                        new_paths.push_back(branch_path);

                        // マップを更新
                        path_map[nr][nc] = branch_path.id;
                        reserved_cells.push_back({nr, nc});
                    }
                }
                // 分岐できない（4マス未満）が複数方向がある場合は1方向を選んで直進
                else if (available_dirs.size() >= 2 && !path.can_branch()) {
                    // 前回と異なる方向を優先
                    int chosen_dir = available_dirs[0];
                    for (int dir : available_dirs) {
                        if (path.last_dir == -1 || dir != path.last_dir) {
                            chosen_dir = dir;
                            break;
                        }
                    }

                    int nr = curr_r + dr[chosen_dir];
                    int nc = curr_c + dc[chosen_dir];

                    // 道を延長
                    path.add_cell(nr, nc, chosen_dir);
                    path_map[nr][nc] = path.id;
                    reserved_cells.push_back({nr, nc});
                    any_extended = true;
                }
                // 1方向のみの場合は道を延長
                else if (available_dirs.size() == 1) {
                    int dir = available_dirs[0];
                    int nr = curr_r + dr[dir];
                    int nc = curr_c + dc[dir];

                    // 道を延長
                    path.add_cell(nr, nc, dir);
                    path_map[nr][nc] = path.id;
                    reserved_cells.push_back({nr, nc});
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
                if (all_inactive)
                    break;
            }

            // メモリ対策：道が多すぎる場合は制限
            if (paths.size() > 100) {
                vector<Path> active_paths;
                for (const auto &path : paths) {
                    if (path.active) {
                        active_paths.push_back(path);
                        if (active_paths.size() >= 50)
                            break;
                    }
                }
                paths = active_paths;
            }

            // 反復回数の制限
            if (iteration > 500)
                break;
        }

        // 道作成後、トレントを配置
        place_treants();
    }

    // BFSで到達可能性をチェック
    bool check_reachability(int start_r, int start_c,
                            const vector<string> &test_maze) {
        vector<vector<bool>> visited(N, vector<bool>(N, false));
        queue<pair<int, int>> q;
        q.push({start_r, start_c});
        visited[start_r][start_c] = true;

        bool flower_reachable = false;
        int reachable_count = 0;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            reachable_count++;

            if (r == ti && c == tj) {
                flower_reachable = true;
            }

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                    !visited[nr][nc] && test_maze[nr][nc] == '.') {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }

        // 全ての空きマスが到達可能かチェック
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (test_maze[i][j] == '.' && !visited[i][j]) {
                    return false;
                }
            }
        }

        return flower_reachable;
    }

    // トレントを配置すべきかチェック（2近傍以上がブロックされている場合は配置しない）
    bool should_place_treant(int r, int c, const vector<string> &test_maze) {
        int blocked_count = 0;
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N ||
                test_maze[nr][nc] == 'T') {
                blocked_count++;
            }
        }
        return blocked_count < 2;
    }

    // トレントを配置
    void place_treants() {
        vector<pair<int, int>> treant_positions;
        set<pair<int, int>> used_positions;
        vector<string> test_maze = maze;

        // 各予約済みマスの4近傍にトレントを配置
        for (const auto &[r, c] : reserved_cells) {
            for (int i = 0; i < 4; i++) {
                int tr = r + dr[i];
                int tc = c + dc[i];

                // 配置可能な位置かチェック
                if (tr >= 0 && tr < N && tc >= 0 && tc < N &&
                    test_maze[tr][tc] == '.' &&
                    path_map[tr][tc] == -1 &&  // どの道にも属していない
                    !(tr == ti && tc == tj) && // 花の位置ではない
                    used_positions.find({tr, tc}) == used_positions.end() &&
                    should_place_treant(tr, tc, test_maze)) {

                    // 仮配置して到達可能性をチェック
                    test_maze[tr][tc] = 'T';
                    if (check_reachability(0, N / 2, test_maze)) {
                        treant_positions.push_back({tr, tc});
                        used_positions.insert({tr, tc});
                    } else {
                        test_maze[tr][tc] = '.'; // 配置を取り消し
                    }
                }
            }
        }

        // トレントリストを更新
        for (const auto &pos : treant_positions) {
            placed_treants.push_back(pos);
        }
    }

    // トレントのリストを取得
    vector<pair<int, int>> get_treants() const { return placed_treants; }
};

int main() {
    cin >> N >> ti >> tj;
    current_maze.resize(N);
    confirmed.assign(N, vector<bool>(N, false));

    for (int i = 0; i < N; ++i) {
        cin >> current_maze[i];
    }

    // 初期状態
    int pi = 0;
    int pj = N / 2;
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

        // 初回のみ道とトレントを配置
        if (placed_treants.empty()) {
            MazeGenerator generator(N, ti, tj, current_maze);
            generator.generate_paths(pi, pj);
            vector<pair<int, int>> treants = generator.get_treants();

            cout << treants.size();
            for (const auto &p : treants) {
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