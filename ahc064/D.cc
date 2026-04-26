#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

const int R = 10;
const int CAP_S = 15;
const int CAP_T = 20;

// plan_disp scoring weights (overridable via -D at compile time).
#ifndef W_CHUNK
#define W_CHUNK 100000
#endif
#ifndef W_NC
#define W_NC 100000
#endif
#ifndef W_M_NE_TR
#define W_M_NE_TR 50000
#endif
#ifndef W_HALF_K
#define W_HALF_K 20000
#endif
#ifndef W_HALF_M
#define W_HALF_M 30000
#endif
#ifndef W_EMPTY
#define W_EMPTY 30000
#endif
#ifndef W_SIZE_PEN
#define W_SIZE_PEN 10
#endif
#ifndef W_CHAIN
#define W_CHAIN 150000
#endif
#ifndef W_DEPTH
#define W_DEPTH 1000
#endif
#ifndef W_L
#define W_L 0
#endif

struct Move {
    int type, i, j, k;
};

vector<int> D[R];
vector<int> Sd[R];
vector<Move> ops;

void op0(int i, int j, int k) {
    // D[i] tail -> Sd[j] head, k cars
    assert((int)D[i].size() >= k);
    assert((int)Sd[j].size() + k <= CAP_T);
    vector<int> chunk(D[i].end() - k, D[i].end());
    D[i].resize(D[i].size() - k);
    Sd[j].insert(Sd[j].begin(), chunk.begin(), chunk.end());
    ops.push_back({0, i, j, k});
}

void op1(int i, int j, int k) {
    // Sd[j] head -> D[i] tail, k cars
    assert((int)Sd[j].size() >= k);
    assert((int)D[i].size() + k <= CAP_S);
    vector<int> chunk(Sd[j].begin(), Sd[j].begin() + k);
    Sd[j].erase(Sd[j].begin(), Sd[j].begin() + k);
    D[i].insert(D[i].end(), chunk.begin(), chunk.end());
    ops.push_back({1, i, j, k});
}

// Plan one displacement step: pick transit m and destination siding k for a
// chunk of items from Sd[j] head. Tuned so that op0(m,k,*) and the subsequent
// op1(target_r,j,1) can share a turn (different lines, different sidings, and
// non-crossing: i1<i2 ⇒ j1<j2).
struct DispChoice {
    int m, k, chunk;
};

