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
double TIME_LIMIT = 1900.0;
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
vector<string> v_walls; // 縦の壁
vector<string> h_walls; // 横の壁

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

    // 最も近いロボットを見つける（BFSで壁を考慮）
    int find_nearest_robot(Pos target) {
        int best_robot = 0;
        int min_dist = bfs_distance(robot_pos[0], target);

        for (int i = 1; i < M; i++) {
            int dist = bfs_distance(robot_pos[i], target);
            if (dist < min_dist) {
                min_dist = dist;
                best_robot = i;
            }
        }
        return best_robot;
    }

    // BFSで壁を考慮した距離を計算
    int bfs_distance(Pos start, Pos goal) {
        if (start == goal)
            return 0;

        vector<vector<int>> dist(N, vector<int>(N, -1));
        queue<Pos> q;

        q.push(start);
        dist[start.h][start.w] = 0;

        while (!q.empty()) {
            Pos current = q.front();
            q.pop();

            // 4方向に移動を試す
            vector<char> directions = {'U', 'D', 'L', 'R'};
            for (char dir : directions) {
                Pos next = move_robot(current, dir);

                // 移動できた場合（壁がない場合）
                if (!(next == current) && dist[next.h][next.w] == -1) {
                    dist[next.h][next.w] = dist[current.h][current.w] + 1;
                    q.push(next);

                    if (next == goal) {
                        return dist[next.h][next.w];
                    }
                }
            }
        }

        // 到達不可能な場合は大きな値を返す
        return N * N;
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

    // 解く
    void solve() {
        setup_random_config();
        init_robots();

        Pos current_target(-1, -1); // 現在のターゲット
        int target_robot = -1;      // ターゲットを担当するロボット

        while (operations.size() < 2 * N * N) {
            vector<Pos> empty_cells = find_empty_cells();
            if (empty_cells.empty())
                break;

            // 現在のターゲットが塗られているか、初回の場合は新しいターゲットを選択
            if (current_target.h == -1 ||
                board[current_target.h][current_target.w] != 0) {
                // ランダムな空きマスを選択
                current_target = empty_cells[mt() % empty_cells.size()];
                target_robot = find_nearest_robot(current_target);
            }

            // 担当ロボットをターゲットに向かわせるボタンを探す
            int best_button = 0;
            int min_dist = N * N;

            for (int button_id = 0; button_id < K; button_id++) {
                Pos new_pos =
                    move_robot(robot_pos[target_robot],
                               button_config[button_id][target_robot]);
                int dist = bfs_distance(new_pos, current_target);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_button = button_id;
                }
            }

            execute_button(best_button);
        }
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

    Grid grid;
    grid.solve();
    grid.output_config();
    grid.output_operations();

    return 0;
}
