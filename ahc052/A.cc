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
        board.assign(N, vector<int>(N));
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
                cout << button_config[i][j];
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

    return 0;
}
