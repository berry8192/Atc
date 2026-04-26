// J.cc — I.cc + permutation π[r] (line r に group π[r] を組む)
// build phase 後、π が identity でなければ permute phase で全行を 3 ターン以内で入れ替え。
//   T1: op0(r, r, 10) for r in cycles  — 並列 (i, j とも昇順)
//   T2/T3: op1(perm[r], r, 10) — i 順に並べて smart pack 任せ (≤ 2 turn)

#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

const int R = 10;
const int CAP_S = 15;
const int CAP_T = 20;
const double TIME_LIMIT_MS = 1850.0;

chrono::system_clock::time_point start_time;
double elapsed_ms() {
    auto now = chrono::system_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(now - start_time).count();
}

mt19937 rng;
int NOISE = 0;
int rand_noise(int range) { return range > 0 ? (int)(rng() % range) : 0; }

struct Move { int type, i, j, k; };

vector<int> D[R];
vector<int> Sd[R];
vector<int> D_init[R];
vector<Move> ops;
int perm[R];

void op0(int i, int j, int k) {
    assert((int)D[i].size() >= k);
    assert((int)Sd[j].size() + k <= CAP_T);
    vector<int> chunk(D[i].end() - k, D[i].end());
    D[i].resize(D[i].size() - k);
    Sd[j].insert(Sd[j].begin(), chunk.begin(), chunk.end());
    ops.push_back({0, i, j, k});
}

void op1(int i, int j, int k) {
    assert((int)Sd[j].size() >= k);
    assert((int)D[i].size() + k <= CAP_S);
    vector<int> chunk(Sd[j].begin(), Sd[j].begin() + k);
    Sd[j].erase(Sd[j].begin(), Sd[j].begin() + k);
    D[i].insert(D[i].end(), chunk.begin(), chunk.end());
    ops.push_back({1, i, j, k});
}

struct DispChoice { int m, k, chunk; };

DispChoice plan_disp(int j, int max_chunk, int target_r) {
    int half_lo = (target_r < 5) ? 0 : 5;
    int half_hi = (target_r < 5) ? 5 : 10;

    int best_m = -1, best_k = -1, best_chunk = 0;
    long long best_score = LLONG_MIN;
    rep(m, R) {
        int space_m = CAP_S - (int)D[m].size();
        if (space_m <= 0) continue;
        rep(k, R) {
            if (k == j) continue;
            int space_k = CAP_T - (int)Sd[k].size();
            if (space_k <= 0) continue;
            int chunk = min({max_chunk, space_m, space_k});

            long long score = 0;
            score += (long long)chunk * 100000;
            if (m != target_r) score += 50000;
            bool nc = (m != target_r) &&
                      ((m < target_r && k < j) || (m > target_r && k > j));
            if (nc) score += 100000;
            if (Sd[k].empty()) score += 30000;
            else score -= (int)Sd[k].size() * 10;
            if (!Sd[k].empty()) {
                int mn = INT_MAX;
                for (int x : Sd[k]) mn = min(mn, x);
                score += mn;
            }
            if (k >= half_lo && k < half_hi) score += 20000;
            if (m >= half_lo && m < half_hi) score += 30000;
            if (!Sd[k].empty() && chunk >= 1) {
                int sk_top = Sd[k][0];
                int t_target = sk_top / 10;
                int expect = sk_top - 1;
                int run = 0;
                for (int idx = chunk - 1; idx >= 0; idx--) {
                    if (Sd[j][idx] == expect &&
                        Sd[j][idx] / 10 == t_target &&
                        expect / 10 == t_target) {
                        run++;
                        expect--;
                    } else break;
                }
                score += (long long)run * 150000;
            }
            score += rand_noise(NOISE);

            if (score > best_score) {
                best_score = score;
                best_m = m;
                best_k = k;
                best_chunk = chunk;
            }
        }
    }
    return {best_m, best_k, best_chunk};
}

void displace(int j, int total, int target_r) {
    int remaining = total;
    while (remaining > 0) {
        DispChoice c = plan_disp(j, remaining, target_r);
        assert(c.m >= 0 && c.k >= 0 && c.chunk > 0);
        op1(c.m, j, c.chunk);
        op0(c.m, c.k, c.chunk);
        remaining -= c.chunk;
    }
}

