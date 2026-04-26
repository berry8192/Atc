// H.cc — F.cc を拡張し、displace の移動先に「後方ビルド (back) 待避線」を追加。
// 別アクションは増やさず、F.cc と同じ front-only メインループのまま、
// plan_disp の移動先候補だけ広げる:
//   - 既存 back_e[r'] への拡張: chunk が r' の次 back IDs と一致するときのみ可、巨大ボーナス
//   - 空き待避線への新規 commit: chunk が [10r+10-K, .., 10r+9] と一致 → そこを back_e[r] に確定
//   - 通常 junk dump: 予約線以外、F.cc と同じスコア
// 最終 op1(r, back_e[r], back_done[r]) で D[r] に流し込む。
// back_e[r] head→tail は常に [10r+10-back_done, .., 10r+9] を維持。

#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

const int R = 10;
const int CAP_S = 15;
const int CAP_T = 20;
const double TIME_LIMIT_MS = 100.0;
const int MAX_BACK_LINES = 5;

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

int back_e[R];      // -1 = 未割当
int back_done[R];   // back_e[r] に「正しく」積んだ枚数 (head 側の pollution を除いた残り)
int back_owner[R];  // back_owner[s] = r (s が r の back_e のとき)、それ以外 -1
int pollution[R];   // back_e[r] head 側に積んだ「汚染」(後で displace で剥がす) の枚数
bool reserved[R];
int stat_pollute_ops = 0;  // 何回 pollution した chunk があったか
int stat_pollute_cars = 0; // 累計 polluted 車両数
int stat_commit = 0;       // back-commit 回数
int stat_extend = 0;       // back-extend 回数
// back_e[r] head→tail = [pollution (pollution[r]個), back-built (back_done[r]個)] の構造を維持。

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
    int back_r;       // -1 なら junk、それ以外は back-extend or back-commit 対象 r
    bool commit_new;  // true なら新規 back_e[back_r] を k に確定
};

int count_back_lines() {
    int c = 0;
    rep(r, R) if (back_e[r] >= 0) c++;
    return c;
}

