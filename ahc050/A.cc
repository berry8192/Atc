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

int N, M;
vector<string> S;

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
vector<Pos> d4 = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

// struct Robot {
//     Pos pos;
//     double prob;

//     Robot() {};
//     Robot(Pos p, double pr) {
//         pos = p;
//         prob = pr;
//     }

//     void print() {
//         cout << "Robot at (" << pos.h << ", " << pos.w << ") with prob " <<
//         prob
//              << endl;
//     }
// };

struct Grid {
    vector<string> board;                    // ボードの状態
    map<Pos, double> robots;                 // ロボットの位置と確率
    vector<Pos> p;                           // 回答の列P
    double remain_robots;                    // 残っているロボットの期待値
    double score;                            // スコア
    vector<vector<vector<Pos>>> landing_pos; // [h][w][dir] -> landing position

    Grid(vector<string> &input_board) {
        board = input_board;
        remain_robots = 1.0;
        score = 0.0;
        landing_pos.resize(N, vector<vector<Pos>>(N, vector<Pos>(4)));
        gen_initial_answer();
        calc_initial_robots();
        calc_landing_positions();
    }

    void gen_initial_answer() {
        rep(i, N) {
            rep(j, N) {
                if (board[i][j] == '.') {
                    p.emplace_back(i, j);
                }
            }
        }
        shuffle(p.begin(), p.end(), mt);
    }
    void calc_initial_robots() {
        robots.clear();
        int total_empty = N * N - M;
        rep3(i, N + 1, -1) {
            rep3(j, N + 1, -1) {
                if (i < 0 || j < 0 || i >= N || j >= N || board[i][j] == '#') {
                    for (const Pos &dir : d4) {
                        int consecutive_empty = 0;
                        Pos reverse_dir(-dir.h, -dir.w);
                        Pos target(i - dir.h, j - dir.w);
                        if (target.is_oob() ||
                            board[target.h][target.w] == '#') {
                            continue; // 障害物があるか、範囲外ならスキップ
                        }

                        Pos current = target;

                        while (!current.is_oob() &&
                               board[current.h][current.w] == '.') {
                            consecutive_empty++;
                            current = current + reverse_dir;
                        }
                        robots[target] +=
                            (consecutive_empty * 1.0 / total_empty) * 0.25;
                    }
                }
            }
        }
    }
    void calc_landing_positions() {
        rep(i, N) {
            rep(j, N) {
                if (board[i][j] == '.') {
                    rep(dir_idx, 4) {
                        Pos current(i, j);
                        Pos dir = d4[dir_idx];
                        Pos next = current + dir;
                        while (!next.is_oob() && board[next.h][next.w] == '.') {
                            current = next;
                            next = current + dir;
                        }
                        landing_pos[i][j][dir_idx] = current;
                    }
                }
            }
        }
    }
    void update_landing_positions(Pos rock_pos) {
        // 岩が置かれた位置の影響を受ける範囲を更新
        rep(dir_idx, 4) {
            Pos dir = d4[dir_idx];
            Pos reverse_dir(-dir.h, -dir.w);

            // 岩の位置から逆方向に進んで影響を受ける位置を更新
            Pos current = rock_pos + reverse_dir;
            while (!current.is_oob() && board[current.h][current.w] == '.') {
                // この位置からdir方向の着地点を再計算
                Pos calc_pos = current;
                Pos next = calc_pos + dir;
                while (!next.is_oob() && board[next.h][next.w] == '.') {
                    calc_pos = next;
                    next = calc_pos + dir;
                }
                landing_pos[current.h][current.w][dir_idx] = calc_pos;
                current = current + reverse_dir;
            }
        }
    }
    void move_robot() {
        vector<vector<double>> prob(N, vector<double>(N, 0.0));
        for (const auto &robot : robots) {
            Pos pos = robot.first;
            double prob_value = robot.second;

            rep(dir_idx, 4) {
                Pos landing = landing_pos[pos.h][pos.w][dir_idx];
                prob[landing.h][landing.w] += prob_value * 0.25;
            }
        }
        robots.clear();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == '.' && prob[i][j] > 0.0) {
                    robots[{i, j}] = prob[i][j];
                }
            }
        }
    }
    void fall_rock(int turn) {
        Pos rock_pos = p[turn];
        board[rock_pos.h][rock_pos.w] = '#';
        if (robots.find(rock_pos) != robots.end()) {
            double prob_value = robots[rock_pos];
            remain_robots -= prob_value;
            robots.erase(rock_pos);
        }
        update_landing_positions(rock_pos);
    }
    void greed_rock(int turn) {
        Pos min_robots_pos;
        double min_robots = imax;
        bool found = false;
        rep(i, N) {
            rep(j, N) {
                if (robots.find({i, j}) != robots.end()) {
                    double prob_value = robots[{i, j}];
                    if (prob_value < min_robots) {
                        min_robots = prob_value;
                        min_robots_pos = {i, j};
                    }
                } else if (board[i][j] == '.') {
                    min_robots = 0.0;
                    min_robots_pos = {i, j};
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }
        // cout << min_robots << endl;
        p[turn] = min_robots_pos;
        fall_rock(turn);
    }
    void greed_rock_surrounded(int turn) {
        Pos best_pos;
        double best_score = -1e9;
        bool found = false;

        // Calculate turn ratio (0.0 at start, 1.0 at end)
        double turn_ratio = (double)turn / (N * N - M - 1);
        // Early turn penalty factor (higher penalty in early turns)
        double early_penalty = (1.0 - turn_ratio) * 5000.0;

        rep(i, N) {
            rep(j, N) {
                if (board[i][j] != '.')
                    continue;

                Pos pos(i, j);
                double robot_prob = 0.0;
                if (robots.find(pos) != robots.end()) {
                    robot_prob = robots[pos];
                }

                // Count surrounding walls/rocks (higher is better)
                int wall_count = count_surrounding_walls(pos);

                // Calculate score: prioritize high wall count and low robot
                // probability Apply stronger penalty for robot probability in
                // early turns
                double score =
                    wall_count * 10.0 - robot_prob * (1000.0 + early_penalty);

                if (!found || score > best_score) {
                    best_score = score;
                    best_pos = pos;
                    found = true;
                }
            }
        }

        p[turn] = best_pos;
        fall_rock(turn);
    }

    int count_surrounding_walls(Pos pos) {
        int wall_count = 0;
        for (const Pos &dir : d4) {
            Pos neighbor = pos + dir;
            if (neighbor.is_oob() || board[neighbor.h][neighbor.w] == '#') {
                wall_count++;
            }
        }
        return wall_count;
    }

    void progress_turn(int turn) {
        greed_rock_surrounded(turn); // Use the new surrounded-aware strategy
        move_robot();
        score += remain_robots;
    }

    void print_ans() {
        for (const Pos &pos : p) {
            cout << pos.h << " " << pos.w << endl;
        }
    }
};

Pos itop(int idx) { return {idx / N, idx % N}; }

void inpt() {
    cin >> N >> M;
    S.resize(N);
    rep(i, N) { cin >> S[i]; }
}

void simple() {
    rep(i, N) {
        rep(j, N) {
            if (S[i][j] == '.') {
                cout << i << " " << j << endl;
            }
        }
    }
    exit(0);
}

int main() {
    inpt();
    Grid grid(S);
    rep(i, N * N - M) { grid.progress_turn(i); }
    grid.print_ans();
    cerr << "Score: " << grid.score * 1000000 / (N * N - M - 1) << endl;
    return 0;

    int loop = 0;
    while (1) {
        current = chrono::system_clock::now();
        if (chrono::duration_cast<chrono::milliseconds>(current - start)
                .count() > TIME_LIMIT) {
            // break;
        }
        loop++;
    }
    // cout<< space.score SP << space.score*25 <<endl;
    // best.print_ans();

    return 0;
}
