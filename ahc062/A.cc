#include <bits/stdc++.h>

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
constexpr long long GIVEUP_MS = 1000;

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
int seed = (int)chrono::steady_clock::now().time_since_epoch().count();
mt19937 mt(seed);

int N;
vector<vector<int>> A;
constexpr int DR[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
constexpr int DC[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
constexpr int EVAL_NOISE = 256;

inline bool inb(int r, int c) { return 0 <= r && r < N && 0 <= c && c < N; }
inline int vid(int r, int c) { return r * N + c; }
inline pair<int, int> rc(int v) { return {v / N, v % N}; }

inline bool time_over() {
    auto now = chrono::system_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(now - start).count() >=
           GIVEUP_MS;
}

int count_unvisited_neighbors(int v, const vector<char> &unvisited,
                              int forbidden = -1) {
    auto [r, c] = rc(v);
    int cnt = 0;
    rep(d, 8) {
        int nr = r + DR[d], nc = c + DC[d];
        if (!inb(nr, nc))
            continue;
        int nv = vid(nr, nc);
        if (nv == forbidden)
            continue;
        if (unvisited[nv])
            cnt++;
    }
    return cnt;
}

vector<int> get_unvisited_neighbors(int v, const vector<char> &unvisited) {
    vector<int> res;
    auto [r, c] = rc(v);
    rep(d, 8) {
        int nr = r + DR[d], nc = c + DC[d];
        if (!inb(nr, nc))
            continue;
        int nv = vid(nr, nc);
        if (unvisited[nv])
            res.push_back(nv);
    }
    return res;
}

bool is_allowed_move_by_deg_rule(int nxt, const vector<char> &unvisited,
                                 int &leaf_to_collect) {
    // Allow creating degree-1 only when exactly one leaf is created,
    // so it can be collected on the very next turn.
    leaf_to_collect = -1;
    int created_leaf_cnt = 0;

    auto affected = get_unvisited_neighbors(nxt, unvisited);
    for (int nv : affected) {
        int deg_before = count_unvisited_neighbors(nv, unvisited);
        int deg_after = deg_before - 1;

        // Isolated new vertex is too dangerous in this phase.
        if (deg_after <= 0)
            return false;

        if (deg_after == 1) {
            created_leaf_cnt++;
            leaf_to_collect = nv;
            if (created_leaf_cnt >= 2)
                return false;
        }
    }

    return true;
}

long long calc_score(const vector<int> &path) {
    long long score = 0;
    rep(k, path.size()) {
        auto [r, c] = rc(path[k]);
        score += 1LL * k * A[r][c];
    }
    return score;
}

bool build_phase1_path(int start_v, vector<int> &path, int &dead_end_count) {
    int total = N * N;
    vector<char> unvisited(total, 1);
    path.clear();
    path.reserve(total);

    dead_end_count = 0;
    path.push_back(start_v);
    unvisited[start_v] = 0;
    int forced_next = -1;

    int iter = 0;
    const int max_iter = total * 300;
    while ((int)path.size() < total) {
        if (time_over()) {
            return false;
        }
        if (++iter > max_iter) {
            return false;
        }

        int cur = path.back();
        vector<int> moves = get_unvisited_neighbors(cur, unvisited);
        if (moves.empty()) {
            dead_end_count++;
            int rollback = min(100, (int)path.size() - 1);
            if (rollback <= 0)
                return false;
            rep(t, rollback) {
                int v = path.back();
                path.pop_back();
                unvisited[v] = 1;
            }
            forced_next = -1;
            continue;
        }

        struct Cand {
            int nxt;
            int leaf_to_collect;
        };

        vector<Cand> cands;
        cands.reserve(moves.size());
        for (int nxt : moves) {
            int leaf_to_collect = -1;
            if (is_allowed_move_by_deg_rule(nxt, unvisited, leaf_to_collect)) {
                cands.push_back({nxt, leaf_to_collect});
            }
        }

        if (cands.empty()) {
            dead_end_count++;
            int rollback = min(100, (int)path.size() - 1);
            if (rollback <= 0)
                return false;
            rep(t, rollback) {
                int v = path.back();
                path.pop_back();
                unvisited[v] = 1;
            }
            forced_next = -1;
            continue;
        }

        // If the previous move created one degree-1 cell, collect it now.
        if (forced_next != -1) {
            bool found = false;
            for (const auto &cd : cands) {
                if (cd.nxt == forced_next) {
                    path.push_back(cd.nxt);
                    unvisited[cd.nxt] = 0;
                    forced_next = cd.leaf_to_collect;
                    found = true;
                    break;
                }
            }
            if (found)
                continue;
            forced_next = -1;
        }

        // Apply random choice with 10% probability on every decision.
        if ((int)(mt() % 10) == 0) {
            int pick = (int)(mt() % cands.size());
            path.push_back(cands[pick].nxt);
            unvisited[cands[pick].nxt] = 0;
            forced_next = cands[pick].leaf_to_collect;
            continue;
        }

        long long best_eval = (1LL << 60);
        int best_v = -1;
        int best_leaf = -1;

        for (const auto &cd : cands) {
            int nxt = cd.nxt;
            int deg_next = count_unvisited_neighbors(nxt, unvisited, cur);

            auto [r, c] = rc(nxt);
            // phase1: low-A greedy + always-on small random noise.
            int noise = (int)(mt() % (2 * EVAL_NOISE + 1)) - EVAL_NOISE;
            long long eval = 1LL * A[r][c] * 1024 - 12LL * deg_next + noise;
            if (eval < best_eval) {
                best_eval = eval;
                best_v = nxt;
                best_leaf = cd.leaf_to_collect;
            }
        }

        if (best_v == -1) {
            return false;
        }

        path.push_back(best_v);
        unvisited[best_v] = 0;
        forced_next = best_leaf;
    }

    return true;
}

void inpt() {
    cin >> N;
    A.assign(N, vector<int>(N));
    rep(i, N) rep(j, N) cin >> A[i][j];
}

int main() {
    start = chrono::system_clock::now();
    inpt();

    int total = N * N;
    vector<int> ids(total);
    rep(v, total) ids[v] = v;
    sort(all(ids), [](int x, int y) {
        auto [xr, xc] = rc(x);
        auto [yr, yc] = rc(y);
        return A[xr][xc] < A[yr][yc];
    });

    vector<int> best_path;
    long long best_score = -1;
    int best_len = -1;
    int best_dead_ends = -1;

    vector<int> start_candidates;
    int fixed_starts = min(32, total);
    rep(i, fixed_starts) start_candidates.push_back(ids[i]);
    rep(i, 64) start_candidates.push_back(mt() % total);

    for (int s : start_candidates) {
        if (time_over())
            break;
        vector<int> path;
        int dead_end_count = 0;
        build_phase1_path(s, path, dead_end_count);
        int len = (int)path.size();
        long long score = calc_score(path);
        if (len > best_len || (len == best_len && score > best_score)) {
            best_len = len;
            best_score = score;
            best_dead_ends = dead_end_count;
            best_path = path;
        }
    }

    if (best_len < 0) {
        best_len = 1;
        best_dead_ends = 0;
        best_path = {0};
    }

    double cover = 100.0 * best_len / total;
    cerr << fixed << setprecision(2);
    cerr << "phase1_coverage: " << best_len << "/" << total << " (" << cover
         << "%)" << '\n';
    cerr << "phase1_dead_ends: " << best_dead_ends << '\n';
    cerr << "elapsed_ms: "
         << chrono::duration_cast<chrono::milliseconds>(
                chrono::system_clock::now() - start)
                .count()
         << '\n';

    if ((int)best_path.size() != total && !best_path.empty()) {
        auto [lr, lc] = rc(best_path.back());
        cerr << "phase1 dead-end at step=" << ((int)best_path.size() - 1)
             << " cell=(" << lr << "," << lc << ") A=" << A[lr][lc] << '\n';
        cerr << "partial path is printed as-is (expected WA for debugging)."
             << '\n';
    }

    for (int v : best_path) {
        auto [r, c] = rc(v);
        cout << r SP << c << '\n';
    }

    return 0;
}
