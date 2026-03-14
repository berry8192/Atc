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
constexpr long long PHASE1_MS = 1000;
constexpr long long TOTAL_MS = 3000;

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
inline bool adjacent_id(int a, int b) {
    auto [ar, ac] = rc(a);
    auto [br, bc] = rc(b);
    return max(abs(ar - br), abs(ac - bc)) == 1;
}

inline long long elapsed_ms() {
    auto now = chrono::system_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(now - start).count();
}

inline bool phase1_over() { return elapsed_ms() >= PHASE1_MS; }
inline bool total_over() { return elapsed_ms() >= TOTAL_MS; }

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

bool try_local_rewire_around_failed(int x, vector<char> &used, vector<int> &prv,
                                    vector<int> &nxt, int &head,
                                    int &inserted_count) {
    if (used[x])
        return true;

    // BFS: collect connected component of unvisited cells including x (cap 4).
    constexpr int MAX_COMPONENT = 6;
    vector<int> component;
    {
        vector<char> seen(N * N, 0);
        queue<int> bfsq;
        bfsq.push(x);
        seen[x] = 1;
        while (!bfsq.empty() && (int)component.size() < MAX_COMPONENT) {
            int v = bfsq.front();
            bfsq.pop();
            component.push_back(v);
            auto [vr, vc] = rc(v);
            rep(d, 8) {
                int nr = vr + DR[d], nc = vc + DC[d];
                if (!inb(nr, nc))
                    continue;
                int nv = vid(nr, nc);
                if (!used[nv] && !seen[nv]) {
                    seen[nv] = 1;
                    bfsq.push(nv);
                }
            }
        }
    }

    // Collect anchor candidates: visited cells neighboring any component cell.
    vector<int> anchors;
    {
        set<int> anchor_set;
        for (int cv : component) {
            auto [cvr, cvc] = rc(cv);
            rep(d, 8) {
                int nr = cvr + DR[d], nc = cvc + DC[d];
                if (!inb(nr, nc))
                    continue;
                int a0 = vid(nr, nc);
                if (!used[a0])
                    continue;
                int a1 = prv[a0], b1 = nxt[a0];
                if (a1 == -1 || b1 == -1)
                    continue;
                int a2 = prv[a1], b2 = nxt[b1];
                if (a2 == -1 || b2 == -1)
                    continue;
                if (!anchor_set.count(a0)) {
                    anchor_set.insert(a0);
                    anchors.push_back(a0);
                }
            }
        }
    }
    if (anchors.empty())
        return false;

    shuffle(anchors.begin(), anchors.end(), mt);

    for (int a0 : anchors) {
        int a1 = prv[a0], b1 = nxt[a0];
        int a2 = prv[a1], b2 = nxt[b1];
        if (a1 == -1 || b1 == -1 || a2 == -1 || b2 == -1)
            continue;

        vector<int> window = {a2, a1, a0, b1, b2};
        int left = prv[a2];
        int right = nxt[b2];

        // Detach 5-cell window from current path.
        if (left != -1)
            nxt[left] = right;
        if (right != -1)
            prv[right] = left;
        if (head == a2)
            head = right;
        for (int v : window) {
            used[v] = 0;
            prv[v] = -1;
            nxt[v] = -1;
        }

        vector<int> nodes = window;
        for (int cv : component)
            nodes.push_back(
                cv); // window(5) + component(1..6) nodes to reconnect.

        int m = (int)nodes.size();
        if (m > 16) { // DFS would be too slow; restore and skip this anchor.
            if (left != -1)
                nxt[left] = a2;
            else
                head = a2;
            prv[a2] = left;
            nxt[a2] = a1;
            prv[a1] = a2;
            nxt[a1] = a0;
            prv[a0] = a1;
            nxt[a0] = b1;
            prv[b1] = a0;
            nxt[b1] = b2;
            prv[b2] = b1;
            nxt[b2] = right;
            if (right != -1)
                prv[right] = b2;
            for (int v : window)
                used[v] = 1;
            continue;
        }
        vector<int> ord(m, -1);
        bool ok = false;

        auto dfs = [&](auto &&self, int last_idx, int mask, int depth) -> void {
            if (ok)
                return;
            if (depth == m) {
                if (right == -1 || adjacent_id(nodes[last_idx], right)) {
                    ok = true;
                }
                return;
            }
            rep(ni, m) {
                if ((mask >> ni) & 1)
                    continue;
                if (!adjacent_id(nodes[last_idx], nodes[ni]))
                    continue;
                ord[depth] = ni;
                self(self, ni, mask | (1 << ni), depth + 1);
            }
        };

        rep(st, m) {
            if (left != -1 && !adjacent_id(left, nodes[st]))
                continue;
            ord[0] = st;
            dfs(dfs, st, (1 << st), 1);
            if (ok)
                break;
        }

        if (ok) {
            int first = nodes[ord[0]];
            if (left != -1)
                nxt[left] = first;
            else
                head = first;
            prv[first] = left;

            for (int i = 1; i < m; i++) {
                int u = nodes[ord[i - 1]];
                int v = nodes[ord[i]];
                nxt[u] = v;
                prv[v] = u;
            }

            int last = nodes[ord[m - 1]];
            nxt[last] = right;
            if (right != -1)
                prv[right] = last;

            for (int v : nodes)
                used[v] = 1;

            // component cells were unvisited, each counts as one insertion.
            inserted_count += (int)component.size();
            return true;
        }

        // Restore original path segment.
        if (left != -1)
            nxt[left] = a2;
        else
            head = a2;
        prv[a2] = left;

        nxt[a2] = a1;
        prv[a1] = a2;
        nxt[a1] = a0;
        prv[a0] = a1;
        nxt[a0] = b1;
        prv[b1] = a0;
        nxt[b1] = b2;
        prv[b2] = b1;
        nxt[b2] = right;
        if (right != -1)
            prv[right] = b2;

        for (int v : window)
            used[v] = 1;
    }

    return false;
}

