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
template <class T> void PV(T pvv) {
    if (!pvv.size())
        return;
    rep(i, pvv.size() - 1) cout << pvv[i] << ", ";
    // rep(i, pvv.size()-1) cout<< pvv[i]/20 SP << pvv[i]%20 <<endl;
    cout << pvv[pvv.size() - 1] << endl;
}

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
double TIME_LIMIT = 2700.0;
// double TIME_LIMIT=190.0;
double start_temp = 10000000.0;
double end_temp = 10000.0;

struct Timer {
    chrono::system_clock::time_point start;

    Timer() { start = chrono::system_clock::now(); }
    double progress() {
        chrono::system_clock::time_point current = chrono::system_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(current - start)
                   .count() /
               TIME_LIMIT;
    }
};
Timer timer;

unsigned int randxor() {
    static unsigned int x = 123456789, y = 362436069, z = 521288629,
                        w = 88675123;
    unsigned int t;
    t = (x ^ (x << 11));
    x = y;
    y = z;
    z = w;
    return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}
template <typename T> T rand(T a, T b) {
    assert(a <= b);
    ll len = (b - a + 1);
    return randxor() % len + a;
}

// 乱数の準備
// auto seed=(unsigned)time(NULL);
// random_device rd;
// mt19937 mt(rd());

int N, M, V;
vector<string> s, t;
int rest_tako_masu;
vector<vector<bool>> def_masu, def_tako;

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

Pos itop(int idx) { return {idx / N, idx % N}; }

Pos d5[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}, {0, 0}};
string dir_char = "RULD.", dir_rot = "R.L";
map<char, int> mdir_char = {{'R', 0}, {'U', 1}, {'L', 2}, {'D', 3}, {'.', 4}};
map<char, int> mdir_rot = {{'R', -1}, {'.', 0}, {'L', 1}};

struct Grid {
    vector<string> ss, tt;
    vector<int> v;
    Pos ipos, pos, npos;
    vector<int> dir, ndir;
    vector<bool> has;
    vector<vector<bool>> tako;
    vector<vector<bool>> masu;
    vector<string> steps;
    int rest;

    Grid(const vector<string> &in_s, const vector<string> &in_t) {
        ss = in_s;
        tt = in_t;
        init_v();
        init_pos();
        tako = def_tako;
        masu = def_masu;
        dir.resize(V);
        ndir.resize(V);
        has.resize(V);
        rest = rest_tako_masu;
    }