DispChoice plan_disp(int j, int max_chunk, int target_r, bool no_pollute = false) {
    int half_lo = (target_r >= 0 && target_r < 5) ? 0 : (target_r >= 5 ? 5 : 0);
    int half_hi = (target_r >= 0 && target_r < 5) ? 5 : (target_r >= 5 ? 10 : 10);

    DispChoice best = {-1, -1, 0, -1, false};
    long long best_score = LLONG_MIN;

    rep(m, R) {
        int space_m = CAP_S - (int)D[m].size();
        if (space_m <= 0) continue;
        rep(k, R) {
            if (k == j) continue;
            int space_k = CAP_T - (int)Sd[k].size();
            if (space_k <= 0) continue;

            // ---- A. 既存 back_e[r'] への拡張 (pollution[rp] == 0 のときのみ) ----
            if (reserved[k]) {
                int rp = back_owner[k];
                if (rp >= 0 && pollution[rp] == 0 && !Sd[j].empty()) {
                    int v_top = Sd[j][0];
                    int v_back_next = 10 * rp + 9 - back_done[rp];
                    if (v_top / 10 == rp && v_top <= v_back_next) {
                        int K = v_back_next - v_top + 1;
                        if (K > 0 && K <= max_chunk && K <= space_m && K <= (int)Sd[j].size()) {
                            bool ok = true;
                            for (int i = 1; i < K; i++) {
                                if (Sd[j][i] != v_top + i) { ok = false; break; }
                            }
                            if (ok) {
                                long long score = 5000000LL + (long long)K * 200000;
                                score += rand_noise(NOISE);
                                if (score > best_score) {
                                    best_score = score;
                                    best = {m, k, K, rp, false};
                                }
                            }
                        }
                    }
                }
                // ---- D. 一時ゴミ箱として back_e[r'] に積む (pollution++) ----
                // TODO: find_next/op1 が back-built 境界を越える可能性がありバグるため一旦無効化。
                // 有効化するときは pollution と back_done の境界制御を追加する必要がある。
                if (false && !no_pollute) {
                    int chunk = min({max_chunk, space_m, space_k});
                    if (chunk > 0) {
                        long long score = (long long)chunk * 100000;
                        score -= 30000;
                        score += rand_noise(NOISE);
                        if (score > best_score) {
                            best_score = score;
                            best = {m, k, chunk, -1, false};
                        }
                    }
                }
                continue;
            }

            // ---- B. 通常 junk dump (k 非予約) ----
            int chunk = min({max_chunk, space_m, space_k});
            {
                long long score = 0;
                score += (long long)chunk * 100000;
                if (target_r >= 0 && m != target_r) score += 50000;
                bool nc = (target_r >= 0 && m != target_r) &&
                          ((m < target_r && k < j) || (m > target_r && k > j));
                if (nc) score += 100000;
                if (Sd[k].empty()) score += 1000;
                else score -= (int)Sd[k].size() * 10;
                if (!Sd[k].empty()) {
                    int mn = INT_MAX;
                    for (int x : Sd[k]) mn = min(mn, x);
                    score += mn;
                }
                if (k >= half_lo && k < half_hi) score += 20000;
                if (m >= half_lo && m < half_hi) score += 5000;
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
                    score += (long long)run * 40000;
                }
                score += rand_noise(NOISE);
                if (score > best_score) {
                    best_score = score;
                    best = {m, k, chunk, -1, false};
                }
            }

            // ---- C. 空き待避線へ新規 back_e[r''] コミット ----
            if (Sd[k].empty() && count_back_lines() < MAX_BACK_LINES && !Sd[j].empty()) {
                int v_top = Sd[j][0];
                int r2 = v_top / 10;
                if (back_e[r2] < 0) {  // r2 がまだ back_e 未割当
                    int Kc = 10 - (v_top % 10);  // chunk 末尾を 10*r2+9 にする長さ
                    if (Kc > 0 && Kc <= max_chunk && Kc <= space_m && Kc <= (int)Sd[j].size()) {
                        bool ok = true;
                        for (int i = 0; i < Kc; i++) {
                            if (Sd[j][i] != v_top + i) { ok = false; break; }
                            if (Sd[j][i] / 10 != r2) { ok = false; break; }
                        }
                        if (ok) {
                            long long score = 4000000LL + (long long)Kc * 200000;
                            score += rand_noise(NOISE);
                            if (score > best_score) {
                                best_score = score;
                                best = {m, k, Kc, r2, true};
                            }
                        }
                    }
                }
            }
        }
    }
    return best;
}

void displace(int j, int total, int target_r, bool no_pollute = false) {
    int remaining = total;
    while (remaining > 0) {
        DispChoice c = plan_disp(j, remaining, target_r, no_pollute);
        assert(c.m >= 0 && c.k >= 0 && c.chunk > 0);
        op1(c.m, j, c.chunk);
        op0(c.m, c.k, c.chunk);
        if (c.back_r >= 0) {
            if (c.commit_new) {
                back_e[c.back_r] = c.k;
                back_owner[c.k] = c.back_r;
                reserved[c.k] = true;
                stat_commit++;
            } else {
                stat_extend++;
            }
            back_done[c.back_r] += c.chunk;
        } else if (reserved[c.k]) {
            // 予約線への junk dump = pollution
            int rp = back_owner[c.k];
            if (rp >= 0) {
                pollution[rp] += c.chunk;
                stat_pollute_ops++;
                stat_pollute_cars += c.chunk;
            }
        }
        // 元の back_e[r] (源 j) の pollution を剥がした場合の更新
        if (j >= 0 && reserved[j]) {
            int rj = back_owner[j];
            if (rj >= 0 && pollution[rj] > 0) {
                int peel = min(pollution[rj], c.chunk);
                pollution[rj] -= peel;
            }
        }
        remaining -= c.chunk;
    }
}