// Phase 3: 2-opt insertion for any remaining unvisited cells.
// All operations are in-place (no temporary vectors); path.reserve(total)
// prevents reallocation.  Cases D/E operate in O(|pnbrs|)=O(8) not O(n).
void repair_2opt_phase(vector<int> &path, int &remaining_unvisited) {
    int total = N * N;
    vector<char> used(total, 0);
    for (int v : path)
        used[v] = 1;

    vector<int> remaining;
    for (int v = 0; v < total; v++)
        if (!used[v])
            remaining.push_back(v);
    if (remaining.empty()) {
        remaining_unvisited = 0;
        return;
    }

    path.reserve(total); // guarantee no reallocation during insertions

    vector<int> pos(total, -1);
    for (int i = 0; i < (int)path.size(); i++)
        pos[path[i]] = i;

    bool progress = true;
    while (progress && !remaining.empty()) {
        if (total_over())
            break;
        progress = false;
        for (auto it = remaining.begin(); it != remaining.end();) {
            int x = *it;
            auto [xr, xc] = rc(x);
            vector<int> pnbrs;
            rep(d, 8) {
                int nr = xr + DR[d], nc = xc + DC[d];
                if (!inb(nr, nc))
                    continue;
                int nv = vid(nr, nc);
                if (used[nv])
                    pnbrs.push_back(nv);
            }

            bool found = false;
            int n = (int)path.size();

            // Case A: extend tail.
            if (!found && adjacent_id(x, path.back())) {
                pos[x] = n;
                path.push_back(x);
                used[x] = 1;
                found = true;
            }
            // Case B: extend head (prepend).
            if (!found && adjacent_id(x, path.front())) {
                path.insert(path.begin(), x);
                for (int k = 0; k < (int)path.size(); k++)
                    pos[path[k]] = k;
                used[x] = 1;
                found = true;
            }
            // Case C: 2-opt in-place.
            // New path: p[0..pi], x, p[pj..pi+1], p[pj+1..n-1]
            // Condition: p[pi+1] adj p[pj+1] (or pj==n-1).
            for (int ai = 0; ai < (int)pnbrs.size() && !found; ai++) {
                for (int bi = ai + 1; bi < (int)pnbrs.size() && !found; bi++) {
                    int pi = pos[pnbrs[ai]], pj = pos[pnbrs[bi]];
                    if (pi > pj)
                        swap(pi, pj);
                    bool ok = (pj == n - 1) ||
                              adjacent_id(path[pi + 1], path[pj + 1]);
                    if (!ok)
                        continue;
                    // Insert x at pi+1, then reverse [pi+2..pj+1].
                    path.insert(path.begin() + pi + 1, x);
                    reverse(path.begin() + pi + 2, path.begin() + pj + 2);
                    for (int k = pi + 1; k < (int)path.size(); k++)
                        pos[path[k]] = k;
                    used[x] = 1;
                    found = true;
                }
            }
            // Case D: reverse-prefix, x becomes new head.
            // New path: x, p[j..0], p[j+1..n-1]
            // Condition: x adj p[j], p[0] adj p[j+1].
            // Iterate over pnbrs (O(8)) not over all j (O(n)).
            if (!found) {
                for (int nv : pnbrs) {
                    int j = pos[nv];
                    if (j <= 0 || j >= n - 1)
                        continue;
                    if (!adjacent_id(path[0], path[j + 1]))
                        continue;
                    reverse(path.begin(), path.begin() + j + 1);
                    path.insert(path.begin(), x);
                    for (int k = 0; k < (int)path.size(); k++)
                        pos[path[k]] = k;
                    used[x] = 1;
                    found = true;
                    break;
                }
            }
            // Case E: reverse-suffix, x becomes new tail.
            // New path: p[0..j-1], p[n-1..j], x
            // Condition: x adj p[j], p[j-1] adj p[n-1].
            if (!found) {
                for (int nv : pnbrs) {
                    int j = pos[nv];
                    if (j <= 0 || j >= n - 1)
                        continue;
                    if (!adjacent_id(path[j - 1], path[n - 1]))
                        continue;
                    reverse(path.begin() + j, path.end());
                    pos[x] = (int)path.size();
                    path.push_back(x);
                    for (int k = j; k < (int)path.size(); k++)
                        pos[path[k]] = k;
                    used[x] = 1;
                    found = true;
                    break;
                }
            }

            if (found) {
                it = remaining.erase(it);
                progress = true;
            } else {
                ++it;
            }
        }
    }
    remaining_unvisited = (int)remaining.size();
}