    void init_v() {
        v.resize(V);
        rep(i, V - 1) { v[i + 1] = (i * N / (V * 2)) + 1; }
        // debug_print_v();
    }
    void init_v_random() {
        v.resize(V);
        vector<int> len(N);
        len[0] = imax;
        rep(i, V - 1) {
            int l = 0;
            while (len[l] > 1) {
                l = rand(1, N - 1);
            }
            len[l]++;
            v[i + 1] = l;
        }
        debug_print_v();
    }
    void init_pos() {
        ipos = {rand(0, N - 1), rand(0, N - 1)};
        pos = ipos;
    }
    char make_mov() {
        // cout << "make_mov" << endl;
        vector<int> tmp;
        rep(i, 4) {
            npos = pos + d5[i];
            if (!npos.is_oob()) {
                tmp.push_back(i);
            }
        }
        int sdir = tmp[rand(0, int(tmp.size() - 1))];
        // pos = pos + d5[sdir];
        npos = pos + d5[sdir];
        return dir_char[sdir];
    }
    Pos calc_leaf_pos(int idx) {
        // cout << "calc_leaf_pos " << (dir[idx] + add_dir + 4) % 4 << endl;
        return pos + d5[dir[idx]] * v[idx];
    }
    Pos calc_leaf_npos(int idx, int add_dir = 0) {
        // cout << "calc_leaf_npos " << (dir[idx] + add_dir + 4) % 4 << endl;
        Pos dd = d5[(dir[idx] + add_dir + 4) % 4];
        return npos + dd * v[idx];
    }
    Pos calc_leaf_npos_ndir(int idx) {
        // cout << "calc_leaf_npos_ndir " << (dir[idx] + add_dir + 4) % 4 <<
        // endl;
        return npos + d5[ndir[idx]] * v[idx];
    }
    string make_rot() {
        // cout << "make_rot" << endl;
        string rot;
        rep3(i, V, 1) {
            vector<int> tmp;
            for (int j = -1; j <= 1; j++) {
                Pos lpos = calc_leaf_npos(i, j);
                if (!lpos.is_oob()) {
                    tmp.push_back(j);
                }
            }
            if (tmp.empty()) {
                rot += 'L';
                // dir[i] = (dir[i] + 1) % 4;
                ndir[i] = (dir[i] + 1) % 4;
            } else {
                int rdir = tmp[rand(0, int(tmp.size() - 1))];
                rot += dir_rot[rdir + 1];
                // dir[i] = (dir[i] + rdir + 4) % 4;
                ndir[i] = (dir[i] + rdir + 4) % 4;
            }
        }
        return rot;
    }
    string make_P(set<int> &prog_pos) {
        // cout << "make_P" << endl;
        string p = ".";
        rep3(i, V, 1) {
            Pos lpos = calc_leaf_npos_ndir(i);
            if (!lpos.is_oob()) {
                if (has[i]) {
                    if (masu[lpos.h][lpos.w] &&
                        prog_pos.find(lpos.index()) == prog_pos.end()) {
                        p += 'P';
                        // masu[lpos.h][lpos.w] = false;
                        // has[i] = false;
                        // rest--;
                        prog_pos.insert(lpos.index());
                    } else {
                        p += '.';
                    }
                } else {
                    if (tako[lpos.h][lpos.w] &&
                        prog_pos.find(lpos.index()) == prog_pos.end()) {
                        p += 'P';
                        // tako[lpos.h][lpos.w] = false;
                        // has[i] = true;
                        // rest--;
                        prog_pos.insert(lpos.index());
                    } else {
                        p += '.';
                    }
                }
            } else {
                p += '.';
            }
        }
        return p;
    }
    void random_move() {
        // cout << "random_move" << endl;
        int best_prog = -1;
        string best_step;
        rep(i, 2 * V) {
            set<int> prog_pos;
            string step;
            step += make_mov();
            step += make_rot();
            step += make_P(prog_pos);
            int tmp = prog_pos.size();
            if (best_prog < tmp) {
                best_prog = tmp;
                best_step = step;
            }
        }
        exec_move(best_step);
        steps.push_back(best_step);
    }
    void exec_move(string step) {
        // cout << "exec_move " << step << endl;
        pos = pos + d5[mdir_char[step[0]]];
        rep3(i, V, 1) { dir[i] = (dir[i] + mdir_rot[step[i]] + 4) % 4; }
        rep3(i, V, 1) {
            Pos lpos = calc_leaf_pos(i);
            if (step[i + V] == 'P') {
                if (has[i]) {
                    masu[lpos.h][lpos.w] = false;
                    has[i] = false;
                } else {
                    tako[lpos.h][lpos.w] = false;
                    has[i] = true;
                }
                rest--;
            }
        }
        // cout << "exec move end" << endl;
    }

    void print_ans() {
        cout << v.size() << endl;
        rep3(i, v.size(), 1) { cout << "0 " << v[i] << endl; }
        cout << ipos.h SP << ipos.w << endl;
        rep(i, steps.size()) { cout << steps[i] << endl; }
    }
    void debug_print_v() {
        cout << v.size() << endl;
        rep3(i, v.size(), 1) { cout << "0 " << v[i] << endl; }
        cout << "0 0" << endl;
        exit(0);
    }
};

void calc_masu() {
    def_tako.resize(N, vector<bool>(N, false));
    def_masu.resize(N, vector<bool>(N, false));
    rep(i, N) {
        rep(j, N) {
            if (s[i][j] == '1' && t[i][j] == '0') {
                def_tako[i][j] = true;
                rest_tako_masu++;
            } else if (s[i][j] == '0' && t[i][j] == '1') {
                def_masu[i][j] = true;
                rest_tako_masu++;
            }
        }
    }
}

void inpt() {
    cin >> N >> M >> V;
    s.resize(N);
    t.resize(N);
    rep(i, N) { cin >> s[i]; }
    rep(i, N) { cin >> t[i]; }
    calc_masu();
}