DispChoice plan_disp(int j, int max_chunk, int target_r) {
    // Half-bias: low-r (0..4) and high-r (5..9) groups should use disjoint
    // siding ranges so their displace pairs can run in the same turn (non-
    // crossing: i1<i2 ⇒ j1<j2 holds when low-r uses low-j and high-r uses
    // high-j).
    int half_lo = (target_r < 5) ? 0 : 5;
    int half_hi = (target_r < 5) ? 5 : 10;

    int best_m = -1, best_k = -1, best_chunk = 0;
    long long best_score = LLONG_MIN;
    rep(m, R) {
        int space_m = CAP_S - (int)D[m].size();
        if (space_m <= 0)
            continue;
        rep(k, R) {
            if (k == j)
                continue;
            int space_k = CAP_T - (int)Sd[k].size();
            if (space_k <= 0)
                continue;
            int chunk = min({max_chunk, space_m, space_k});

            long long score = 0;
            // Bigger chunk wins big (fewer round trips).
            score += (long long)chunk * W_CHUNK;
            // m != target_r lets op0 and op1(target_r, j, 1) share a turn.
            if (m != target_r)
                score += W_M_NE_TR;
            // Non-crossing pair so packing actually fires.
            bool nc = (m != target_r) &&
                      ((m < target_r && k < j) || (m > target_r && k > j));
            if (nc)
                score += W_NC;
            // Prefer empty / lightly-loaded destination siding (avoid burying).
            if (Sd[k].empty())
                score += W_EMPTY;
            else
                score -= (int)Sd[k].size() * W_SIZE_PEN;
            // Among equally-good destinations, prefer one whose min-ID is high.
            if (!Sd[k].empty()) {
                int mn = INT_MAX;
                for (int x : Sd[k])
                    mn = min(mn, x);
                score += mn;
            }
            // Half-bias: keep displace dest in same half as target_r so the
            // other half's ops can fire in parallel turns.
            if (k >= half_lo && k < half_hi)
                score += W_HALF_K;
            if (m >= half_lo && m < half_hi)
                score += W_HALF_M;
            // Run-formation bonus: count how many cars at the chunk's tail
            // (which will sit just above old Sd[k] head) extend a same-target
            // chain v, v+1, ... toward the head. Each linked car saves one
            // op1 in the future.
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
                    } else
                        break;
                }
                score += (long long)run * W_CHAIN;
            }

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Rin;
    cin >> Rin;
    rep(r, R) {
        D[r].resize(10);
        rep(c, 10) cin >> D[r][c];
    }

    // Phase 1: dump each D[r] into Sd[r] (10 cars each).
    rep(r, R) op0(r, r, 10);

    // Phase 2: at each step pick the target_r whose next-needed car is cheapest
    // to fetch (smallest displacement depth, with chain-length bonus). This
    // lets r=9 get assembled before r=0 if its cars happen to be near the
    // siding heads.
    auto find_next = [&](int target_r) {
        int c = (int)D[target_r].size();
        int v = 10 * target_r + c;
        int j = -1, d = -1, L = 0;
        rep(s, R) {
            rep(p, (int)Sd[s].size()) {
                if (Sd[s][p] == v) {
                    j = s;
                    d = p;
                    break;
                }
            }
            if (j >= 0)
                break;
        }
        if (j >= 0) {
            int line_remaining = 10 - c;
            L = 1;
            while (L < line_remaining && d + L < (int)Sd[j].size() &&
                   Sd[j][d + L] == v + L) {
                L++;
            }
        }
        return tuple<int, int, int>{j, d, L};
    };

    // 2-step lookahead: for each candidate r, simulate the displace+op1, then
    // estimate the next-step min depth across remaining lines. Pick r that
    // minimizes step1 + step2 cost. Falls back to the snapshot approach.
    auto simulate_cost2 = [&](int j_first, int d_first, int target_r) {
        // Snapshot
        vector<int> Sd_save[R], D_save[R];
        rep(s, R) Sd_save[s] = Sd[s];
        rep(s, R) D_save[s] = D[s];
        size_t ops_size_save = ops.size();

        // Execute step 1
        if (d_first > 0)
            displace(j_first, d_first, target_r);
        int v = 10 * target_r + (int)D[target_r].size();
        int line_remaining = 10 - (int)D[target_r].size();
        // After displace, the wanted car is at Sd[j_first][0]; extend L while
        // consecutive same-target IDs follow.
        int Lq = 1;
        while (Lq < line_remaining && Lq < (int)Sd[j_first].size() &&
               Sd[j_first][Lq] == v + Lq) {
            Lq++;
        }
        op1(target_r, j_first, Lq);

        // Step 2 cost: min depth across remaining unfinished lines.
        long long min_cost2 = LLONG_MAX;
        rep(rr, R) {
            if ((int)D[rr].size() == 10)
                continue;
            auto [jj, dd, ll] = find_next(rr);
            if (jj < 0)
                continue;
            long long c = (long long)dd * W_DEPTH - (long long)ll * W_L;
            if (c < min_cost2)
                min_cost2 = c;
        }
        if (min_cost2 == LLONG_MAX)
            min_cost2 = 0;

        // Restore
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
            if ((int)D[r].size() == 10)
                continue;
            auto [j, d, L] = find_next(r);
            assert(j >= 0);
            long long cost1 = (long long)d * W_DEPTH - (long long)L * W_L;
            long long cost2 = simulate_cost2(j, d, r);
            long long total = cost1 + cost2;
            if (total < best_total) {
                best_total = total;
                best_r = r;
                best_j = j;
                best_d = d;
                best_L = L;
            }
        }
        if (best_r < 0)
            break;
        if (best_d > 0)
            displace(best_j, best_d, best_r);
        op1(best_r, best_j, best_L);
    }

    // Combine consecutive same-(type, i, j) ops into bigger k.
    vector<Move> combined;
    for (const auto &m : ops) {
        if (!combined.empty() && combined.back().type == m.type &&
            combined.back().i == m.i && combined.back().j == m.j) {
            combined.back().k += m.k;
        } else {
            combined.push_back(m);
        }
    }

    // Smart pack: each op goes into the earliest turn it can join.
    // The earliest valid turn is bounded below by max(last turn touching same
    // line, last turn touching same siding) + 1; from there we scan forward
    // for the first turn whose contents are compatible (line-disjoint,
    // siding-disjoint, non-crossing).
    vector<vector<Move>> turns;
    vector<int> last_line(R, -1), last_sid(R, -1);
    for (const auto &m : combined) {
        int earliest = max(last_line[m.i], last_sid[m.j]) + 1;
        int chosen = -1;
        for (int t = earliest; t < (int)turns.size(); t++) {
            bool ok = true;
            for (const auto &tm : turns[t]) {
                if (tm.i == m.i || tm.j == m.j) {
                    ok = false;
                    break;
                }
                if ((tm.i < m.i && tm.j > m.j) || (tm.i > m.i && tm.j < m.j)) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                chosen = t;
                break;
            }
        }
        if (chosen < 0) {
            chosen = turns.size();
            turns.push_back({});
        }
        turns[chosen].push_back(m);
        last_line[m.i] = chosen;
        last_sid[m.j] = chosen;
    }

    cout << turns.size() << "\n";
    for (const auto &t : turns) {
        cout << t.size() << "\n";
        for (const auto &m : t) {
            cout << m.type << " " << m.i << " " << m.j << " " << m.k << "\n";
        }
    }
    return 0;
}
