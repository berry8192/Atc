#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
typedef int8_t i8;

const int R = 10;
const int CAP_S = 15;
const int CAP_T = 20;
const double TIME_LIMIT_MS = 1850.0;

chrono::system_clock::time_point start_time;
double elapsed_ms() {
    auto now = chrono::system_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(now - start_time)
        .count();
}

struct Move {
    i8 type, i, j, k;
};

struct State {
    i8 S[R][CAP_S];
    i8 T[R][CAP_T];
    i8 Sn[R], Tn[R];
    int parent;
    Move move;
    int score;
};

int total_score(const State &s) {
    int sc = 0;
    int locked[R];
    // Starting lines: locked prefix + same-line consecutive pairs
    for (int r = 0; r < R; r++) {
        int n = s.Sn[r];
        int L = 0;
        while (L < n && s.S[r][L] == 10 * r + L) L++;
        locked[r] = L;
        sc += L * 10;
        for (int c = 0; c + 1 < n; c++) {
            int a = s.S[r][c], b = s.S[r][c + 1];
            if (b == a + 1 && a / 10 == b / 10) sc += 5;
        }
    }
    // Standby lines: same-line consecutive pairs + head deploy-readiness
    for (int j = 0; j < R; j++) {
        int n = s.Tn[j];
        for (int c = 0; c + 1 < n; c++) {
            int a = s.T[j][c], b = s.T[j][c + 1];
            if (b == a + 1 && a / 10 == b / 10) sc += 5;
        }
        if (n > 0) {
            int t = s.T[j][0] / 10;
            if (locked[t] >= 10) {
                sc -= 1;
            } else {
                int needed = 10 * t + locked[t];
                int k = 0;
                while (k < n && s.T[j][k] == needed + k &&
                       locked[t] + k < 10)
                    k++;
                sc += k * 2;
                if (k == 0) sc -= 1;
            }
        }
    }
    return sc;
}

void apply_move(State &s, const Move &m) {
    if (m.type == 0) {
        int n = s.Sn[m.i];
        int tn = s.Tn[m.j];
        for (int c = tn - 1; c >= 0; c--)
            s.T[m.j][c + m.k] = s.T[m.j][c];
        for (int c = 0; c < m.k; c++)
            s.T[m.j][c] = s.S[m.i][n - m.k + c];
        s.Tn[m.j] += m.k;
        s.Sn[m.i] -= m.k;
    } else {
        int n = s.Sn[m.i];
        for (int c = 0; c < m.k; c++)
            s.S[m.i][n + c] = s.T[m.j][c];
        int tn = s.Tn[m.j];
        for (int c = m.k; c < tn; c++)
            s.T[m.j][c - m.k] = s.T[m.j][c];
        s.Tn[m.j] -= m.k;
        s.Sn[m.i] += m.k;
    }
}

Move reverse_move(const Move &m) {
    return Move{(i8)(1 - m.type), m.i, m.j, m.k};
}

bool is_solved(const State &s) {
    for (int r = 0; r < R; r++) {
        if (s.Sn[r] != 10) return false;
        for (int c = 0; c < 10; c++)
            if (s.S[r][c] != 10 * r + c) return false;
    }
    return true;
}

uint64_t hash_state(const State &s) {
    uint64_t h = 0xcbf29ce484222325ull;
    for (int r = 0; r < R; r++) {
        h ^= (uint64_t)(uint8_t)s.Sn[r];
        h *= 0x100000001b3ull;
        for (int c = 0; c < s.Sn[r]; c++) {
            h ^= (uint64_t)(uint8_t)s.S[r][c];
            h *= 0x100000001b3ull;
        }
    }
    for (int r = 0; r < R; r++) {
        h ^= (uint64_t)(uint8_t)s.Tn[r];
        h *= 0x100000001b3ull;
        for (int c = 0; c < s.Tn[r]; c++) {
            h ^= (uint64_t)(uint8_t)s.T[r][c];
            h *= 0x100000001b3ull;
        }
    }
    return h;
}

vector<State> all_states;