void zero_tree() {
    cout << 1 << endl;

    rep(i, N) {
        rep(j, N) {
            if (s[i][j] == '1' && t[i][j] == '1') {
                s[i][j] = '0';
                t[i][j] = '0';
            }
        }
    }
    Pos pos;
    rep(i, N) {
        rep(j, N) {
            if (s[i][j] == '1') {
                pos = {i, j};
                i = N;
                break;
            }
        }
    }
    cout << pos.h SP << pos.w << endl;
    s[pos.h][pos.w] = '0';
    cout << ".P" << endl;
    bool hold = true;
    while (1) {
        // if (hold) {
        //     cout << "hold" << endl;
        // } else {
        //     cout << "not hold" << endl;
        // }
        int min_dist = imax;
        Pos min_dist_pos;
        rep(i, N) {
            rep(j, N) {
                if (hold) {
                    if (t[i][j] == '1') {
                        int tmp = pos.manhattan({i, j});
                        if (tmp < min_dist) {
                            min_dist = tmp;
                            min_dist_pos = {i, j};
                        }
                    }
                } else {
                    if (s[i][j] == '1') {
                        int tmp = pos.manhattan({i, j});
                        if (tmp < min_dist) {
                            min_dist = tmp;
                            min_dist_pos = {i, j};
                        }
                    }
                }
            }
        }
        // cout << "min_dist_pos: "; //
        // min_dist_pos.print(); //

        if (hold) {
            t[min_dist_pos.h][min_dist_pos.w] = '0';
        } else {
            s[min_dist_pos.h][min_dist_pos.w] = '0';
        }

        if (min_dist == imax) {
            exit(0);
        }
        while (!(pos == min_dist_pos)) {
            int min_dir_dist = imax;
            int min_dir_dist_index;
            Pos npos;
            rep(i, 5) {
                npos = pos + d5[i];
                int tmp = npos.manhattan(min_dist_pos);
                // cout << tmp << endl; //
                if (tmp < min_dir_dist) {
                    min_dir_dist = tmp;
                    min_dir_dist_index = i;
                }
            }
            pos = pos + d5[min_dir_dist_index];
            // cout << "pos: "; //
            // pos.print(); //
            cout << dir_char[min_dir_dist_index];
            if (pos == min_dist_pos) {
                cout << 'P' << endl;
            } else {
                cout << '.' << endl;
            }
        }
        hold = !hold;
    }
}

