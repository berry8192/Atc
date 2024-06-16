#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

#define MAX_FROM_SIZE 10   // 運び出し元の最大数
#define MAX_TO_SIZE 10     // 運び出し先の最大数
#define IGNORE_DIFF_MAX 3  // 誤差を無視する上界
#define IGNORE_DIFF_MIN -3 // 誤差を無視する下界

using namespace std;
// using namespace atcoder;

std::ofstream outputFile("debug_log.txt");

// template <class T> void PV(T pvv) {
//     if (!pvv.size())
//         return;
//     rep(i, pvv.size() - 1) outputFile << pvv[i] << ", ";
//     outputFile << pvv[pvv.size() - 1] << endl;
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
double TIME_LIMIT = 1900.0;
// double TIME_LIMIT=190.0;
double start_temp = 10000000.0;
double end_temp = 10000.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed = 1;
mt19937 mt(seed);

int N;
vector<vector<int>> H;

// 構造体
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

Pos itop(int idx) { return {idx / N, idx % N}; }

Pos d4[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
Pos d12[] = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1},
             {1, 0}, {1, 1},  {0, 2},  {-2, 0},  {0, -2}, {2, 0}};
string d4c = "RULD";
map<char, int> c4d;

// かたまり
struct Cluster {
    vector<Pos> poses;
    string root;
    int dist;
    // Pos start_pos;  // 開始地点
    // Pos end_pos;    // 終了地点
    int amount; // 変動する土の量

    void calc_dist_from_center() {
        assert(poses.size() == 1);
        dist = poses[0].manhattan({N / 2, N / 2});
    }
    void calc_amount(vector<vector<int>> &h) {
        amount = 0;
        rep(i, poses.size()) { amount += h[poses[i].h][poses[i].w]; }
    }

    void gen_root() {
        set<Pos> remain;
        rep(i, poses.size()) { remain.insert(poses[i]); }

        root = "";
        Pos cpos = poses[0];
        remain.erase(cpos);
        while (!remain.empty()) {
            int offset = mt() % 4;
            rep(i, 4) {
                int dir = (i + offset) % 4;
                Pos npos = cpos + d4[dir];
                if (npos.is_oob()) {
                    continue;
                }
                if (remain.find(npos) != remain.end()) {
                    remain.erase(npos);
                    cpos = npos;
                    root += d4c[dir];
                    break;
                }
            }
            rep(i, 4) {
                int dir = (i + offset) % 4;
                Pos npos = cpos + d4[dir];
                if (npos.is_oob()) {
                    continue;
                }
                for (auto pos : poses) {
                    if (remain.find(pos) == remain.end()) {
                        continue;
                    }
                    if (pos.manhattan(npos) < pos.manhattan(cpos)) {
                        cpos = npos;
                        root += d4c[dir];
                        break;
                    }
                }
            }
        }
    }

    void execute(Pos &cpos, int cv, vector<vector<int>> &h) {
        assert(cpos == poses[0]);
        rep(i, root.size()) {
            if (h[cpos.h][cpos.w] > 0) {
                cout << "+" << h[cpos.h][cpos.w] << endl;
                cv += h[cpos.h][cpos.w];
                h[cpos.h][cpos.w] = 0;
            }
            if (h[cpos.h][cpos.w] < 0 && cv > 0) {
                int tmp = min(cv, abs(h[cpos.h][cpos.w]));
                cv -= tmp;
                cout << "-" << tmp << endl;
                h[cpos.h][cpos.w] += tmp;
            }
            cpos = cpos + d4[c4d[root[i]]];
            assert(!cpos.is_oob());
        }
        if (h[cpos.h][cpos.w] > 0) {
            cout << "+" << h[cpos.h][cpos.w] << endl;
            cv += h[cpos.h][cpos.w];
            h[cpos.h][cpos.w] = 0;
        }
        if (h[cpos.h][cpos.w] < 0 && cv > 0) {
            int tmp = min(cv, abs(h[cpos.h][cpos.w]));
            cv -= tmp;
            cout << "-" << tmp << endl;
            h[cpos.h][cpos.w] += tmp;
        }
    }

    bool operator<(const Cluster &in) const { return dist > in.dist; };
};

// ひとかたまりの移動作業
struct Carry {
    int froms_id; // 運び出し元cluster
    int tos_id;   // 運び出し先cluster
    // 運び出しコスト
    // ダンプカーの土増減

    // 操作をprintする
    void execute() {}
};

struct Plan {
    vector<vector<int>> h;          // Hのコピー
    vector<Cluster> plus_clusters;  // かたまりたち
    vector<Cluster> minus_clusters; // かたまりたち
    vector<Carry> carries;          // 移動作業たち
    vector<int> carry_perm;         // 作業順

    Plan() { h = H; }