void repair_by_queue_insert(vector<int> &path, int &inserted_count,
                            int &remaining_unvisited, int &rewire_success) {
    int total = N * N;
    inserted_count = 0;
    rewire_success = 0;

    if (path.empty()) {
        remaining_unvisited = total;
        return;
    }

    vector<char> used(total, 0);
    for (int v : path)
        used[v] = 1;

    vector<int> prv(total, -1), nxt(total, -1);
    for (int i = 0; i + 1 < (int)path.size(); i++) {
        int a = path[i], b = path[i + 1];
        nxt[a] = b;
        prv[b] = a;
    }
    int head = path.front();

    deque<int> q;
    rep(v, total) {
        if (!used[v])
            q.push_back(v);
    }

    int fail_streak = 0;
    while (!q.empty() && !total_over()) {
        int x = q.front();
        q.pop_front();

        if (used[x]) {
            fail_streak = 0;
            continue;
        }

        bool inserted = false;
        auto [r, c] = rc(x);
        rep(d, 8) {
            int nr = r + DR[d], nc = c + DC[d];
            if (!inb(nr, nc))
                continue;
            int u = vid(nr, nc);
            if (!used[u])
                continue;
            int v = nxt[u];
            if (v == -1)
                continue;
            if (!adjacent_id(x, v))
                continue;

            // Insert x between u -> v.
            nxt[u] = x;
            prv[x] = u;
            nxt[x] = v;
            prv[v] = x;
            used[x] = 1;
            inserted = true;
            inserted_count++;
            break;
        }

        if (inserted) {
            fail_streak = 0;
        } else {
            q.push_back(x);
            fail_streak++;
            if (fail_streak >= (int)q.size()) {
                bool rewired = false;
                int trials = min((int)q.size(), 24);
                rep(t, trials) {
                    if (total_over())
                        break;
                    int cand = q.front();
                    q.pop_front();
                    q.push_back(cand);
                    if (used[cand])
                        continue;
                    if (try_local_rewire_around_failed(cand, used, prv, nxt,
                                                       head, inserted_count)) {
                        rewired = true;
                        rewire_success++;
                        break;
                    }
                }
                if (rewired) {
                    fail_streak = 0;
                    continue;
                }
                break;
            }
        }
    }

    vector<int> rebuilt;
    rebuilt.reserve(total);
    int cur = head;
    while (cur != -1) {
        rebuilt.push_back(cur);
        cur = nxt[cur];
    }
    path.swap(rebuilt);

    remaining_unvisited = total - (int)path.size();
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
        if (phase1_over() || total_over()) {
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
        if (phase1_over() || total_over())
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

    int inserted_count = 0;
    int remaining_unvisited = total;
    int rewire_success = 0;
    repair_by_queue_insert(best_path, inserted_count, remaining_unvisited,
                           rewire_success);

    int twoopt_remaining = remaining_unvisited;
    repair_2opt_phase(best_path, twoopt_remaining);

    double cover = 100.0 * best_len / total;
    cerr << fixed << setprecision(2);
    cerr << "phase1_coverage: " << best_len << "/" << total << " (" << cover
         << "%)" << '\n';
    cerr << "phase1_dead_ends: " << best_dead_ends << '\n';
    cerr << "repair_inserted: " << inserted_count << '\n';
    cerr << "repair_rewire_success: " << rewire_success << '\n';
    cerr << "remaining_after_queue: " << remaining_unvisited << '\n';
    cerr << "remaining_after_2opt: " << twoopt_remaining << '\n';
    cerr << "remaining_unvisited: " << twoopt_remaining << '\n';
    cerr << "final_path_len: " << (int)best_path.size() << '\n';
    cerr << "elapsed_ms: " << elapsed_ms() << '\n';

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