void v_tree() {
    rep(i, N) {
        rep(j, N) {
            if (s[i][j] == '1' && t[i][j] == '1') {
                s[i][j] = '0';
                t[i][j] = '0';
            }
        }
    }
    V = min(V, N / 2);
    cout << V << endl;
    // rep3(i, V, 1) { cout << 0 SP << i * ((N) / V) << endl; }
    rep3(i, V, 1) { cout << 0 SP << i << endl; }

    Pos pos;
    rep(j, N - 1) {
        rep(i, N) {
            if (s[i][j + 1] == '0') {
                pos = {i, j};
                j = N;
                break;
            }
        }
    }
    cout << pos.h SP << pos.w << endl;
    vector<int> dirs(V);
    vector<bool> hold(V);
    // rep(j, 2) {
    //     cout << ".R";
    //     rep3(j, 2 * V, 2) cout << ".";
    //     cout << endl;
    // }
    // dirs[1] = 2;
    while (1) {
        // if (hold) {
        //     cout << "hold" << endl;
        // } else {
        //     cout << "not hold" << endl;
        // }
        int min_dist = imax;
        Pos min_dist_pos = {imax, imax};
        rep(i, N) {
            rep(j, N) {
                int tmp = (pos + d5[dirs[1]]).manhattan({i, j});
                if (tmp < min_dist) {
                    if ((t[i][j] == '1' && hold[1]) ||
                        (s[i][j] == '1' && !hold[1])) {
                        min_dist = tmp;
                        min_dist_pos = {i, j};
                    }
                }
            }
        }
        // cout << "min_dist_pos: "; //
        // min_dist_pos.print(); //

        if (min_dist != imax) {
            assert(!min_dist_pos.is_oob());
            if (hold[1]) {
                t[min_dist_pos.h][min_dist_pos.w] = '0';
            } else {
                s[min_dist_pos.h][min_dist_pos.w] = '0';
            }
        }
        while (!(pos + d5[dirs[1]] == min_dist_pos)) {
            if (min_dist == imax) {
                int flg = 1;
                rep3(i, V, 2) {
                    if (hold[i]) {
                        flg = 0;
                        break;
                    }
                }
                if (flg) {
                    return;
                }
            }
            int min_dir_dist = (pos + d5[dirs[1]]).manhattan(min_dist_pos);
            int min_dir_dist_index = -1;
            Pos npos;
            if (min_dist != imax) {
                rep(i, 4) {
                    npos = pos + d5[i];
                    if (npos.is_oob()) {
                        continue;
                    }
                    int tmp = (npos + d5[dirs[1]]).manhattan(min_dist_pos);
                    // cout << tmp << endl; //
                    if (tmp < min_dir_dist) {
                        min_dir_dist = tmp;
                        min_dir_dist_index = i;
                    }
                }
            } else {
                rep3(i, V, 2) {
                    if (hold[i]) {
                        min_dir_dist = imax;
                        rep(j, 4) {
                            npos = pos + d5[j];
                            if (npos.is_oob()) {
                                continue;
                            }
                            rep(k, N) {
                                rep(l, N) {
                                    if (t[k][l] == '1') {
                                        int tmp = (npos + (d5[dirs[i]] * i))
                                                      .manhattan({k, l});
                                        if (tmp < min_dir_dist) {
                                            min_dir_dist = tmp;
                                            min_dir_dist_index = j;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }
            if (min_dir_dist_index != -1) {
                pos = pos + d5[min_dir_dist_index];
                cout << dir_char[min_dir_dist_index];
            } else {
                cout << '.';
            }
            if (pos + d5[dirs[1]] == min_dist_pos && min_dist != imax) {
                cout << '.';
            } else {
                if ((pos.h < N / 2 && dirs[1] != 1) ||
                    (N <= pos.h + N / 2 && dirs[1] != 3)) {
                    cout << 'L';
                    dirs[1] = (dirs[1] + 1) % 4;
                } else {
                    cout << '.';
                }
            }
            rep3(i, V, 2) {
                int best_dir = 0;
                for (int j = -1; j <= 1; j++) {
                    Pos nvpos = pos + (d5[(dirs[i] + j) % 4] * i);
                    if (nvpos.is_oob()) {
                        continue;
                    }
                    if (t[nvpos.h][nvpos.w] == '1' && hold[i]) {
                        best_dir = j;
                        break;
                    } else if (s[nvpos.h][nvpos.w] == '1' && !hold[i]) {
                        best_dir = j;
                        break;
                    }
                }
                dirs[i] = (dirs[i] + best_dir) % 4;
                if (best_dir == 1) {
                    cout << "L";
                } else if (best_dir == -1) {
                    cout << "R";
                } else {
                    cout << ".";
                }
            }
            cout << ".";
            if (pos + d5[dirs[1]] == min_dist_pos && min_dist != imax) {
                cout << 'P';
            } else {
                cout << '.';
            }
            rep3(i, V, 2) {
                Pos nvpos = pos + (d5[dirs[i]] * i);
                if (!nvpos.is_oob() && t[nvpos.h][nvpos.w] == '1' && hold[i]) {
                    t[nvpos.h][nvpos.w] = '0';
                    hold[i] = false;
                    cout << 'P';
                } else if (!nvpos.is_oob() && s[nvpos.h][nvpos.w] == '1' &&
                           !hold[i]) {
                    s[nvpos.h][nvpos.w] = '0';
                    hold[i] = true;
                    cout << 'P';
                } else {
                    cout << ".";
                }
            }
            cout << endl;
        }
        hold[1] = !hold[1];
        if (min_dist == imax) {
            hold[1] = false;
        }
    }
}

int main() {
    start = chrono::system_clock::now();
    inpt();
    Grid best(s, t);
    int best_score = imax;

    int lp = 0;
    while (timer.progress() < 1) {
        lp++;
        Grid grid(s, t);
        rep(i, min(100000, best_score)) {
            grid.random_move();
            if (grid.rest == 0) {
                if (i + 1 < best_score) {
                    best_score = i + 1;
                    best = grid;
                    // cerr << lp SP << i + 1 << endl;
                }
                break;
            }
        }
    }
    best.print_ans();

    return 0;
}
