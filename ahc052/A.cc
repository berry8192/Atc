#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

using namespace std;
// using namespace atcoder;

// std::ofstream outputFile("log.csv");

// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) outputFile << pvv[i] << ", ";
// 	outputFile<< pvv[pvv.size()-1] <<endl;
// }
// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) cout << pvv[i] << ", ";
// 	// rep(i, pvv.size()-1) cout<< pvv[i]/20 SP << pvv[i]%20 <<endl;
// 	cout<< pvv[pvv.size()-1] <<endl;
// }

// template <class T>void PVV(T pvv) {
// 	rep(i, pvv.size()){
//         // outputFile<< "i: " << i <<endl;
// 		rep(j, pvv[i].size()-1){
// 			outputFile<< pvv[i][j] << ", ";
// 		}
// 		if(pvv[i].size()) outputFile<< pvv[i][pvv[i].size()-1] <<endl;
// 	}
// }
// template <class T> void PM(T pm) {
//     // cout<< "{";
// 	for(auto m : pm){
// 		outputFile<< "(" << m.first << "->" << m.second << "), ";
// 	}
// 	// cout<< "}";
// 	outputFile<<endl;
// }

int imax = 2147483647;
long long llimax = 9223372036854775807;

// 焼きなましの定数
chrono::system_clock::time_point start, current;
double TIME_LIMIT = 2000.0;
// double TIME_LIMIT=190.0;
double start_temp = 10000000.0;
double end_temp = 10000.0;

struct Timer {
    chrono::_V2::system_clock::time_point start;

    Timer() { start = chrono::system_clock::now(); }
    double progress() {
        chrono::_V2::system_clock::time_point current =
            chrono::system_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(current - start)
                   .count() /
               TIME_LIMIT;
    }
};
Timer timer;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed = 1;
mt19937 mt(seed);

int N, M, K;
vector<string> v_walls;               // 縦の壁
vector<string> h_walls;               // 横の壁
vector<vector<int>> precomputed_dist; // 前計算した距離

// 前計算で全マス間の最短距離を計算
void precompute_distances() {
    precomputed_dist.assign(N * N, vector<int>(N * N, N * N));

    // 各マスから隣接マスへの距離を設定
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int idx = i * N + j;
            precomputed_dist[idx][idx] = 0;

            // 4方向をチェック
            vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for (auto dir : dirs) {
                int di = dir.first;
                int dj = dir.second;
                int ni = i + di;
                int nj = j + dj;

                if (ni >= 0 && ni < N && nj >= 0 && nj < N) {
                    bool has_wall_between = false;

                    if (di == 0) { // 横移動
                        int min_j = min(j, nj);
                        has_wall_between = v_walls[i][min_j] == '1';
                    } else { // 縦移動
                        int min_i = min(i, ni);
                        has_wall_between = h_walls[min_i][j] == '1';
                    }

                    if (!has_wall_between) {
                        int nidx = ni * N + nj;
                        precomputed_dist[idx][nidx] = 1;
                    }
                }
            }
        }
    }

    // Floyd-Warshall法で全マス間の最短距離を計算
    for (int k = 0; k < N * N; k++) {
        for (int i = 0; i < N * N; i++) {
            for (int j = 0; j < N * N; j++) {
                if (precomputed_dist[i][k] + precomputed_dist[k][j] <
                    precomputed_dist[i][j]) {
                    precomputed_dist[i][j] =
                        precomputed_dist[i][k] + precomputed_dist[k][j];
                }
            }
        }
    }
}

// 構造体
struct Pos {
    int h;
    int w;

    Pos() {};
    Pos(int hh, int ww) {
        h = hh;
        w = ww;
    }

