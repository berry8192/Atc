#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

const int R = 10;
const int CAP_S = 15;
const int CAP_T = 20;
const double TIME_LIMIT_MS = 1950.0;

chrono::system_clock::time_point start_time;
double elapsed_ms() {
    auto now = chrono::system_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(now - start_time)
        .count();
}

mt19937 rng;
int NOISE = 0;
int rand_noise(int range) { return range > 0 ? (int)(rng() % range) : 0; }

struct Move {
    int type, i, j, k;
};

vector<int> D[R];
vector<int> Sd[R];
vector<int> D_init[R];
vector<int> Sd_init[R];
vector<Move> ops;

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

struct DispChoice {
    int m, k, chunk;
};

DispChoice plan_disp(int j, int max_chunk, int target_r) {
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
            score += (long long)chunk * 100000;
            if (m != target_r)
                score += 50000;
            bool nc = (m != target_r) &&
                      ((m < target_r && k < j) || (m > target_r && k > j));
            if (nc)
                score += 100000;
            // Tuned (D.cc sweep): empty 1000→30000.
            if (Sd[k].empty())
                score += 30000;
            else
                score -= (int)Sd[k].size() * 10;
            if (!Sd[k].empty()) {
                int mn = INT_MAX;
                for (int x : Sd[k])
                    mn = min(mn, x);
                score += mn;
            }
            // Tuned: half-bias m 5000→30000.
            if (k >= half_lo && k < half_hi)
                score += 20000;
            if (m >= half_lo && m < half_hi)
                score += 30000;
            if (!Sd[k].empty() && chunk >= 1) {
                int sk_top = Sd[k][0];
                int t_target = sk_top / 10;
                int expect = sk_top - 1;
                int run = 0;
                for (int idx = chunk - 1; idx >= 0; idx--) {
                    if (Sd[j][idx] == expect && Sd[j][idx] / 10 == t_target &&
                        expect / 10 == t_target) {
                        run++;
                        expect--;
                    } else
                        break;
                }
                // Tuned: chain run 40000→150000.
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
        Sd[r] = Sd_init[r];
    }
    ops.clear();

    rep(r, R) op0(r, r, 10);

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
                   Sd[j][d + L] == v + L)
                L++;
        }
        return tuple<int, int, int>{j, d, L};
    };

    while (true) {
        int best_r = -1;
        long long best_cost = LLONG_MAX;
        int best_j = -1, best_d = -1, best_L = 0;
        rep(r, R) {
            if ((int)D[r].size() == 10)
                continue;
            auto [j, d, L] = find_next(r);
            assert(j >= 0);
            long long cost = (long long)d * 1000;
            cost += rand_noise(NOISE * 5);
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
        if (best_d > 0)
            displace(best_j, best_d, best_r);
        op1(best_r, best_j, best_L);
    }
}

vector<vector<Move>> pack_ops(const vector<Move> &ops_in) {
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
    return turns;
}

int main() {
    start_time = chrono::system_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Rin;
    cin >> Rin;
    rep(r, R) {
        D_init[r].resize(10);
        rep(c, 10) cin >> D_init[r][c];
    }

    rng.seed(12345);

    // Deterministic baseline (no noise).
    NOISE = 0;
    run_solver();
    vector<vector<Move>> best_turns = pack_ops(ops);
    int best_T = (int)best_turns.size();

    // Randomized restarts. Empirical analysis (100 seeds) showed NOISE=5000
    // wins 56% of seeds, NOISE=1000 wins 37%, larger noises (20k/50k) almost
    // never win — so we drop them and split trials between 1000 and 5000.
    int trials = 0;
    while (elapsed_ms() < TIME_LIMIT_MS) {
        trials++;
        NOISE = 1000 + (int)(rng() % 4001); // uniform in [1000, 5000]

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