int main() {
    start_time = chrono::system_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Rin;
    cin >> Rin;

    State init = {};
    init.parent = -1;
    init.move = {-1, -1, -1, -1};
    rep(r, R) {
        init.Sn[r] = 10;
        init.Tn[r] = 0;
        rep(c, 10) {
            int x;
            cin >> x;
            init.S[r][c] = (i8)x;
        }
    }
    init.score = total_score(init);

    all_states.reserve(300000);
    all_states.push_back(init);

    vector<int> beam = {0};
    int best_idx = 0;
    int best_score = init.score;

    const int BEAM_WIDTH = 40;
    const int MAX_DEPTH = 4000;

    unordered_set<uint64_t> visited;
    visited.reserve(500000);
    visited.insert(hash_state(init));

    int solved_idx = -1;

    struct Cand {
        int score;
        int parent;
        Move move;
    };
    vector<Cand> cands;
    cands.reserve(BEAM_WIDTH * 500);

    rep(depth, MAX_DEPTH) {
        if (elapsed_ms() > TIME_LIMIT_MS) break;

        cands.clear();
        bool found_solved = false;

        for (int sidx : beam) {
            State &s = all_states[sidx];
            if (is_solved(s)) {
                solved_idx = sidx;
                found_solved = true;
                break;
            }

            for (int i = 0; i < R; i++) {
                int sni = s.Sn[i];
                int locked_i = 0;
                while (locked_i < sni && s.S[i][locked_i] == 10 * i + locked_i)
                    locked_i++;

                // PRUNE: skip type 0 if line i has no non-locked tail
                bool gen_t0 = (locked_i < sni);
                int extra = sni - locked_i;

                for (int j = 0; j < R; j++) {
                    // type 0: tail of S[i] -> head of T[j]
                    if (gen_t0 && s.Tn[j] < CAP_T) {
                        int max_k0 = min(extra, CAP_T - s.Tn[j]);
                        if (max_k0 < 1) goto skip_t0;
                        {
                            int kopt[2];
                            int nk = 0;
                            kopt[nk++] = 1;
                            if (max_k0 >= 2) kopt[nk++] = max_k0;
                            for (int oi = 0; oi < nk; oi++) {
                                int k = kopt[oi];
                                Move m{0, (i8)i, (i8)j, (i8)k};
                                apply_move(s, m);
                                int sc = total_score(s);
                                apply_move(s, reverse_move(m));
                                cands.push_back({sc, sidx, m});
                            }
                        }
                    skip_t0:;
                    }
                    // type 1: head of T[j] -> tail of S[i]
                    // PRUNE: only allow if head car belongs to line i
                    if (s.Tn[j] > 0 && sni < CAP_S &&
                        s.T[j][0] / 10 == i && sni < 10) {
                        int max_k1 = min((int)s.Tn[j], CAP_S - sni);
                        // k_useful: extends locked
                        int k_useful = 0;
                        if (locked_i == sni) {
                            for (int c = 0; c < max_k1; c++) {
                                if (s.T[j][c] == 10 * i + sni + c)
                                    k_useful++;
                                else
                                    break;
                            }
                        }
                        // k_partial: number of head cars that belong to line i
                        int k_partial = 0;
                        for (int c = 0; c < max_k1; c++) {
                            if (s.T[j][c] / 10 == i)
                                k_partial++;
                            else
                                break;
                        }
                        int kopt[3];
                        int nk = 0;
                        kopt[nk++] = 1;
                        if (k_useful >= 2) kopt[nk++] = k_useful;
                        if (k_partial >= 2 && k_partial != k_useful)
                            kopt[nk++] = k_partial;
                        for (int oi = 0; oi < nk; oi++) {
                            int k = kopt[oi];
                            if (k <= 0 || k > max_k1) continue;
                            Move m{1, (i8)i, (i8)j, (i8)k};
                            apply_move(s, m);
                            int sc = total_score(s);
                            apply_move(s, reverse_move(m));
                            cands.push_back({sc, sidx, m});
                        }
                    }
                }
            }
        }

        if (found_solved) break;
        if (cands.empty()) break;

        sort(cands.begin(), cands.end(),
             [](const Cand &a, const Cand &b) { return a.score > b.score; });

        vector<int> new_beam;
        new_beam.reserve(BEAM_WIDTH);
        for (auto &c : cands) {
            if ((int)new_beam.size() >= BEAM_WIDTH) break;
            State ns = all_states[c.parent];
            apply_move(ns, c.move);
            uint64_t h = hash_state(ns);
            if (visited.count(h)) continue;
            visited.insert(h);
            ns.parent = c.parent;
            ns.move = c.move;
            ns.score = c.score;
            all_states.push_back(ns);
            int new_idx = (int)all_states.size() - 1;
            new_beam.push_back(new_idx);
            if (c.score > best_score) {
                best_score = c.score;
                best_idx = new_idx;
            }
        }

        if (new_beam.empty()) break;
        beam = std::move(new_beam);
    }

    int final_idx = solved_idx != -1 ? solved_idx : best_idx;

    // Reconstruct moves
    vector<Move> moves;
    int cur = final_idx;
    while (all_states[cur].parent != -1) {
        moves.push_back(all_states[cur].move);
        cur = all_states[cur].parent;
    }
    reverse(moves.begin(), moves.end());

    // Combine consecutive same-(type, i, j) moves into larger k
    vector<Move> combined;
    for (const auto &m : moves) {
        if (!combined.empty() && combined.back().type == m.type &&
            combined.back().i == m.i && combined.back().j == m.j) {
            combined.back().k += m.k;
        } else {
            combined.push_back(m);
        }
    }

    // Pack into turns via dependency-graph list scheduling.
    // For each move, schedule it into the earliest turn t such that:
    //   (a) t > last_turn[m.i] and t > last_turn[m.j]   (line dependency)
    //   (b) no move in turn t shares a line with m
    //   (c) no move in turn t crosses with m
    int M = (int)combined.size();
    vector<int> last_turn_for_S(R, -1), last_turn_for_T(R, -1);
    vector<vector<Move>> turns;
    for (int idx = 0; idx < M; idx++) {
        const Move &m = combined[idx];
        int min_turn = 0;
        if (last_turn_for_S[m.i] >= 0)
            min_turn = max(min_turn, last_turn_for_S[m.i] + 1);
        if (last_turn_for_T[m.j] >= 0)
            min_turn = max(min_turn, last_turn_for_T[m.j] + 1);
        int t = min_turn;
        while (true) {
            if (t >= (int)turns.size()) {
                turns.push_back({});
                break;
            }
            bool ok = true;
            for (const auto &tm : turns[t]) {
                if (tm.i == m.i || tm.j == m.j) {
                    ok = false;
                    break;
                }
                if ((tm.i < m.i && tm.j > m.j) ||
                    (tm.i > m.i && tm.j < m.j)) {
                    ok = false;
                    break;
                }
            }
            if (ok) break;
            t++;
        }
        turns[t].push_back(m);
        last_turn_for_S[m.i] = t;
        last_turn_for_T[m.j] = t;
    }

    // Output
    cout << turns.size() << "\n";
    for (const auto &t : turns) {
        cout << t.size() << "\n";
        for (const auto &m : t) {
            cout << (int)m.type << " " << (int)m.i << " " << (int)m.j << " "
                 << (int)m.k << "\n";
        }
    }

    return 0;
}
