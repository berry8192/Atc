#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long
template <typename T> inline bool chmin(T &a, const T &b) {
    if (a > b) {
        a = b;
        return 1;
    }
    return 0;
}
template <typename T> inline bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}

using namespace std;
// using namespace atcoder;

std::ofstream outputFile("log.txt");

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

template <class T> void PVV(T pvv) {
    rep(i, pvv.size()) {
        // outputFile<< "i: " << i <<endl;
        rep(j, pvv[i].size() - 1) { outputFile << pvv[i][j] << " "; }
        if (pvv[i].size())
            outputFile << pvv[i][pvv[i].size() - 1] << endl;
    }
}
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
double TIME_LIMIT = 1500.0;
// double TIME_LIMIT=190.0;
double start_temp = 10000000.0;
double end_temp = 10000.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed = 1;
mt19937 mt(seed);

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

// 入力
int t, n, look;
vector<string> ve, ho;
vector<vector<int>> a;

// 構造体
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

string move_alphabet = "RULD";
struct Pos {
    int h;
    int w;

    Pos(){};
    Pos(int hh, int ww) {
        h = hh;
        w = ww;
    }

    bool is_oob() {
        // assert(0<=h);
        // assert(h<n);
        // assert(0<=w);
        // assert(w<=h);
        return !(0 <= h && h < n && 0 <= w && w < n);
    }
    int manhattan(Pos pos) { return abs(h - pos.h) + abs(w - pos.w); }
    int index() { return h * n + w; }
    void print() { cout << "(" << h << ", " << w << ")" << endl; }
    // 受け取った近傍でPosを作る
    vector<Pos> around_pos() {
        vector<Pos> rtn;
        Pos new_pos;
        new_pos = {h, w + 1};
        if (!new_pos.is_oob() && ve[h][w] == '0')
            rtn.emplace_back(new_pos);
        new_pos = {h - 1, w};
        if (!new_pos.is_oob() && ho[h - 1][w] == '0')
            rtn.emplace_back(new_pos);
        new_pos = {h, w - 1};
        if (!new_pos.is_oob() && ve[h][w - 1] == '0')
            rtn.emplace_back(new_pos);
        new_pos = {h + 1, w};
        if (!new_pos.is_oob() && ho[h][w] == '0')
            rtn.emplace_back(new_pos);
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

// Pos itop(int idx) { return {idx / n, idx % n}; }

Pos d4[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

char calc_dir(Pos from, Pos to) {
    if (from == to)
        return '.';
    rep(i, 4) {
        if (from + d4[i] == to)
            return move_alphabet[i];
    }
    // 一致しない場合
    assert(0);
}

struct Turn {
    int s;
    char d;
    char e;

    Turn(){};
    Turn(int ss, char dd, char ee) {
        s = ss;
        d = dd;
        e = ee;
    }

    void print() { cout << s SP << d SP << e << endl; }
};

struct Neighbor {
    Pos prev_pos;
    int dist;

    Neighbor(){};
};
vector<map<Pos, Neighbor>> NN;

void calc_all_NN(int depth) {
    NN.resize(n * n);
    rep(i, n) {
        rep(j, n) {
            int c_index = i * n + j;
            Pos cpos = {i, j};
            NN[c_index][cpos].prev_pos = {-1, -1};
            NN[c_index][cpos].dist = 0;
            queue<Pos> qp;
            queue<int> qd;
            qp.push(cpos);
            qd.push(0);
            vector<int> seen(n * n);

            while (!qd.empty()) {
                Pos pos = qp.front();
                int dep = qd.front();
                qp.pop();
                qd.pop();

                seen[pos.index()] = 1;
                vector<Pos> poses = pos.around_pos();
                rep(k, poses.size()) {
                    if (seen[poses[k].index()])
                        continue;
                    seen[poses[k].index()] = 1;
                    NN[c_index][poses[k]].prev_pos = pos;
                    NN[c_index][poses[k]].dist = dep + 1;
                    if (dep + 1 >= depth)
                        continue;
                    qp.push(poses[k]);
                    qd.push(dep + 1);
                }
            }

            // for (auto it : NN[c_index]) {
            //     Pos pos = it.first;
            //     Neighbor neighbor = it.second;
            //     pos.print();
            //     neighbor.prev_pos.print();
            //     cout << neighbor.dist << endl;
            // }
            // exit(0);
        }
    }
}

struct Grid {
    int pi, pj, qi, qj;
    Pos taka, aoki;
    vector<vector<int>> board;
    // vector<vector<int>> taka_visit, aoki_visit;
    vector<Turn> ans;

    void init() {
        // cout << "init" << endl;
        pi = 0;
        pj = 0;
        qi = n - 1;
        qj = n - 1;
        taka = {pi, pj};
        aoki = {qi, qj};
        board = a;
        // taka_visit = vector<vector<int>>(n, vector<int>(n));
        // aoki_visit = vector<vector<int>>(n, vector<int>(n));
        // cout << "init end" << endl;
    }

    void set_random_start() {
        pi = rand(0, n - 1);
        pj = rand(0, n - 1);
        qi = rand(0, n - 1);
        qj = rand(0, n - 1);
        taka = Pos(pi, pj);
        aoki = Pos(qi, qj);
        // taka.print();
        // aoki.print();
    }

    long long getDij(Pos p) {
        ll sum = 0;
        vector<Pos> around_p = p.around_pos();
        for (auto nxt : around_p) {
            ll diff = board[nxt.h][nxt.w] - board[p.h][p.w];
            sum += diff * diff;
        }
        return sum;
    }

    long long getD() {
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                sum += getDij(Pos(i, j));
            }
        }
        return sum / 2;
    }

    long long exchange(Pos p1, Pos p2, bool execute = false) {
        ll now = getDij(p1) + getDij(p2);
        // p1とp2を交換してみる
        swap(board[p1.h][p1.w], board[p2.h][p2.w]);
        ll change = getDij(p1) + getDij(p2);
        // if (execute)
        // cout << now SP << change << endl;

        // 悪化していたらもとに戻す
        if (!execute) {
            swap(board[p1.h][p1.w], board[p2.h][p2.w]);
        }
        // どれだけ改善したか
        return now - change;
    }

    void random_walk() {
        // cout << "random_walk" << endl;
        rep(i, 4 * n * n) {
            // taka_visit[taka.h][taka.w] += 3;
            // aoki_visit[aoki.h][aoki.w] += 3;
            bool kaizen = (0 < exchange(taka, aoki));
            int s;
            if (kaizen)
                s = 1;
            else
                s = 0;

            vector<Pos> tpos = taka.around_pos();
            vector<Pos> apos = aoki.around_pos();
            int t_idx = mt() % tpos.size();
            int a_idx = mt() % apos.size();
            ans.emplace_back(s, calc_dir(taka, tpos[t_idx]),
                             calc_dir(aoki, apos[a_idx]));
            taka = tpos[t_idx];
            aoki = apos[a_idx];
        }
    }

    void random_walk_and_dfs() {

        vector<int> seen(n * n);
        vector<Pos> dfs_route;

        auto dfs = [&](auto dfs, Pos p) -> void {
            seen[p.h * n + p.w] = 1;
            vector<Pos> around_p = p.around_pos();
            for (auto nxt : around_p) {
                if (seen[nxt.h * n + nxt.w])
                    continue;
                dfs_route.push_back(nxt);
                dfs(dfs, nxt);
                dfs_route.push_back(p);
            }
            return;
        };

        dfs(dfs, aoki);
        // outputFile << dfs_route.size() << endl;

        // cout << "random_walk" << endl;
        rep(i, 4 * n * n) {
            // taka_visit[taka.h][taka.w] += 3;
            // aoki_visit[aoki.h][aoki.w] += 3;
            // outputFile << "i, taka, aoki: " << i SP << taka.h SP << taka.w SP
            //            << aoki.h SP << aoki.w << endl;
            bool kaizen = (0 < exchange(taka, aoki));
            int s;
            if (kaizen)
                s = 1;
            else
                s = 0;

            vector<Pos> tpos = taka.around_pos();

            Pos nxt_taka = tpos[0];
            ll max_exchange = -llimax;
            for (auto nxt : tpos) {
                ll tmp = exchange(nxt, dfs_route[i % dfs_route.size()]) *
                         rand(50, 150);
                if (tmp > 0)
                    swap(board[nxt.h][nxt.w],

                         board[dfs_route[i % dfs_route.size()].h]
                              [dfs_route[i % dfs_route.size()].w]);
                if (chmax(max_exchange, tmp)) {
                    nxt_taka = nxt;
                }
            }

            // int a_idx = mt() % apos.size();
            ans.emplace_back(s, calc_dir(taka, nxt_taka),
                             calc_dir(aoki, dfs_route[i % dfs_route.size()]));
            taka = nxt_taka;
            aoki = dfs_route[i % dfs_route.size()];
        }
    }

    void NN_walk() {
        int turn = 0;
        while (turn < 4 * n * n) {
            // cout << "turn_start" << endl;
            // cout << "from" << endl;
            // taka.print();
            // aoki.print();
            map<Pos, Neighbor> t_nei = NN[taka.index()];
            map<Pos, Neighbor> a_nei = NN[aoki.index()];
            int best_eval = -llimax;
            Pos best_taka, best_aoki;
            int need_turn, best_need_turn;
            ll tmp;
            for (auto tk : t_nei) {
                for (auto ao : a_nei) {
                    need_turn = max(tk.second.dist, ao.second.dist);
                    if (turn + need_turn + 1 > 4 * n * n)
                        continue;
                    // cout << tk.first.h SP << tk.first.w << ", " << ao.first.h
                    // SP
                    //      << ao.first.w << endl;
                    tmp = exchange(tk.first, ao.first) / (1 + need_turn);
                    // cout << tmp << endl;
                    // cout << tk.second.dist << ", " << ao.second.dist << endl;
                    // cout << need_turn << endl;
                    if (best_eval < tmp) {
                        best_eval = tmp;
                        best_taka = tk.first;
                        best_aoki = ao.first;
                        best_need_turn = need_turn;
                    }
                }
            }
            if (taka == best_taka && aoki == best_aoki) {
                return;
                cout << "same" << endl;
            }

            // cout << "kaizen, tuen: " << best_eval SP << best_need_turn <<
            // endl; cout << "goto" << endl; best_taka.print();
            // best_aoki.print();
            // exit(0);

            turn += best_need_turn;
            vector<int> ses(best_need_turn);
            ses[0] = 1;
            string tpos, apos;
            // 逆順に詰める
            Pos cpos = best_taka;
            Pos ppos = NN[taka.index()][best_taka].prev_pos;
            if (!(taka == best_taka)) {
                while (1) {
                    // ppos.print();
                    // cout << "T " << calc_dir(ppos, cpos) << endl;
                    // cpos.print();
                    tpos += calc_dir(ppos, cpos);
                    cpos = ppos;
                    ppos = NN[taka.index()][ppos].prev_pos;

                    if (ppos == Pos(-1, -1))
                        break;
                }
            }
            assert(tpos.size() <= best_need_turn);
            while (tpos.size() < best_need_turn) {
                tpos += '.';
            }
            // 逆順に詰める
            cpos = best_aoki;
            ppos = NN[aoki.index()][best_aoki].prev_pos;
            if (!(aoki == best_aoki)) {
                while (1) {
                    // ppos.print();
                    // cout << "A " << calc_dir(ppos, cpos) << endl;
                    // cpos.print();
                    apos += calc_dir(ppos, cpos);
                    cpos = ppos;
                    ppos = NN[aoki.index()][ppos].prev_pos;

                    if (ppos == Pos(-1, -1))
                        break;
                }
            }
            assert(apos.size() <= best_need_turn);
            while (apos.size() < best_need_turn) {
                apos += '.';
            }
            // cout << tpos << endl;
            // cout << apos << endl;
            reverse(all(tpos));
            reverse(all(apos));

            rep(i, best_need_turn) {
                // cout << ses[i] SP << tpos[i] SP << apos[i] << endl;
                ans.emplace_back(ses[i], tpos[i], apos[i]);
            }

            taka = best_taka;
            aoki = best_aoki;
            exchange(taka, aoki, true);
            // cout << "exchanged" << endl;
        }
    }

    void output_board() {
        outputFile << "board" << endl;
        PVV(board);
        // outputFile << "taka" << endl;
        // PVV(taka_visit);
        // outputFile << "aoki" << endl;
        // PVV(aoki_visit);
    }
    void print_ans() {
        cout << pi SP << pj SP << qi SP << qj << endl;
        rep(i, ans.size()) ans[i].print();
    }
};

void inpt() {
    // cout << "inpt" << endl;
    cin >> t >> n;
    look = ceil(3);
    ve.resize(n);
    ho.resize(n - 1);
    a.resize(n, vector<int>(n));

    rep(i, n) { cin >> ve[i]; }
    rep(i, n - 1) { cin >> ho[i]; }
    rep(i, n) {
        rep(j, n) { cin >> a[i][j]; }
    }
    // cout << "inpt end" << endl;
}

int main() {
    start = chrono::system_clock::now();

    inpt();
    calc_all_NN(look);

    // Grid grid;
    // grid.init();
    // long long prev = grid.getD();
    // cerr << "prev:" << prev << endl;
    // grid.random_walk();
    // long long rw = grid.getD();
    // grid.print_ans();
    // cerr << "random_walk:" << rw << endl;

    Grid best, base;
    base.init();
    // cerr << "random_walk_and_dfs:" << rw_dfs << endl;
    ll best_score = llimax;

    int loop = 0;
    while (1) {
        current = chrono::system_clock::now();
        if (chrono::duration_cast<chrono::milliseconds>(current - start)
                .count() > TIME_LIMIT) {
            break;
        }
        loop++;

        // cout << "loop: " << loop << endl;
        Grid grid = base;
        grid.set_random_start();
        grid.NN_walk();
        long long score = grid.getD();
        // cout << score << endl;

        if (best_score > score) {
            best = grid;
            best_score = score;
            // cout << "loop: " << loop << endl;
            // best.print_ans();
            // cout << "score: " << score << endl;
        }
    }
    // cout << 25 << endl;
    best.print_ans();

    return 0;
}

// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
// 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 61 62 63 64 65
// 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91
// 92 93 94 95 96 97 98 99 100