void run_solver() {
    rep(r, R) {
        D[r] = D_init[r];
        Sd[r].clear();
    }
    ops.clear();

    rep(r, R) op0(r, r, 10);

    auto find_next = [&](int target_r) {
        int c = (int)D[target_r].size();
        int v = 10 * perm[target_r] + c;
        int j = -1, d = -1, L = 0;
        rep(s, R) {
            rep(p, (int)Sd[s].size()) {
                if (Sd[s][p] == v) { j = s; d = p; break; }
            }
            if (j >= 0) break;
        }
        if (j >= 0) {
            int line_remaining = 10 - c;
            L = 1;
            while (L < line_remaining && d + L < (int)Sd[j].size() &&
                   Sd[j][d + L] == v + L) L++;
        }
        return tuple<int, int, int>{j, d, L};
    };

    auto simulate_cost2 = [&](int j_first, int d_first, int target_r) {
        vector<int> Sd_save[R], D_save[R];
        rep(s, R) Sd_save[s] = Sd[s];
        rep(s, R) D_save[s] = D[s];
        size_t ops_size_save = ops.size();

        if (d_first > 0) displace(j_first, d_first, target_r);
        int v = 10 * perm[target_r] + (int)D[target_r].size();
        int line_remaining = 10 - (int)D[target_r].size();
        int Lq = 1;
        while (Lq < line_remaining && Lq < (int)Sd[j_first].size() &&
               Sd[j_first][Lq] == v + Lq) Lq++;
        op1(target_r, j_first, Lq);

        long long min_cost2 = LLONG_MAX;
        rep(rr, R) {
            if ((int)D[rr].size() == 10) continue;
            auto [jj, dd, ll] = find_next(rr);
            if (jj < 0) continue;
            long long c = (long long)dd * 1000;
            if (c < min_cost2) min_cost2 = c;
        }
        if (min_cost2 == LLONG_MAX) min_cost2 = 0;

        rep(s, R) Sd[s] = Sd_save[s];
        rep(s, R) D[s] = D_save[s];
        ops.resize(ops_size_save);
        return min_cost2;
    };

    while (true) {
        int best_r = -1;
        long long best_total = LLONG_MAX;
        int best_j = -1, best_d = -1, best_L = 0;
        rep(r, R) {
            if ((int)D[r].size() == 10) continue;
            auto [j, d, L] = find_next(r);
            assert(j >= 0);
            long long cost1 = (long long)d * 1000;
            long long cost2 = simulate_cost2(j, d, r);
            long long total = cost1 + cost2;
            total += rand_noise(NOISE * 5);
            if (total < best_total) {
                best_total = total;
                best_r = r;
                best_j = j;
                best_d = d;
                best_L = L;
            }
        }
        if (best_r < 0) break;
        if (best_d > 0) displace(best_j, best_d, best_r);
        op1(best_r, best_j, best_L);
    }

    // Permute phase: build 後 line r は group perm[r] を保持。
    // Move line r → line perm[r] (sid r を中継に使用、build 終了時 sid は全空)。
    vector<int> moving;
    rep(r, R) if (perm[r] != r) moving.push_back(r);
    if (!moving.empty()) {
        // T1: parallel dump (i, j とも r 昇順 → 非交差 OK)
        for (int r : moving) op0(r, r, 10);
        // T2/T3: op1(perm[r], r, 10) を i (= perm[r]) 昇順に発行。
        // smart pack が非交差ペアを同 turn にまとめる。
        vector<pair<int, int>> moves;
        for (int r : moving) moves.push_back({perm[r], r});
        sort(moves.begin(), moves.end());
        for (auto [dst, src] : moves) op1(dst, src, 10);
    }
}

