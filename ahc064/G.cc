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

// Reverse-build state. Lines REV_LO..R-1 build their target chain at the head
// of Sd[r] (using same index as siding). chain_len[r] tracks how many cars
// have been prepended (0 .. 10). Once chain_len[r] > 0, Sd[r] is "locked"
// and must not receive displacement junk.
const int REV_LO = 10;  // 10 = no reverse lines (forward only). Set < 10 to enable reverse for r=REV_LO..9.
int chain_len[R];

bool is_reverse_line(int r) { return r >= REV_LO; }
bool siding_locked(int s) {
    return s >= REV_LO && chain_len[s] > 0;
}

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
    if ((int)Sd[j].size() < k) {
        fprintf(stderr, "op1 fail: i=%d j=%d k=%d Sd[j].size=%d chain_len[j]=%d\n",
                i, j, k, (int)Sd[j].size(), chain_len[j]);
        for (int s = 0; s < R; s++)
            fprintf(stderr, "  Sd[%d] (size=%d, chain=%d): ", s, (int)Sd[s].size(), chain_len[s]);
        abort();
    }
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

// Skip locked sidings as displacement destinations (k) but allow them as
// source j (a forward pull might still come from there if some earlier
// displacement put a needed car there before locking). Locked sidings are
// also off-limits as transit lines? No, transit is via D[m], not siding.
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
            if (siding_locked(k))
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
            // Reverse-build protection: Sd[k] (k in REV_LO..R-1) is or will
            // become a chain build target. Cars from other lines placed here
            // get buried under the eventual chain and become inaccessible.
            // Heavy penalty for non-matching-target cars in chunk to that
            // siding (wrong-target = chunk car / 10 != k).
            if (k >= REV_LO) {
                int wrong = 0;
                for (int idx = 0; idx < chunk; idx++) {
                    if (Sd[j][idx] / 10 != k) wrong++;
                }
                score -= (long long)wrong * 10000000LL;
            }
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

    // Phase 1: distribute every D[r] into Sd[0..4] (each ends up with 20 cars).
    // Sd[5..9] start empty so they can serve as build targets for reverse
    // lines (and as displacement scratch in early Phase 2).
    rep(r, 5) op0(r, r, 10);
    for (int r = 5; r < R; r++) op0(r, r - 5, 10);

    // Phase 2: hybrid greedy. Forward lines (r < REV_LO) build [10r..10r+9] at
    // D[r] head by op1 pulls. Reverse lines (r >= REV_LO) build the same chain
    // at the head of Sd[r] by prepending cars 10r+9, 10r+8, ..., 10r in this
    // order via op1(m,j,1)+op0(m,r,1). Phase 3 then op1(r,r,10) to transfer.
    rep(r, R) chain_len[r] = 0;

    auto line_done = [&](int r) {
        if (is_reverse_line(r))
            return chain_len[r] == 10;
        return (int)D[r].size() == 10;
    };

    auto next_v = [&](int r) {
        if (is_reverse_line(r))
            return 10 * r + 9 - chain_len[r];
        return 10 * r + (int)D[r].size();
    };

    // find_next returns (source siding j, depth d, chain L). For forward lines
    // L is the run of consecutive ascending IDs starting at d (extends in the
    // SAME siding). For reverse lines L = 1 (single-car prepend; multi-card
    // chunks for reverse require ascending IDs above the wanted car which is
    // an unusual layout, so skip it for now).
    auto find_next = [&](int r) {
        int v = next_v(r);
        int j = -1, d = -1, L = 0;
        rep(s, R) {
            if (siding_locked(s))
                continue;
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
        if (j < 0)
            return tuple<int, int, int>{-1, -1, 0};
        if (is_reverse_line(r)) {
            L = 1;
        } else {
            int line_remaining = 10 - (int)D[r].size();
            L = 1;
            while (L < line_remaining && d + L < (int)Sd[j].size() &&
                   Sd[j][d + L] == v + L) {
                L++;
            }
        }
        return tuple<int, int, int>{j, d, L};
    };

    // Pick a transit line m (D[m] tail) for reverse prepends. Prefer m
    // distinct from the build-target siding's "natural" line (e.g., for r=5,
    // prefer m ∈ 0..4) and with capacity. Reverse build target is Sd[r] (a
    // siding), and m here is a 出発線 — they have separate index spaces, but
    // we still pick m != r as a soft preference for non-crossing parallelism.
    auto pick_transit = [&](int target_r) {
        int best_m = -1;
        rep(mm, R) {
            if ((int)D[mm].size() + 1 > CAP_S)
                continue;
            if (mm == target_r)
                continue;
            best_m = mm;
            break;
        }
        if (best_m < 0) {
            // Fallback: even target_r line is OK (just not common case).
            rep(mm, R) {
                if ((int)D[mm].size() + 1 <= CAP_S) {
                    best_m = mm;
                    break;
                }
            }
        }
        return best_m;
    };

    // Main greedy loop.
    while (true) {
        int best_r = -1;
        long long best_cost = LLONG_MAX;
        int best_j = -1, best_d = -1, best_L = 0;
        rep(r, R) {
            if (line_done(r))
                continue;
            auto [j, d, L] = find_next(r);
            if (j < 0)
                continue;
            long long cost = (long long)d * W_DEPTH - (long long)L * W_L;
            // For a reverse line that hasn't started yet, factor in the cost
            // of clearing Sd[r] before the first prepend.
            if (is_reverse_line(r) && chain_len[r] == 0) {
                cost += (long long)Sd[r].size() * W_DEPTH;
            }
            if (cost < best_cost) {
                best_cost = cost;
                best_r = r;
                best_j = j;
                best_d = d;
                best_L = L;
            }
        }
        if (best_r < 0)
            break;

        if (is_reverse_line(best_r)) {
            // First prepend? Clear Sd[best_r] of any junk first.
            if (chain_len[best_r] == 0 && !Sd[best_r].empty()) {
                int sz = (int)Sd[best_r].size();
                displace(best_r, sz, best_r);
                // Re-find target car (it may have moved if it was in Sd[best_r]).
                auto [j2, d2, L2] = find_next(best_r);
                assert(j2 >= 0);
                best_j = j2;
                best_d = d2;
                best_L = L2;
            }
            if (best_d > 0)
                displace(best_j, best_d, best_r);
            int m = pick_transit(best_r);
            assert(m >= 0);
            op1(m, best_j, 1);
            op0(m, best_r, 1);
            chain_len[best_r]++;
        } else {
            if (best_d > 0)
                displace(best_j, best_d, best_r);
            op1(best_r, best_j, best_L);
        }
    }

    // Phase 3: transfer reverse-built chains from Sd[r] to D[r].
    for (int r = REV_LO; r < R; r++) {
        op1(r, r, 10);
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