void run_solver() {
    rep(r, R) {
        D[r] = D_init[r];
        Sd[r].clear();
        back_e[r] = -1;
        back_done[r] = 0;
        back_owner[r] = -1;
        pollution[r] = 0;
        reserved[r] = false;
    }
    ops.clear();

    rep(r, R) op0(r, r, 10);

    auto find_next = [&](int target_r) {
        int c = (int)D[target_r].size();
        int v = 10 * target_r + c;
        int j = -1, d = -1, L = 0;
        rep(s, R) {
            rep(p, (int)Sd[s].size()) {
                if (Sd[s][p] == v) { j = s; d = p; break; }
            }
            if (j >= 0) break;
        }
        if (j >= 0) {
            int line_remaining = 10 - c - back_done[target_r];
            L = 1;
            while (L < line_remaining && d + L < (int)Sd[j].size() &&
                   Sd[j][d + L] == v + L) L++;
        }
        return tuple<int, int, int>{j, d, L};
    };

    while (true) {
        int best_r = -1;
        long long best_cost = LLONG_MAX;
        int best_j = -1, best_d = -1, best_L = 0;
        rep(r, R) {
            if ((int)D[r].size() + back_done[r] >= 10) continue;
            auto [j, d, L] = find_next(r);
            if (j < 0) continue;
            long long cost = (long long)d * 1000 - (long long)L * 100;
            cost += rand_noise(NOISE * 5);
            if (cost < best_cost) {
                best_cost = cost;
                best_r = r;
                best_j = j;
                best_d = d;
                best_L = L;
            }
        }
        if (best_r < 0) break;
        if (best_d > 0) displace(best_j, best_d, best_r);
        // displace 中に back_done[best_r] が増え line_remaining が狭まることがあるので、
        // 取り出し直前に L を再計算する。
        {
            int v = 10 * best_r + (int)D[best_r].size();
            int line_remaining = 10 - (int)D[best_r].size() - back_done[best_r];
            int L2 = 0;
            if (line_remaining > 0 && (int)Sd[best_j].size() > 0 && Sd[best_j][0] == v) {
                L2 = 1;
                while (L2 < line_remaining && L2 < (int)Sd[best_j].size() &&
                       Sd[best_j][L2] == v + L2) L2++;
            }
            if (L2 > 0) op1(best_r, best_j, L2);
        }
    }

    // pollution の後片付け (back_e[r] の head に積まれた汚染を non-reserved へ displace)
    rep(r, R) {
        if (back_done[r] > 0 && pollution[r] > 0) {
            displace(back_e[r], pollution[r], r, /*no_pollute=*/true);
        }
    }
    // 後方ビルドを D[r] に流し込む
    rep(r, R) {
        if (back_done[r] > 0) {
            op1(r, back_e[r], back_done[r]);
        }
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

    NOISE = 0;
    run_solver();
    vector<vector<Move>> best_turns = pack_ops(ops);
    int best_T = (int)best_turns.size();

    int trials = 0;
    while (elapsed_ms() < TIME_LIMIT_MS) {
        trials++;
        NOISE = (trials & 1) ? 5000 : 1000;

        run_solver();
        auto t = pack_ops(ops);
        if ((int)t.size() < best_T) {
            best_T = (int)t.size();
            best_turns = t;
        }
    }

    cerr << "trials=" << trials << " best_T=" << best_T
         << " commit=" << stat_commit << " extend=" << stat_extend
         << " pollute_ops=" << stat_pollute_ops
         << " pollute_cars=" << stat_pollute_cars << "\n";

    cout << best_turns.size() << "\n";
    for (const auto &t : best_turns) {
        cout << t.size() << "\n";
        for (const auto &m : t) {
            cout << m.type << " " << m.i << " " << m.j << " " << m.k << "\n";
        }
    }
    return 0;
}
