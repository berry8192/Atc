#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

const int R = 10;
const int CAP_S = 15;
const int CAP_T = 20;

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
struct DispChoice { int m, k, chunk; };

DispChoice plan_disp(int j, int max_chunk, int target_r) {
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
            if (Sd[k].empty()) score += 1000;
            else score -= (int)Sd[k].size() * 10;
            if (!Sd[k].empty()) {
                int mn = INT_MAX;
                for (int x : Sd[k]) mn = min(mn, x);
                score += mn;
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

    // Phase 2: round-robin across lines. Each round advances every unfinished
    // line by one (or more, via chain extension), interleaving ops for
    // different target lines so smart-pack can pack non-crossing ops together.
    while (true) {
        bool progress = false;
        rep(target_r, R) {
            int c = (int)D[target_r].size();
            if (c == 10) continue;
            int v = 10 * target_r + c;

            int j = -1, d = -1;
            rep(s, R) {
                bool stop = false;
                rep(p, (int)Sd[s].size()) {
                    if (Sd[s][p] == v) {
                        j = s;
                        d = p;
                        stop = true;
                        break;
                    }
                }
                if (stop) break;
            }
            assert(j >= 0);

            int line_remaining = 10 - c;
            int L = 1;
            while (L < line_remaining && d + L < (int)Sd[j].size() &&
                   Sd[j][d + L] == v + L) {
                L++;
            }

            if (d > 0) displace(j, d, target_r);
            op1(target_r, j, L);
            progress = true;
        }
        if (!progress) break;
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

    cout << turns.size() << "\n";
    for (const auto &t : turns) {
        cout << t.size() << "\n";
        for (const auto &m : t) {
            cout << m.type << " " << m.i << " " << m.j << " " << m.k << "\n";
        }
    }
    return 0;
}
