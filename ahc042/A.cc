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
double TIME_LIMIT = 190.0;
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

int N;
vector<string> C;
string direction = "RULD";
int best_hand;

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
    Pos operator*(const int x) {
        Pos rtn;
        rtn.h = h * x;
        rtn.w = w * x;
        return rtn;
    }
};
Pos d4[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

struct Hand {
    int dir;
    int idx;
    double ev;

    bool operator<(const Hand &in) const { return ev < in.ev; };
};

struct Grid {
    vector<string> board;
    vector<int> ans_d, ans_i;
    int score = 0;
    double ev;

    void init() { board = C; }

    bool present_oni(int dir, int idx) {
        if (dir == 0 || dir == 2) {
            rep(i, N) {
                if (board[idx][i] == 'x') {
                    return true;
                }
            }
        } else if (dir == 1 || dir == 3) {
            rep(i, N) {
                if (board[i][idx] == 'x') {
                    return true;
                }
            }
        }
        return false;
    }
    bool movable(int dir, int idx, vector<string> &bo) {
        if (dir == 2) {
            // L
            if (bo[idx][0] != 'o') {
                rep(i, N - 1) { bo[idx][i] = bo[idx][i + 1]; }
                bo[idx][N - 1] = '.';
            } else {
                return false;
            }
        } else if (dir == 1) {
            // U
            if (bo[0][idx] != 'o') {
                rep(i, N - 1) { bo[i][idx] = bo[i + 1][idx]; }
                bo[N - 1][idx] = '.';
            } else {
                return false;
            }

        } else if (dir == 0) {
            // R
            if (bo[idx][N - 1] != 'o') {
                rep(i, N - 1) { bo[idx][N - 1 - i] = bo[idx][N - 2 - i]; }
                bo[idx][0] = '.';
            } else {
                return false;
            }
        } else {
            // D
            if (bo[N - 1][idx] != 'o') {
                rep(i, N - 1) { bo[N - 1 - i][idx] = bo[N - 2 - i][idx]; }
                bo[0][idx] = '.';
            } else {
                return false;
            }
        }
        return true;
    }
    bool none_oni() {
        // cout << "none_oni" << endl;
        rep(i, N) {
            rep(j, N) {
                if (board[i][j] == 'x') {
                    return false;
                }
            }
        }
        return true;
    }
    bool random() {
        // cout << "random" << endl;
        while (ans_d.size() < best_hand) {
            int dir = mt() % 4;
            int idx = mt() % N;
            while (!present_oni(dir, idx)) {
                dir = mt() % 4;
                idx = mt() % N;
            }
            if (move(dir, idx)) {
                // cout << direction[dir] SP << idx << endl;
                // rep(i, N) { cout << board[i] << endl; }
                if (none_oni()) {
                    calc_score();
                    return true;
                }
            }
        }
        return false;
    }
    double eval(int dir, int idx) {
        // 鬼の残り数が少ないほうがいい
        // 福が一人でもいなくなったら-∞
        // 直で出られる画面端までの距離が短いほうがいい
        vector<string> tmp = board;
        if (!movable(dir, idx, tmp)) {
            return imax;
        }
        double oni_ev = 0.0;
        rep(i, N) {
            rep(j, N) {
                if (tmp[i][j] == 'x') {
                    oni_ev += 0.1;
                    int dist = N;
                    Pos cpos = {i, j};
                    Pos npos;
                    rep(k, 4) {
                        int l = 1;
                        int blo = 0;
                        npos = cpos + d4[k] * l;
                        while (!npos.is_oob()) {
                            if (tmp[npos.h][npos.w] == 'o') {
                                blo += 2;
                            }
                            if (dist <= l + blo) {
                                l = N;
                                break;
                            }
                            l++;
                            npos = cpos + d4[k] * l;
                        }
                        dist = min(dist, l + blo);
                    }
                    oni_ev += sqrt(dist);
                    // cout << oni_ev SP << dist SP;
                }
            }
        }
        return oni_ev;
    }
    double grid_eval() {
        double oni_ev = 0.0;
        rep(i, N) {
            rep(j, N) {
                if (board[i][j] == 'x') {
                    oni_ev += 0.1;
                    int dist = N;
                    Pos cpos = {i, j};
                    Pos npos;
                    rep(k, 4) {
                        int l = 1;
                        int blo = 0;
                        npos = cpos + d4[k] * l;
                        while (!npos.is_oob()) {
                            if (board[npos.h][npos.w] == 'o') {
                                blo += 2;
                            }
                            if (dist <= l + blo) {
                                l = N;
                                break;
                            }
                            l++;
                            npos = cpos + d4[k] * l;
                        }
                        dist = min(dist, l + blo);
                    }
                    oni_ev += sqrt(dist);
                    // cout << oni_ev SP << dist SP;
                }
            }
        }
        return oni_ev;
    }
    bool all_all_hands() {
        rep(lp, 4 * N * N) {
            all_hands();
            // rep(i, N) { cout << board[i] << endl; }
            if (none_oni()) {
                // print_board();
                calc_score();
                return true;
            }
        }
        // print_ans();
        // print_board();
        // exit(0);
        return false;
    }
    bool move_by_hand(Hand hand) { return move(hand.dir, hand.idx); }
    vector<Hand> beam() {
        vector<Hand> hands;
        rep(dir, 4) {
            rep(idx, N) {
                double ev = eval(dir, idx);
                // cout << dir SP << idx SP << cur_eval << endl;
                hands.push_back({dir, idx, ev});
            }
        }
        sort(all(hands));
        return hands;
    }
    void all_hands() {
        double best_eval = imax;
        int best_dir;
        int best_idx;
        double cur_eval;
        rep(dir, 4) {
            rep(idx, N) {
                cur_eval = eval(dir, idx);
                // cout << dir SP << idx SP << cur_eval << endl;
                if (best_eval > cur_eval) {
                    best_eval = cur_eval;
                    best_dir = dir;
                    best_idx = idx;
                }
            }
        }
        assert(move(best_dir, best_idx));
    }
    bool move(int dir, int idx) {
        // cout << "move" << endl;
        if (dir == 2) {
            // L
            if (board[idx][0] != 'o') {
                rep(i, N - 1) { board[idx][i] = board[idx][i + 1]; }
                board[idx][N - 1] = '.';
            } else {
                return false;
            }
        } else if (dir == 1) {
            // U
            if (board[0][idx] != 'o') {
                rep(i, N - 1) { board[i][idx] = board[i + 1][idx]; }
                board[N - 1][idx] = '.';
            } else {
                return false;
            }

        } else if (dir == 0) {
            // R
            if (board[idx][N - 1] != 'o') {
                rep(i, N - 1) { board[idx][N - 1 - i] = board[idx][N - 2 - i]; }
                board[idx][0] = '.';
            } else {
                return false;
            }
        } else {
            // D
            if (board[N - 1][idx] != 'o') {
                rep(i, N - 1) { board[N - 1 - i][idx] = board[N - 2 - i][idx]; }
                board[0][idx] = '.';
            } else {
                return false;
            }
        }
        ans_d.push_back(dir);
        ans_i.push_back(idx);
        return true;
    }

    void calc_score() {
        int sco = 8 * N * N - ans_d.size();
        score = sco;
    }
    void print_board() {
        rep(i, N) { cout << board[i] << endl; }
    }
    void print_ans() {
        assert(ans_d.size() == ans_i.size());
        assert(ans_d.size() <= 4 * N * N);
        rep(i, ans_d.size()) {
            cout << direction[ans_d[i]] SP << ans_i[i] << endl;
        }
    }
    bool operator<(const Grid &in) const { return ev < in.ev; };
};

void inpt() {
    cin >> N;
    best_hand = 4 * N * N;
    C.resize(N);
    rep(i, N) { cin >> C[i]; }
}

int main() {
    inpt();
    Grid best;
    best.init();

    int BEAM_WIDTH = 20;
    vector<Grid> bests = {best};
    rep(lp, 4 * N * N) {
        vector<Grid> grids;
        rep(i, bests.size()) {
            vector<Hand> hands = bests[i].beam();
            rep(j, min(int(hands.size()), BEAM_WIDTH)) {
                // cout << i SP << j << endl;
                Grid grid = bests[i];
                if (grid.move_by_hand(hands[j])) {
                    grid.ev = grid.grid_eval();
                    if (grid.none_oni()) {
                        grid.print_ans();
                        return 0;
                    }
                    grids.push_back(grid);
                }
            }
        }
        sort(all(grids));
        bests.clear();
        rep(i, min(int(grids.size()), BEAM_WIDTH)) {
            bests.push_back(grids[i]);
        }
    }
    return 0;

    Grid grid;
    grid.init();
    grid.random();
    grid.print_ans();
    return 0;
    int loop = 0;
    while (timer.progress() < 1) {
        loop++;
        // cout << loop << endl;

        Grid grid;
        grid.init();
        while (!grid.all_all_hands()) {
        }
        if (best.score < grid.score) {
            best = grid;
            cerr << "loop: " << loop << endl;
            // best.print_ans();
            cerr << "score: " << grid.score << endl;
        }
    }
    // cout<< space.score SP << space.score*25 <<endl;
    best.print_ans();

    return 0;
}
