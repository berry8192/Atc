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
// int global_cnt = 0; //

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

vector<Pos> d5 = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}, {0, 0}};
vector<Pos> d2 = {{0, 0},  {0, 1},   {-1, 0}, {0, -1}, {1, 0}, {0, 2}, {-1, 1},
                  {-2, 0}, {-1, -1}, {0, -2}, {1, -1}, {2, 0}, {1, 1}};
vector<Pos> d3 = {{0, 0},  {0, 1},  {-1, 0},  {0, -1},  {1, 0},
                  {0, 2},  {-1, 1}, {-2, 0},  {-1, -1}, {0, -2},
                  {1, -1}, {2, 0},  {1, 1},   {0, 3},   {-1, 2},
                  {-2, 1}, {-3, 0}, {-2, -1}, {-1, -2}, {0, -3},
                  {1, -2}, {2, -1}, {3, 0},   {2, 1},   {1, 2}};
vector<Pos> d4 = {{0, 0},   {0, 1},   {-1, 0},  {0, -1}, {1, 0},  {0, 2},
                  {-1, 1},  {-2, 0},  {-1, -1}, {0, -2}, {1, -1}, {2, 0},
                  {1, 1},   {0, 3},   {-1, 2},  {-2, 1}, {-3, 0}, {-2, -1},
                  {-1, -2}, {0, -3},  {1, -2},  {2, -1}, {3, 0},  {2, 1},
                  {1, 2},   {0, 4},   {-1, 3},  {-2, 2}, {-3, 1}, {-4, 0},
                  {-3, -1}, {-2, -2}, {-1, -3}, {0, -4}, {1, -3}, {2, -2},
                  {3, -1},  {4, 0},   {3, 1},   {2, 2},  {1, 3}};

string dir_char = "RULD.", dir_rot = "R.L";
map<char, int> mdir_char = {{'R', 0}, {'U', 1}, {'L', 2}, {'D', 3}, {'.', 4}};
map<char, int> mdir_rot = {{'R', -1}, {'.', 0}, {'L', 1}};
string base_str;
set<Pos> def_tako, def_masu;

struct Grid {
    vector<int> v, vp;
    Pos ipos, pos;
    vector<int> dir;
    vector<bool> has;
    set<Pos> tako;
    set<Pos> masu;
    vector<string> steps;
    int rest;

    Grid(int joint_len) {
        // cout << "Grid" << endl;
        if (joint_len > 0) {
            init_v_with_joint(joint_len);
        } else {
            init_v();
        }
        init_pos();
        for (auto dt : def_tako) {
            tako.insert(dt);
        }
        for (auto dm : def_masu) {
            masu.insert(dm);
        }
        dir.resize(V);
        has.resize(V);
        rest = rest_tako_masu;
    }