vector<vector<Move>> pack_ops(const vector<Move>& ops_in) {
    vector<Move> combined;
    for (const auto &m : ops_in) {
        if (!combined.empty() && combined.back().type == m.type &&
            combined.back().i == m.i && combined.back().j == m.j) {
            combined.back().k += m.k;
        } else {
            combined.push_back(m);
        }
    }

    vector<vector<Move>> turns;
    vector<int> last_line(R, -1), last_sid(R, -1);
    for (const auto &m : combined) {
        int earliest = max(last_line[m.i], last_sid[m.j]) + 1;
        int chosen = -1;
        for (int t = earliest; t < (int)turns.size(); t++) {
            bool ok = true;
            for (const auto &tm : turns[t]) {
                if (tm.i == m.i || tm.j == m.j) { ok = false; break; }
                if ((tm.i < m.i && tm.j > m.j) ||
                    (tm.i > m.i && tm.j < m.j)) { ok = false; break; }
            }
            if (ok) { chosen = t; break; }
        }
        if (chosen < 0) {
            chosen = turns.size();
            turns.push_back({});
        }
        turns[chosen].push_back(m);
        last_line[m.i] = chosen;
        last_sid[m.j] = chosen;
    }
    return turns;
}

// W[r][g] = D_init[r] 内に含まれる group g (= IDs 10g..10g+9) の数
int W[R][R];
int hperm_buf[R];

void compute_W() {
    rep(r, R) rep(g, R) W[r][g] = 0;
    rep(r, R) for (int v : D_init[r]) W[r][v / 10]++;
}

// max sum_{r} W[r][perm[r]] via bitmask DP (R=10, 10240 ops)
void hungarian_perm(int out_perm[R]) {
    int N = 1 << R;
    vector<int> dp(N, INT_MIN);
    vector<int> par(N, -1);
    dp[0] = 0;
    for (int mask = 0; mask < N; mask++) {
        if (dp[mask] == INT_MIN) continue;
        int r = __builtin_popcount(mask);
        if (r == R) continue;
        rep(g, R) {
            if (mask & (1 << g)) continue;
            int new_mask = mask | (1 << g);
            int new_score = dp[mask] + W[r][g];
            if (new_score > dp[new_mask]) {
                dp[new_mask] = new_score;
                par[new_mask] = g;
            }
        }
    }
    int mask = N - 1;
    for (int r = R - 1; r >= 0; r--) {
        int g = par[mask];
        out_perm[r] = g;
        mask ^= (1 << g);
    }
}

int main() {
    start_time = chrono::system_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Rin; cin >> Rin;
    rep(r, R) {
        D_init[r].resize(10);
        rep(c, 10) cin >> D_init[r][c];
    }

    rng.seed(12345);

    // 1. 安全な baseline: identity perm + NOISE=0
    rep(r, R) perm[r] = r;
    NOISE = 0;
    run_solver();
    vector<vector<Move>> best_turns = pack_ops(ops);
    int best_T = (int)best_turns.size();
    int id_baseline_T = best_T;

    // 2. Hungarian perm + NOISE=0 (single trial, perm 候補として保持)
    compute_W();
    hungarian_perm(hperm_buf);
    rep(r, R) perm[r] = hperm_buf[r];
    NOISE = 0;
    run_solver();
    int hung_baseline_T;
    {
        auto t = pack_ops(ops);
        hung_baseline_T = (int)t.size();
        if ((int)t.size() < best_T) {
            best_T = (int)t.size();
            best_turns = t;
        }
    }
    cerr << "baselines: id=" << id_baseline_T << " hung=" << hung_baseline_T << "\n";

    // 3. メインループ: 大半 identity (I.cc 同等)、少数 (1/10) で hungarian perm を NOISE 付きで再試行
    int trials = 0;
    while (elapsed_ms() < TIME_LIMIT_MS) {
        trials++;
        if (trials % 10 == 0) {
            rep(r, R) perm[r] = hperm_buf[r];
        } else {
            rep(r, R) perm[r] = r;
        }
        NOISE = (trials & 1) ? 5000 : 1000;

        run_solver();
        auto t = pack_ops(ops);
        if ((int)t.size() < best_T) {
            best_T = (int)t.size();
            best_turns = t;
        }
    }

    cerr << "trials=" << trials << " best_T=" << best_T << "\n";

    cout << best_turns.size() << "\n";
    for (const auto &t : best_turns) {
        cout << t.size() << "\n";
        for (const auto &m : t) {
            cout << m.type << " " << m.i << " " << m.j << " " << m.k << "\n";
        }
    }
    return 0;
}