    bool is_oob() {
        // assert(0<=h);
        // assert(h<n);
        // assert(0<=w);
        // assert(w<=h);
        return !(0 <= h && h < N && 0 <= w && w < N);
    }
    int manhattan(Pos pos) { return abs(h - pos.h) + abs(w - pos.w); }
    int index() { return h * N + w; }
    void print() { cout << "(" << h << ", " << w << ")" << endl; }
    // 受け取った近傍でPosを作る
    vector<Pos> around_pos(const vector<Pos> &dir) {
        vector<Pos> rtn;
        Pos new_pos;
        for (int i = 0; i < dir.size(); i++) {
            new_pos = {h + dir[i].h, w + dir[i].w};
            if (!new_pos.is_oob())
                rtn.emplace_back(new_pos);
        }
        return rtn;
    }

    bool operator<(const Pos &in) const {
        return h != in.h ? h < in.h : w < in.w;
    };
    bool operator==(const Pos &cpos) const {
        return (h == cpos.h && w == cpos.w);
    };
    Pos operator+(const Pos pos) {
        Pos rtn;
        rtn.h = h + pos.h;
        rtn.w = w + pos.w;
        return rtn;
    }
    Pos operator-(const Pos pos) {
        Pos rtn;
        rtn.h = h - pos.h;
        rtn.w = w - pos.w;
        return rtn;
    }
};
vector<Pos> robots;

// 前計算した距離を取得
int get_distance(Pos from, Pos to) {
    return precomputed_dist[from.index()][to.index()];
}

struct Grid {
    vector<Pos> robot_pos; // 各ロボットの現在位置
    vector<vector<int>>
        board; // 各マスの状態 (0: 未塗装, -1: 塗装済み, 1-M: ロボットが存在)
    vector<vector<char>>
        button_config;       // [button_id][robot_id] -> action (U/D/L/R/S)
    vector<char> operations; // 操作列 (押すボタンの番号)

    Grid() {
        robot_pos.resize(M);
        board.assign(N, vector<int>(N, 0));
        button_config.assign(K, vector<char>(M, 'U'));
        operations.clear();
    }

    // ロボットの初期位置を設定
    void init_robots() {
        for (int i = 0; i < M; i++) {
            robot_pos[i] = robots[i];
            // 初期位置にロボットを配置（1-indexed）
            board[robot_pos[i].h][robot_pos[i].w] = i + 1;
        }
    }

    // ボタンの設定を行う
    void set_button(int button_id, int robot_id, char action) {
        button_config[button_id][robot_id] = action;
    }

    // 操作を追加
    void add_operation(char button_id) { operations.push_back(button_id); }