    vector<Pos> get_max_poses() {
        set<Pos> max_pos_set;
        vector<Pos> rtn;
        // vector<vector<int>> debug_print(N, vector<int>(N));
        rep(i, N) {
            rep(j, N) {
                if (h[i][j] < IGNORE_DIFF_MAX) {
                    continue;
                }
                bool not_max_f = false;
                bool next_to_max_f = false;
                Pos cpos = {i, j};
                rep(k, 12) {
                    Pos npos = cpos + d12[k];
                    if (npos.is_oob()) {
                        continue;
                    }
                    if (h[i][j] < h[npos.h][npos.w]) {
                        not_max_f = true;
                        break;
                    }
                    if (max_pos_set.find(npos) != max_pos_set.end()) {
                        next_to_max_f = true;
                    }
                }
                if (not_max_f) {
                    continue;
                }
                max_pos_set.insert(cpos);
                if (next_to_max_f == false) {
                    rtn.push_back(cpos);
                    // debug_print[i][j] = h[i][j];
                }
            }
        }
        // PVV(debug_print);
        return rtn;
    }
    vector<Pos> get_min_poses() {
        set<Pos> min_pos_set;
        vector<Pos> rtn;
        // vector<vector<int>> debug_print(N, vector<int>(N));
        rep(i, N) {
            rep(j, N) {
                if (h[i][j] > IGNORE_DIFF_MIN) {
                    continue;
                }
                bool not_min_f = false;
                bool next_to_min_f = false;
                Pos cpos = {i, j};
                rep(k, 12) {
                    Pos npos = cpos + d12[k];
                    if (npos.is_oob()) {
                        continue;
                    }
                    if (h[i][j] > h[npos.h][npos.w]) {
                        not_min_f = true;
                        break;
                    }
                    if (min_pos_set.find(npos) != min_pos_set.end()) {
                        next_to_min_f = true;
                    }
                }
                if (not_min_f) {
                    continue;
                }
                min_pos_set.insert(cpos);
                if (next_to_min_f == false) {
                    rtn.push_back(cpos);
                    // debug_print[i][j] = h[i][j];
                }
            }
        }
        // PVV(debug_print);
        return rtn;
    }

    void make_clusters() {
        // PVV(h);
        vector<vector<int>> syozoku(N, vector<int>(N)); // 0は無所属
        vector<Pos> max_poses = get_max_poses();
        vector<Pos> min_poses = get_min_poses();
        // rep(i, max_poses.size()) { max_poses[i].print(); }
        // rep(i, min_poses.size()) { min_poses[i].print(); }
        // PVV(max_poses);
        // PVV(min_poses);
        queue<Pos> pos_q;
        queue<int> id_q;
        rep(i, max_poses.size()) {
            pos_q.push(max_poses[i]);
            id_q.push(i + 1);
            plus_clusters.push_back({});
            plus_clusters[i].poses.push_back(max_poses[i]);
            plus_clusters[i].calc_dist_from_center();
        }
        while (!pos_q.empty()) {
            Pos cpos = pos_q.front();
            int id = id_q.front();
            pos_q.pop();
            id_q.pop();
            // if (id != 7) {
            //     continue;
            // }
            rep(i, 4) {
                Pos npos = cpos + d4[i];
                if (npos.is_oob()) {
                    continue;
                }
                if (syozoku[npos.h][npos.w] != 0) {
                    continue;
                }
                if (h[cpos.h][cpos.w] < h[npos.h][npos.w]) {
                    continue;
                }
                if (h[npos.h][npos.w] < IGNORE_DIFF_MAX) {
                    continue;
                }
                pos_q.push(npos);
                id_q.push(id);
                syozoku[npos.h][npos.w] = id * 10;
                plus_clusters[id - 1].poses.push_back(npos);
            }
        }

        rep(i, min_poses.size()) {
            pos_q.push(min_poses[i]);
            id_q.push(-i - 1);
            minus_clusters.push_back({});
            minus_clusters[i].poses.push_back(min_poses[i]);
            minus_clusters[i].calc_dist_from_center();
        }
        while (!pos_q.empty()) {
            Pos cpos = pos_q.front();
            int id = id_q.front();
            pos_q.pop();
            id_q.pop();
            rep(i, 4) {
                Pos npos = cpos + d4[i];
                if (npos.is_oob()) {
                    continue;
                }
                if (syozoku[npos.h][npos.w] != 0) {
                    continue;
                }
                if (h[cpos.h][cpos.w] > h[npos.h][npos.w]) {
                    continue;
                }
                if (h[npos.h][npos.w] > IGNORE_DIFF_MIN) {
                    continue;
                }
                pos_q.push(npos);
                id_q.push(id);
                syozoku[npos.h][npos.w] = id * 10;
                minus_clusters[-id - 1].poses.push_back(npos);
            }
        }
        // PVV(syozoku);
        sort(all(plus_clusters));
        sort(all(minus_clusters));
        rep(i, plus_clusters.size()) {
            plus_clusters[i].calc_amount(h);
            // cout << "size: " << plus_clusters[i].poses.size() << endl;
            // cout << "dist: " << plus_clusters[i].dist << endl;
            // cout << "amount: " << plus_clusters[i].amount << endl;
            // plus_clusters[i].poses[0].print();
        }
        rep(i, minus_clusters.size()) {
            minus_clusters[i].calc_amount(h);
            // cout << "size: " << minus_clusters[i].poses.size() << endl;
            // cout << "dist: " << minus_clusters[i].dist << endl;
            // cout << "amount: " << minus_clusters[i].amount << endl;
            // minus_clusters[i].poses[0].print();
        }
    }