    void init_v() {
        v.resize(V);
        vp.resize(V);
        // rep(i, V - 1) { v[i + 1] = (i * N / (V * 2)) + 1; }
        rep(i, V - 1) { v[i + 1] = rand(1, N / 2); }
    }
    void init_v_with_joint(int joint_len) {
        v.resize(V);
        vp.resize(V);
        v[1] = joint_len;
        rep3(i, V, 2) {
            v[i] = rand(1, N / 2);
            vp[i] = 1;
        }
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
        // debug_print_v(); //
    }
    char make_mov() {
        // cout << "make_mov" << endl;
        vector<int> tmp;
        rep(i, 5) {
            Pos npos = pos + d5[i];
            if (!npos.is_oob()) {
                tmp.push_back(i);
            }
        }
        assert(tmp.size() > 0);
        int sdir = tmp[rand(0, int(tmp.size() - 1))];
        pos = pos + d5[sdir];
        return dir_char[sdir];
    }
    Pos calc_leaf_pos(int idx) {
        // cout << "calc_leaf_pos " << (dir[idx] + add_dir + 4) % 4 << endl;
        if (vp[idx] == 0) {
            return pos + d5[dir[idx]] * v[idx];
        } else {
            return pos + (d5[dir[1]] * v[1]) +
                   (d5[(dir[1] + dir[idx]) % 4] * v[idx]);
        }
    }
    Pos calc_leaf_npos(int idx, int add_dir = 0) {
        assert(vp[idx] == 0);
        // cout << "calc_leaf_npos " << (dir[idx] + add_dir + 4) % 4 << endl;
        Pos dd = d5[(dir[idx] + add_dir + 4) % 4];
        return pos + dd * v[idx];
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
                dir[i] = (dir[i] + 1) % 4;
            } else {
                int rdir = tmp[rand(0, int(tmp.size() - 1))];
                rot += dir_rot[rdir + 1];
                // dir[i] = (dir[i] + rdir + 4) % 4;
                dir[i] = (dir[i] + rdir + 4) % 4;
            }
        }
        return rot;
    }
    string make_P() {
        // // cout << "make_P" << endl;
        string p = ".";
        // rep3(i, V, 1) {
        //     Pos lpos = calc_leaf_pos(i);
        //     if (!lpos.is_oob()) {
        //         if (has[i]) {
        //             if (masu[lpos.h][lpos.w]) {
        //                 p += 'P';
        //                 masu[lpos.h][lpos.w] = false;
        //                 has[i] = false;
        //                 rest--;
        //             } else {
        //                 p += '.';
        //             }
        //         } else {
        //             if (tako[lpos.h][lpos.w]) {
        //                 p += 'P';
        //                 tako[lpos.h][lpos.w] = false;
        //                 has[i] = true;
        //                 rest--;
        //             } else {
        //                 p += '.';
        //             }
        //         }
        //     } else {
        //         p += '.';
        //     }
        // }
        return p;
    }
    string just_move() {
        // cout << "just_move" << endl;
        // int need_masu = 0;
        // rep3(i, V, 1) {
        //     if (has[i]) {
        //         need_masu++;
        //     }
        // }
        // int need_tako = V - 1 - need_masu;
        Pos nearest_pos = {-1, -1};
        int nearest_pos_dist = imax;
        int v1_dir = -1;
        int v1 = -1;
        int vi_dir = -1;
        // global_cnt++; //
        // cout << global_cnt << endl;
        // rep(i, N) {
        //     rep(j, N) {
        //         if (tako[i][j] || masu[i][j]) {
        //             rep3(k, V, 1) {
        //                 if (tako[i][j] == !has[k] || masu[i][j] == has[k]) {
        //                     rep(l, 4) {
        //                         // 目指すべき根の位置
        //                         Pos mpos = Pos(i, j) - (d5[l] * v[k]);
        //                         if (mpos.is_oob()) {
        //                             continue;
        //                         }
        //                         // 任意の方向を向いた時の葉の位置
        //                         Pos lpos = pos + (d5[l] * v[k]);
        //                         int dist = lpos.manhattan({i, j});
        //                         if (dist < nearest_pos_dist) {
        //                             nearest_pos = mpos;
        //                             nearest_pos_dist = dist;
        //                         }
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }
        if (vp[2] == 0) {
            rep3(i, V, 1) {
                rep(j, 4) {
                    Pos rpos = d5[j] * v[i];
                    if (has[i]) {
                        for (auto mp : masu) {
                            Pos mpos = mp - rpos;
                            if (mpos.is_oob()) {
                                continue;
                            }
                            Pos lpos = pos + rpos;
                            int dist = lpos.manhattan(mp);
                            if (dist < nearest_pos_dist) {
                                nearest_pos = mpos;
                                nearest_pos_dist = dist;
                            }
                        }
                    } else {
                        for (auto tp : tako) {
                            Pos mpos = tp - rpos;
                            if (mpos.is_oob()) {
                                continue;
                            }
                            Pos lpos = pos + rpos;
                            int dist = lpos.manhattan(tp);
                            if (dist < nearest_pos_dist) {
                                nearest_pos = mpos;
                                nearest_pos_dist = dist;
                            }
                        }
                    }
                }
            }
        } else {
            rep(i, 4) {
                Pos bvec = d5[i] * v[1];
                rep3(j, V, 2) {
                    rep(k, 4) {
                        Pos rvec = bvec + (d5[k] * v[j]);
                        if (has[j]) {
                            for (auto mp : masu) {
                                Pos mpos = mp - rvec;
                                if (mpos.is_oob()) {
                                    continue;
                                }
                                Pos lpos = pos + rvec;
                                int dist = lpos.manhattan(mp);
                                if (dist < nearest_pos_dist) {
                                    nearest_pos = mpos;
                                    nearest_pos_dist = dist;
                                    v1_dir = i;
                                    v1 = j;
                                    vi_dir = k;
                                }
                            }
                        } else {
                            for (auto tp : tako) {
                                Pos mpos = tp - rvec;
                                if (mpos.is_oob()) {
                                    continue;
                                }
                                Pos lpos = pos + rvec;
                                int dist = lpos.manhattan(tp);
                                if (dist < nearest_pos_dist) {
                                    nearest_pos = mpos;
                                    nearest_pos_dist = dist;
                                    v1_dir = i;
                                    v1 = j;
                                    vi_dir = k;
                                }
                            }
                        }
                    }
                }
            }
        }
        assert(nearest_pos.h != -1);
        int best_dir = -1;
        int best_dir_dist = imax;
        rep(i, 5) {
            Pos lpos = pos + d5[i];
            int tmp = lpos.manhattan(nearest_pos);
            if (tmp < best_dir_dist) {
                best_dir = i;
                best_dir_dist = tmp;
            }
        }
        string rtn(2 * V, '.');
        rtn[0] = dir_char[best_dir];
        if (vp[2] != 0) {
            assert(v1 != -1);
            assert(vi_dir != -1);
            assert(v1_dir != -1);
            if ((v1_dir - dir[1] + 4) % 4 < 2) {
                rtn[1] = 'L';
            } else if ((v1_dir - dir[1] + 4) % 4 == 3) {
                rtn[1] = 'R';
            }
        }
        rep3(i, V, 2) { rtn[i] = 'R'; }
        if (vp[2] != 0) {
            if ((vi_dir - (v1_dir + dir[v1]) + 4) % 4 < 2) {
                rtn[v1] = 'L';
            } else if ((vi_dir - (v1_dir + dir[v1]) + 4) % 4 == 3) {
                rtn[v1] = 'R';
            }
        }
        return rtn;
    }
    bool random_move() {
        // cout << "random_move" << endl;

        int i1, i2, j1, j2, j01, j02;
        vector<int> step_score(25);
        vector<string> step1(25, string(2 * V, '.'));
        vector<string> step2(25, string(2 * V, '.'));
        set<int> used;
        for (i1 = 0; i1 < 5; i1++) {
            Pos pos1 = pos + d5[i1];
            if (pos1.is_oob()) {
                continue;
            }
            for (i2 = 0; i2 < 5; i2++) {
                Pos pos2 = pos1 + d5[i2];
                if (pos2.is_oob()) {
                    continue;
                }
                step1[i1 + i2 * 5][0] = dir_char[i1];
                step2[i1 + i2 * 5][0] = dir_char[i2];
                rep3(i, V, 1) {
                    int best_prog = 0;
                    int best_dir1 = -1;
                    int best_dir2 = -1;
                    bool best_prog1 = false;
                    bool best_prog2 = false;
                    for (j1 = -1; j1 <= 1; j1++) {
                        Pos lpos1 = pos1 + (d5[(dir[i] + j1 + 4) % 4] * v[i]);
                        bool prog1 = false;
                        if (((has[i] && masu.find(lpos1) != masu.end()) ||
                             (!has[i] && tako.find(lpos1) != tako.end()))) {
                            int hash =
                                i1 + i2 * 5 + lpos1.h * 25 + lpos1.w * 750;
                            if (used.find(hash) == used.end()) {
                                used.insert(hash);
                                prog1 = true;
                            }
                        }
                        for (j2 = -1; j2 <= 1; j2++) {
                            Pos lpos2 =
                                pos2 + (d5[(dir[i] + j1 + j2 + 4) % 4] * v[i]);
                            bool prog2 = false;
                            if ((((prog1 ^ has[i]) &&
                                  masu.find(lpos2) != masu.end()) ||
                                 ((prog1 ^ !has[i]) &&
                                  tako.find(lpos2) != tako.end()))) {
                                int hash =
                                    i1 + i2 * 5 + lpos2.h * 25 + lpos2.w * 750;
                                if (used.find(hash) == used.end()) {
                                    used.insert(hash);
                                    prog2 = true;
                                }
                            }
                            if (best_prog < int(prog1 + prog2)) {
                                best_prog = int(prog1 + prog2);
                                best_dir1 = j1;
                                best_dir2 = j2;
                                best_prog1 = prog1;
                                best_prog2 = prog2;
                            }
                        }
                    }
                    step_score[i1 + i2 * 5] += best_prog;
                    step1[i1 + i2 * 5][i] = dir_rot[best_dir1 + 1];
                    if (best_prog1) {
                        step1[i1 + i2 * 5][i + V] = 'P';
                    }
                    step2[i1 + i2 * 5][i] = dir_rot[best_dir2 + 1];
                    if (best_prog2) {
                        step2[i1 + i2 * 5][i + V] = 'P';
                    }
                }
            }
        }
        string best_step1, best_step2;
        int best_score = 0;
        rep(i, 25) {
            if (step_score[i] > best_score) {
                best_score = step_score[i];
                best_step1 = step1[i];
                best_step2 = step2[i];
            }
        }
        if (best_score == 0) {
            // cout << "just_move" << endl;
            if (rest == rest_tako_masu) {
                return false;
            }
            string step = just_move();
            exec_move(step);
            // cout << step << endl; //
            steps.push_back(step);
        } else {
            exec_move(best_step1);
            // cout << best_step1 << endl; //
            steps.push_back(best_step1);
            if (rest == 0) {
                return true;
            }
            exec_move(best_step2);
            // cout << best_step2 << endl; //
            steps.push_back(best_step2);
        }

        // cout << "random move end" << endl;
        return true;
    }
    bool random_move_with_joint() {
        // cout << "random move with joint" << endl;
        string best_step;
        int best_score = 0;
        rep(i, 5) {
            string step(2 * V, '.');
            Pos npos = pos + d5[i];
            if (npos.is_oob()) {
                continue;
            }
            step[0] = dir_char[i];
            for (int j = -1; j <= 1; j++) {
                Pos bpos = npos + (d5[(dir[1] + j + 4) % 4]) * v[1];
                step[1] = dir_rot[j + 1];
                int score = 0;
                set<int> used;
                rep3(k, V, 2) {
                    step[k] = 'R';
                    step[k + V] = '.';
                    for (int l = -1; l <= 1; l++) {
                        Pos lpos =
                            bpos + d5[(dir[1] + j + dir[k] + l + 4) % 4] * v[k];
                        if (lpos.is_oob()) {
                            continue;
                        }
                        if (has[k]) {
                            if (masu.find(lpos) != masu.end()) {
                                int hash = lpos.h + lpos.w * 30;
                                if (used.find(hash) == used.end()) {
                                    used.insert(hash);
                                    step[k] = dir_rot[l + 1];
                                    step[k + V] = 'P';
                                    score += 1;
                                    break;
                                }
                            }
                        } else {
                            if (tako.find(lpos) != tako.end()) {
                                int hash = lpos.h + lpos.w * 30;
                                if (used.find(hash) == used.end()) {
                                    used.insert(hash);
                                    step[k] = dir_rot[l + 1];
                                    step[k + V] = 'P';
                                    score += 1;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (best_score < score) {
                    best_score = score;
                    best_step = step;
                }
            }
        }

        if (best_score == 0) {
            // cout << "just_move" << endl;
            if (rest == rest_tako_masu) {
                return false;
            }
            string step = just_move();
            exec_move_with_joint(step);
            // cout << step << endl; //
            steps.push_back(step);
        } else {
            exec_move_with_joint(best_step);
            // cout << best_step << endl; //
            steps.push_back(best_step);
        }
        return true;
    }
    void exec_move(string step) {
        // cout << "exec_move " << step << endl;
        pos = pos + d5[mdir_char[step[0]]];
        rep3(i, V, 1) { dir[i] = (dir[i] + mdir_rot[step[i]] + 4) % 4; }
        rep3(i, V, 1) {
            Pos lpos = calc_leaf_pos(i);
            if (step[i + V] == 'P') {
                if (has[i]) {
                    auto itr = masu.find(lpos);
                    assert(itr != masu.end());
                    masu.erase(itr);
                    has[i] = false;
                } else {
                    auto itr = tako.find(lpos);
                    assert(itr != tako.end());
                    tako.erase(itr);
                    has[i] = true;
                }
                rest--;
            }
        }
        // cout << "exec move end" << endl;
    }
    void exec_move_with_joint(string step) {
        // cout << "exec_move_with_joint " << step << endl;
        pos = pos + d5[mdir_char[step[0]]];
        rep3(i, V, 1) { dir[i] = (dir[i] + mdir_rot[step[i]] + 4) % 4; }
        rep3(i, V, 2) {
            Pos lpos = calc_leaf_pos(i);
            if (step[i + V] == 'P') {
                if (has[i]) {
                    auto itr = masu.find(lpos);
                    assert(itr != masu.end());
                    masu.erase(itr);
                    has[i] = false;
                } else {
                    auto itr = tako.find(lpos);
                    assert(itr != tako.end());
                    tako.erase(itr);
                    has[i] = true;
                }
                rest--;
            }
        }
        // cout << "exec move end" << endl;
    }
    void revert_move(string step) {
        // rep3(i, V, 1) {
        //     Pos lpos = calc_leaf_pos(i);
        //     if (step[i + V] == 'P') {
        //         if (!has[i]) {
        //             masu[lpos.h][lpos.w] = true;
        //             has[i] = true;
        //         } else {
        //             tako[lpos.h][lpos.w] = true;
        //             has[i] = false;
        //         }
        //         rest++;
        //     }
        // }
        // rep3(i, V, 1) { dir[i] = (dir[i] - mdir_rot[step[i]] + 4) % 4; }
        // pos = pos - d5[mdir_char[step[0]]];
    }

    void print_ans() {
        cout << v.size() << endl;
        rep3(i, v.size(), 1) { cout << vp[i] SP << v[i] << endl; }
        cout << ipos.h SP << ipos.w << endl;
        rep(i, steps.size()) { cout << steps[i] << endl; }
    }
    void debug_print_v() {
        // cout << "debug_print_v" << endl;
        cout << v.size() << endl;
        rep3(i, v.size(), 1) { cout << vp[i] SP << v[i] << endl; }
        cout << ipos.h SP << ipos.w << endl;
    }
    void debug_print_info() {
        cout << "debug_print_info" << endl;
        debug_print_v();
        pos.print();
        PV(dir);
        PV(has);
    }
};

void calc_masu() {
    rep(i, N) {
        rep(j, N) {
            if (s[i][j] == '1' && t[i][j] == '0') {
                def_tako.insert(Pos(i, j));
                rest_tako_masu++;
            } else if (s[i][j] == '0' && t[i][j] == '1') {
                def_masu.insert(Pos(i, j));
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
    Grid best(0);
    int best_score = imax;

    int lp = 0;
    while (timer.progress() < 1) {
        lp++;
        // cout << "lp: " << lp << endl;
        if (0) {
            Grid grid(1);

            rep(i, min(100000, best_score)) {
                if (!grid.random_move_with_joint()) {
                    break;
                }
                if (grid.rest == 0) {
                    if (i + 1 < best_score) {
                        best_score = i + 1;
                        best = grid;
                        // cerr << lp SP << i + 1 << endl;
                    }
                    break;
                }
            }
        } else {
            Grid grid(0);

            rep(i, min(100000, best_score)) {
                if (!grid.random_move()) {
                    break;
                }
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
    }
    // cerr << lp << endl;
    best.print_ans();

    return 0;
}