    // ボタン設定を出力
    void output_config() {
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < M; j++) {
                cout << button_config[i][j] << " ";
            }
            cout << endl;
        }
    }

    // 操作列を出力
    void output_operations() {
        for (char op : operations) {
            cout << op << endl;
        }
    }

    // ランダムに操作列を設定（各ロボットにUDLRを必ず1つ以上含む）
    void setup_random_config() {
        vector<char> actions = {'U', 'D', 'L', 'R'};

        for (int robot_id = 0; robot_id < M; robot_id++) {
            // 各ロボットに対してUDLRを必ず1つ以上割り当て
            vector<int> assigned_buttons;
            for (char action : actions) {
                int button_id = mt() % K;
                button_config[button_id][robot_id] = action;
                assigned_buttons.push_back(button_id);
            }

            // 残りのボタンにランダムな行動を割り当て
            for (int button_id = 0; button_id < K; button_id++) {
                bool already_assigned = false;
                for (int assigned : assigned_buttons) {
                    if (button_id == assigned) {
                        already_assigned = true;
                        break;
                    }
                }
                if (!already_assigned) {
                    button_config[button_id][robot_id] = actions[mt() % 4];
                }
            }
        }
    }

    // 全ロボットに8パターンの変換を適用したキーコンフィグを設定
    void setup_random_config_same() {
        vector<char> actions = {'U', 'D', 'L', 'R'};

        // 基本設定を作成
        vector<char> base_config(K);

        // UDLR を必ず1つ以上含むように設定
        vector<int> assigned_buttons;
        for (char action : actions) {
            int button_id = mt() % K;
            base_config[button_id] = action;
            assigned_buttons.push_back(button_id);
        }

        // 残りのボタンにランダムな行動を割り当て
        for (int button_id = 0; button_id < K; button_id++) {
            bool already_assigned = false;
            for (int assigned : assigned_buttons) {
                if (button_id == assigned) {
                    already_assigned = true;
                    break;
                }
            }
            if (!already_assigned) {
                base_config[button_id] = actions[mt() % 4];
            }
        }

        // 変換関数
        auto transform_config = [&](const vector<char> &config,
                                    int pattern) -> vector<char> {
            vector<char> result = config;
            for (int i = 0; i < K; i++) {
                char original = config[i];
                char transformed;

                switch (pattern) {
                case 0: // 元の状態
                    transformed = original;
                    break;
                case 1: // 90度回転 (U->R, R->D, D->L, L->U)
                    if (original == 'U')
                        transformed = 'R';
                    else if (original == 'R')
                        transformed = 'D';
                    else if (original == 'D')
                        transformed = 'L';
                    else if (original == 'L')
                        transformed = 'U';
                    break;
                case 2: // 180度回転 (U->D, D->U, L->R, R->L)
                    if (original == 'U')
                        transformed = 'D';
                    else if (original == 'D')
                        transformed = 'U';
                    else if (original == 'L')
                        transformed = 'R';
                    else if (original == 'R')
                        transformed = 'L';
                    break;
                case 3: // 270度回転 (U->L, L->D, D->R, R->U)
                    if (original == 'U')
                        transformed = 'L';
                    else if (original == 'L')
                        transformed = 'D';
                    else if (original == 'D')
                        transformed = 'R';
                    else if (original == 'R')
                        transformed = 'U';
                    break;
                case 4: // 垂直軸反転 (U->D, D->U, L->L, R->R)
                    if (original == 'U')
                        transformed = 'D';
                    else if (original == 'D')
                        transformed = 'U';
                    else
                        transformed = original;
                    break;
                case 5: // 水平軸反転 (U->U, D->D, L->R, R->L)
                    if (original == 'L')
                        transformed = 'R';
                    else if (original == 'R')
                        transformed = 'L';
                    else
                        transformed = original;
                    break;
                case 6: // 対角線反転1 (U->L, L->U, D->R, R->D)
                    if (original == 'U')
                        transformed = 'L';
                    else if (original == 'L')
                        transformed = 'U';
                    else if (original == 'D')
                        transformed = 'R';
                    else if (original == 'R')
                        transformed = 'D';
                    break;
                case 7: // 対角線反転2 (U->R, R->U, D->L, L->D)
                    if (original == 'U')
                        transformed = 'R';
                    else if (original == 'R')
                        transformed = 'U';
                    else if (original == 'D')
                        transformed = 'L';
                    else if (original == 'L')
                        transformed = 'D';
                    break;
                }
                result[i] = transformed;
            }
            return result;
        };

        // 8台のロボットに8パターンを適用
        for (int robot_id = 0; robot_id < min(8, M); robot_id++) {
            vector<char> config = transform_config(base_config, robot_id);
            for (int button_id = 0; button_id < K; button_id++) {
                button_config[button_id][robot_id] = config[button_id];
            }
        }

        // 余った2台は別途適当にUDLRを割り当て
        for (int robot_id = 8; robot_id < M; robot_id++) {
            vector<int> extra_assigned_buttons;
            for (char action : actions) {
                int button_id = mt() % K;
                button_config[button_id][robot_id] = action;
                extra_assigned_buttons.push_back(button_id);
            }

            for (int button_id = 0; button_id < K; button_id++) {
                bool already_assigned = false;
                for (int assigned : extra_assigned_buttons) {
                    if (button_id == assigned) {
                        already_assigned = true;
                        break;
                    }
                }
                if (!already_assigned) {
                    button_config[button_id][robot_id] = actions[mt() % 4];
                }
            }
        }
    }

    // スコアを計算する関数
    int calculate_score() {
        int empty_count = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == 0) {
                    empty_count++;
                }
            }
        }

        int T = operations.size();
        if (empty_count == 0) {
            return 3 * N * N - T; // R=0の場合
        } else {
            return N * N - empty_count; // R>0の場合
        }
    }

    // 状態をリセットする関数
    void reset() {
        robot_pos.clear();
        robot_pos.resize(M);
        board.assign(N, vector<int>(N, 0));
        operations.clear();
    }

    // 現在の状態をコピーする関数
    Grid copy() {
        Grid new_grid;
        new_grid.robot_pos = robot_pos;
        new_grid.board = board;
        new_grid.button_config = button_config;
        new_grid.operations = operations;
        return new_grid;
    }

    // 最適化されたsolve関数（シミュレーション用）
    int solve_simulation(int best_operations = INT_MAX) {
        init_robots();

        Pos current_target(-1, -1);
        int target_robot = -1;

        while (operations.size() < 2 * N * N) {
            // 現在の最良操作回数を上回ったら打ち切り
            if (operations.size() >= best_operations) {
                return -1; // スコア計算せずに早期終了
            }

            vector<Pos> empty_cells = find_empty_cells();
            if (empty_cells.empty())
                break;

            if (current_target.h == -1 ||
                board[current_target.h][current_target.w] != 0) {
                int best_robot = 0;
                Pos best_target = empty_cells[0];
                int min_distance = get_distance(robot_pos[0], empty_cells[0]);

                for (int i = 0; i < M; i++) {
                    for (const Pos &empty_cell : empty_cells) {
                        int dist = get_distance(robot_pos[i], empty_cell);
                        if (dist < min_distance) {
                            min_distance = dist;
                            best_robot = i;
                            best_target = empty_cell;
                        }
                    }
                }

                current_target = best_target;
                target_robot = best_robot;
            }

            int best_button = 0;
            int min_dist = N * N;

            for (int button_id = 0; button_id < K; button_id++) {
                Pos new_pos =
                    move_robot(robot_pos[target_robot],
                               button_config[button_id][target_robot]);
                int dist = get_distance(new_pos, current_target);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_button = button_id;
                }
            }

            execute_button(best_button);
        }

        return calculate_score();
    }

    // 時間制限付き最適化
    void solve_with_optimization() {
        // 初期解を生成
        setup_random_config_same();
        reset();
        int best_score = solve_simulation();
        vector<vector<char>> best_config = button_config;
        int best_operations_count = operations.size();

        cerr << "Initial score: " << best_score
             << " (operations: " << best_operations_count << ")" << endl;

        int iteration = 0;
        while (timer.progress() < 0.95) { // 95%の時間まで最適化
            iteration++;

            // 新しいランダム設定を試す
            setup_random_config_same();
            reset();
            int current_score = solve_simulation(best_operations_count);

            // 早期終了した場合はスキップ
            if (current_score == -1) {
                continue;
            }

            // より良いスコアの場合は更新
            if (current_score > best_score) {
                best_score = current_score;
                best_config = button_config;
                best_operations_count = operations.size();
                cerr << "Iteration " << iteration << ": New best score "
                     << best_score << " (operations: " << best_operations_count
                     << ")" << endl;
            }

            // 100回に1回進捗を出力
            if (iteration % 100 == 0) {
                cerr << "Iteration " << iteration << ": Current best "
                     << best_score << " (operations: " << best_operations_count
                     << ", progress: " << timer.progress() * 100 << "%)"
                     << endl;
            }
        }

        cerr << "Total iterations: " << iteration << endl;
        cerr << "Final best score: " << best_score
             << " (operations: " << best_operations_count << ")" << endl;

        // 最良の設定で最終実行
        button_config = best_config;
        reset();
        init_robots();

        Pos current_target(-1, -1);
        int target_robot = -1;

        while (operations.size() < 2 * N * N) {
            vector<Pos> empty_cells = find_empty_cells();
            if (empty_cells.empty())
                break;

            if (current_target.h == -1 ||
                board[current_target.h][current_target.w] != 0) {
                int best_robot = 0;
                Pos best_target = empty_cells[0];
                int min_distance = get_distance(robot_pos[0], empty_cells[0]);

                for (int i = 0; i < M; i++) {
                    for (const Pos &empty_cell : empty_cells) {
                        int dist = get_distance(robot_pos[i], empty_cell);
                        if (dist < min_distance) {
                            min_distance = dist;
                            best_robot = i;
                            best_target = empty_cell;
                        }
                    }
                }

                current_target = best_target;
                target_robot = best_robot;
            }

            int best_button = 0;
            int min_dist = N * N;

            for (int button_id = 0; button_id < K; button_id++) {
                Pos new_pos =
                    move_robot(robot_pos[target_robot],
                               button_config[button_id][target_robot]);
                int dist = get_distance(new_pos, current_target);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_button = button_id;
                }
            }

            execute_button(best_button);
        }
    }

    // 解く（最適化版を使用）
    void solve() { solve_with_optimization(); }

    // 壁があるかチェック
    bool has_wall(Pos from, Pos to) {
        if (from.h == to.h) {
            // 横移動
            int min_w = min(from.w, to.w);
            return v_walls[from.h][min_w] == '1';
        } else {
            // 縦移動
            int min_h = min(from.h, to.h);
            return h_walls[min_h][from.w] == '1';
        }
    }

    // ロボットを移動（壁チェック付き）
    Pos move_robot(Pos pos, char action) {
        Pos new_pos = pos;
        if (action == 'U')
            new_pos.h--;
        else if (action == 'D')
            new_pos.h++;
        else if (action == 'L')
            new_pos.w--;
        else if (action == 'R')
            new_pos.w++;

        if (new_pos.is_oob() || has_wall(pos, new_pos)) {
            return pos; // 移動できない場合は元の位置
        }
        return new_pos;
    }

    // 最も近いロボットを見つける（前計算した距離を利用）
    int find_nearest_robot(Pos target) {
        int best_robot = 0;
        int min_dist = get_distance(robot_pos[0], target);

        for (int i = 1; i < M; i++) {
            int dist = get_distance(robot_pos[i], target);
            if (dist < min_dist) {
                min_dist = dist;
                best_robot = i;
            }
        }
        return best_robot;
    }

    // 空きマスを探す
    vector<Pos> find_empty_cells() {
        vector<Pos> empty_cells;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == 0) {
                    empty_cells.push_back(Pos(i, j));
                }
            }
        }
        return empty_cells;
    }

    // ボタンを押してロボットを移動
    void execute_button(int button_id) {
        // 現在のロボット位置をクリア
        for (int i = 0; i < M; i++) {
            if (board[robot_pos[i].h][robot_pos[i].w] > 0) {
                board[robot_pos[i].h][robot_pos[i].w] = -1;
            }
        }

        // 各ロボットを移動
        for (int i = 0; i < M; i++) {
            robot_pos[i] =
                move_robot(robot_pos[i], button_config[button_id][i]);
            board[robot_pos[i].h][robot_pos[i].w] = i + 1;
        }

        operations.push_back('0' + button_id);
    }
};

Pos itop(int idx) { return {idx / N, idx % N}; }

Pos d4[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

void inpt() {
    cin >> N >> M >> K;

    // ロボットの初期位置を読み込み
    robots.resize(M);
    for (int i = 0; i < M; i++) {
        cin >> robots[i].h >> robots[i].w;
    }

    // 縦の壁を読み込み
    v_walls.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> v_walls[i];
    }

    // 横の壁を読み込み
    h_walls.resize(N - 1);
    for (int i = 0; i < N - 1; i++) {
        cin >> h_walls[i];
    }
}

int main() {
    inpt();
    precompute_distances();

    Grid grid;
    grid.solve();
    grid.output_config();
    grid.output_operations();

    return 0;
}