    void gen_clusters_root() {
        rep(i, plus_clusters.size()) { plus_clusters[i].gen_root(); }
        rep(i, minus_clusters.size()) { minus_clusters[i].gen_root(); }
    }
    void move_to(Pos &cpos, Pos pos, int &cv) {
        while (cpos.h != pos.h || cpos.w != pos.w) {
            if (cpos.h < pos.h) {
                cpos = cpos + d4[c4d['R']];
                cout << 'R' << endl;
            } else if (cpos.h > pos.h) {
                cpos = cpos + d4[c4d['L']];
                cout << 'L' << endl;
            }
            if (cpos.w < pos.w) {
                cpos = cpos + d4[c4d['D']];
                cout << 'D' << endl;
            } else if (cpos.w > pos.w) {
                cpos = cpos + d4[c4d['U']];
                cout << 'U' << endl;
            }
            if (h[cpos.h][cpos.w] < 0 && cv > 0) {
                int tmp = min(cv, abs(h[cpos.h][cpos.w]));
                cv -= tmp;
                cout << "-" << tmp << endl;
                h[cpos.h][cpos.w] += tmp;
            }
        }
    }
    void use_dirt(Pos &cpos, int &cv) {
        Pos best_pos;
        int best_score = -100000000;
        rep(i, N) {
            rep(j, N) {
                int dist = Pos(i, j).manhattan(cpos);
                int score = 0;
                score -= dist * dist * 100;
                score += h[i][j] * 100;
                if (best_score < score) {
                    best_pos = Pos(i, j);
                }
            }
        }
        move_to(cpos, best_pos, cv);
    }
    void kari_exec() {
        // vector<int> perm(plus_clusters.size());
        // rep(i, perm.size()) { perm[i] = i; }
        // shuffle(all(perm), mt);
        Pos cpos = {0, 0};
        int cv = 0;
        rep(i, plus_clusters.size()) {
            plus_clusters[i].gen_root();
            move_to(cpos, plus_clusters[i].poses[0], cv);
            plus_clusters[i].execute(cpos, cv, h);
            use_dirt(cpos, cv);
        }
    }

    void execute() {
        rep(i, carries.size()) { carries[carry_perm[i]].execute(); }
        exit(0); // 結果を出力したら終わりにする
    }
};

void inpt() {
    cin >> N;
    H.resize(N);
    rep(i, N) { H[i].resize(N); }
    rep(i, N) {
        rep(j, N) { cin >> H[i][j]; }
    }
    c4d['R'] = 0;
    c4d['U'] = 1;
    c4d['L'] = 2;
    c4d['D'] = 3;
}

void gutyoku() {
    int cnt = 0;
    rep(i, N) {
        rep(j, N) {
            if (H[i][j] == 0)
                cnt++;
        }
    }
    int ch = 0, cw = 0, cv = 0;
    while (cnt < N * N) {
        // cout << ch SP << cw << endl;
        if (H[ch][cw] > 0) {
            cout << "+" << H[ch][cw] << endl;
            cv += H[ch][cw];
            H[ch][cw] = 0;
            cnt++;
        }
        if (H[ch][cw] < 0 && cv > 0) {
            int tmp = min(cv, abs(H[ch][cw]));
            cv -= tmp;
            cout << "-" << tmp << endl;
            H[ch][cw] += tmp;
            if (H[ch][cw] == 0)
                cnt++;
        }
        Pos cpos(ch, cw);
        Pos npos;
        int dir;
        while (1) {
            dir = mt() % 4;
            npos = cpos + d4[dir];
            if (!npos.is_oob())
                break;
        }
        cout << d4c[dir] << endl;
        ch = npos.h;
        cw = npos.w;
    }
    exit(0);
}

int main() {
    start = chrono::system_clock::now();

    inpt();
    // gutyoku();

    Plan best;
    best.make_clusters();
    best.kari_exec();
    return 0;

    int loop = 0;
    while (1) {
        current = chrono::system_clock::now();
        if (chrono::duration_cast<chrono::milliseconds>(current - start)
                .count() > TIME_LIMIT) {
            // break;
        }
        loop++;

        // Grid grid;

        // if (best.score < grid.score) {
        //     best = space;
        // cout<< "loop: " << loop <<endl;
        // best.print_ans();
        // cout<< "score: " << space.score SP << space.score*25 <<endl;
        // }
    }
    // cout<< space.score SP << space.score*25 <<endl;
    // best.print_ans();

    return 0;
}
