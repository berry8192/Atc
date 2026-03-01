#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, AK, AM, AW;
    cin >> N >> AK >> AM >> AW;

    vector<string> wv(N), wh(N - 1);
    for (int i = 0; i < N; i++)
        cin >> wv[i];
    for (int i = 0; i < N - 1; i++)
        cin >> wh[i];

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    auto has_wall = [&](int r, int c, int d) -> bool {
        switch (d) {
        case 0:
            return r == 0 || wh[r - 1][c] == '1';
        case 1:
            return c == N - 1 || wv[r][c] == '1';
        case 2:
            return r == N - 1 || wh[r][c] == '1';
        case 3:
            return c == 0 || wv[r][c - 1] == '1';
        }
        return false;
    };

    auto simulate_bs = [&](int sr, int sc, int sd,
                           const vector<array<int, 4>> &trans) -> bitset<400> {
        int M = (int)trans.size();
        int r = sr, c = sc, d = sd, s = 0;
        vector<int> vis(N * N * 4 * M, -1);
        vector<int> traj;
        for (int step = 0;; step++) {
            int key = ((r * N + c) * 4 + d) * M + s;
            if (vis[key] >= 0) {
                bitset<400> patrol;
                for (int i = vis[key]; i < step; i++)
                    patrol.set(traj[i]);
                return patrol;
            }
            vis[key] = step;
            traj.push_back(r * N + c);
            bool wall = has_wall(r, c, d);
            int act = trans[s][wall ? 2 : 0];
            int ns = trans[s][wall ? 3 : 1];
            if (act == 0) {
                r += dr[d];
                c += dc[d];
            } else if (act == 1)
                d = (d + 1) % 4;
            else
                d = (d + 3) % 4;
            s = ns;
        }
    };

    // 全オートマトン定義
    struct AutoDef {
        vector<array<int, 4>> trans;
        int cost;
    };
    vector<AutoDef> all_autos = {
        {{{0, 0, 1, 1},
          {0, 2, 1, 2},
          {1, 3, 1, 3},
          {0, 3, 2, 4},
          {0, 5, 2, 5},
          {2, 0, 2, 0}},
         6}, // 0: zigzag
        {{{0, 0, 2, 1},
          {0, 2, 2, 2},
          {2, 3, 2, 3},
          {0, 3, 1, 4},
          {0, 5, 1, 5},
          {1, 0, 1, 0}},
         6},                               // 1: zigzag_rev
        {{{1, 1, 1, 1}, {0, 0, 2, 1}}, 2}, // 2: right_hand
        {{{2, 1, 2, 1}, {0, 0, 1, 1}}, 2}, // 3: left_hand
        {{{0, 0, 1, 0}}, 1},               // 4: rect_cw
        {{{0, 0, 2, 0}}, 1},               // 5: rect_ccw
        {{{0, 0, 1, 1}, {1, 0, 1, 0}}, 2}, // 6: uturn
        {{{0, 1, 1, 1}, {1, 0, 1, 0}}, 2}, // 7: square2x2 (F→R交互で2×2周回)
    };

    // ---- 全候補の事前計算 + 重複除去 ----
    struct Cand {
        bitset<400> patrol;
        int cost, auto_idx, r, c, d;
    };

    vector<Cand> cands;
    {
        map<string, int> seen;
        for (int t = 0; t < (int)all_autos.size(); t++)
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    for (int d = 0; d < 4; d++) {
                        auto bs = simulate_bs(i, j, d, all_autos[t].trans);
                        int cov = (int)bs.count();
                        if (cov <= all_autos[t].cost)
                            continue;
                        string key = bs.to_string();
                        if (seen.count(key)) {
                            int idx = seen[key];
                            if (all_autos[t].cost < cands[idx].cost)
                                cands[idx] = {bs, all_autos[t].cost, t, i, j,
                                              d};
                        } else {
                            seen[key] = (int)cands.size();
                            cands.push_back(
                                {bs, all_autos[t].cost, t, i, j, d});
                        }
                    }

        // 2状態オートマトンの全列挙 (576通り)
        for (int a00 = 0; a00 < 3; a00++)
        for (int b00 = 0; b00 < 2; b00++)
        for (int a01 = 1; a01 < 3; a01++)
        for (int b01 = 0; b01 < 2; b01++)
        for (int a10 = 0; a10 < 3; a10++)
        for (int b10 = 0; b10 < 2; b10++)
        for (int a11 = 1; a11 < 3; a11++)
        for (int b11 = 0; b11 < 2; b11++) {
            if (a00 != 0 && a10 != 0) continue; // Fなし → 移動しない
            vector<array<int,4>> trans = {{a00,b00,a01,b01},{a10,b10,a11,b11}};
            int auto_idx = (int)all_autos.size();
            all_autos.push_back({trans, 2});
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    for (int d = 0; d < 4; d++) {
                        auto bs = simulate_bs(i, j, d, trans);
                        int cov = (int)bs.count();
                        if (cov <= 2) continue;
                        string key = bs.to_string();
                        if (seen.count(key)) {
                            int idx = seen[key];
                            if (2 < cands[idx].cost)
                                cands[idx] = {bs, 2, auto_idx, i, j, d};
                        } else {
                            seen[key] = (int)cands.size();
                            cands.push_back({bs, 2, auto_idx, i, j, d});
                        }
                    }
        }

        // ランダムなジグザグ変種 (7状態) を候補に追加
        mt19937 rng(42);
        const int NUM_RANDOM = 200;
        for (int trial = 0; trial < NUM_RANDOM; trial++) {
            int base = rng() % 2; // zigzag or zigzag_rev
            auto trans = all_autos[base].trans;
            int M = (int)trans.size(); // 6
            // 7番目の状態をランダム生成
            int a0 = (int)(rng() % 3);
            int b0 = (int)(rng() % (M + 1));
            int a1 = 1 + (int)(rng() % 2); // R or L (壁ありなのでF不可)
            int b1 = (int)(rng() % (M + 1));
            trans.push_back({a0, b0, a1, b1});
            // 既存状態の1つの遷移先を新状態(M)に変更
            int ts = (int)(rng() % M);
            int tc = (int)(rng() % 2);
            trans[ts][tc * 2 + 1] = M;

            int auto_idx = (int)all_autos.size();
            all_autos.push_back({trans, M + 1});

            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    for (int d = 0; d < 4; d++) {
                        auto bs = simulate_bs(i, j, d, trans);
                        int cov = (int)bs.count();
                        if (cov <= M + 1)
                            continue;
                        string key = bs.to_string();
                        if (seen.count(key)) {
                            int idx = seen[key];
                            if (M + 1 < cands[idx].cost)
                                cands[idx] = {bs, M + 1, auto_idx, i, j, d};
                        } else {
                            seen[key] = (int)cands.size();
                            cands.push_back({bs, M + 1, auto_idx, i, j, d});
                        }
                    }
        }

        // ランダムな3〜6状態オートマトンを候補に追加
        const int NUM_RANDOM_3 = 200;
        for (int trial = 0; trial < NUM_RANDOM_3; trial++) {
            int ms = 3 + (int)(rng() % 4); // 3〜6状態
            vector<array<int, 4>> trans(ms);
            bool has_forward = false;
            for (int s = 0; s < ms; s++) {
                trans[s][0] = (int)(rng() % 3);      // a_s_0: F/R/L
                trans[s][1] = (int)(rng() % ms);      // b_s_0: 0〜ms-1
                trans[s][2] = 1 + (int)(rng() % 2);  // a_s_1: R/L
                trans[s][3] = (int)(rng() % ms);      // b_s_1: 0〜ms-1
                if (trans[s][0] == 0) has_forward = true;
            }
            if (!has_forward) continue; // 直進なし → 移動しない

            int auto_idx = (int)all_autos.size();
            all_autos.push_back({trans, ms});

            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    for (int d = 0; d < 4; d++) {
                        auto bs = simulate_bs(i, j, d, trans);
                        int cov = (int)bs.count();
                        if (cov <= ms) continue;
                        string key = bs.to_string();
                        if (seen.count(key)) {
                            int idx = seen[key];
                            if (ms < cands[idx].cost)
                                cands[idx] = {bs, ms, auto_idx, i, j, d};
                        } else {
                            seen[key] = (int)cands.size();
                            cands.push_back({bs, ms, auto_idx, i, j, d});
                        }
                    }
        }
    }

    int n = (int)cands.size();
    fprintf(stderr, "candidates=%d\n", n);

    // ---- コスパ順貪欲 ----
    // 毎ステップ cost/new_covered が最小（=コスパ最良）の候補を選択
    // ratio >= 1.0 なら定点(1状態/1マス)の方が得なので打ち切り
    auto greedy_solve = [&](bitset<400> init_covered) -> vector<int> {
        bitset<400> covered = init_covered;
        vector<int> selected;
        vector<bool> used(n, false);

        while ((int)covered.count() < N * N) {
            int best_idx = -1;
            double best_ratio = 1.0; // 定点のコスパ = 1.0
            int best_new = 0;

            for (int i = 0; i < n; i++) {
                if (used[i])
                    continue;
                int new_cov = (int)(cands[i].patrol & ~covered).count();
                if (new_cov == 0)
                    continue;
                double ratio = (double)cands[i].cost / new_cov;
                if (ratio < best_ratio ||
                    (ratio == best_ratio && new_cov > best_new)) {
                    best_ratio = ratio;
                    best_idx = i;
                    best_new = new_cov;
                }
            }
            if (best_idx == -1)
                break;
            selected.push_back(best_idx);
            used[best_idx] = true;
            covered |= cands[best_idx].patrol;
        }
        return selected;
    };

    auto calc_total = [&](const vector<int> &selected) -> int {
        bitset<400> covered;
        int cost = 0;
        for (int idx : selected) {
            covered |= cands[idx].patrol;
            cost += cands[idx].cost;
        }
        cost += N * N - (int)covered.count(); // 残りは定点
        return cost;
    };

    // 初回貪欲
    vector<int> selected = greedy_solve(bitset<400>());
    int best_total = calc_total(selected);
    fprintf(stderr, "greedy=%d (robots=%d)\n", best_total,
            (int)selected.size());

    // ---- 局所探索: 1台抜いて再充填 ----
    bool improved = true;
    while (improved) {
        improved = false;
        for (int s = 0; s < (int)selected.size(); s++) {
            // s番目を抜いた状態のカバー
            bitset<400> remaining_cov;
            int remaining_cost = 0;
            vector<int> remaining;
            for (int i = 0; i < (int)selected.size(); i++) {
                if (i != s) {
                    remaining_cov |= cands[selected[i]].patrol;
                    remaining_cost += cands[selected[i]].cost;
                    remaining.push_back(selected[i]);
                }
            }
            // 残りを再充填
            auto refill = greedy_solve(remaining_cov);
            bitset<400> new_cov = remaining_cov;
            int new_cost = remaining_cost;
            for (int idx : refill) {
                new_cov |= cands[idx].patrol;
                new_cost += cands[idx].cost;
            }
            new_cost += N * N - (int)new_cov.count();

            if (new_cost < best_total) {
                for (int idx : refill)
                    remaining.push_back(idx);
                selected = remaining;
                best_total = new_cost;
                improved = true;
                fprintf(stderr, "local_search improved to %d\n", best_total);
                break;
            }
        }
    }

    fprintf(stderr, "final=%d\n", best_total);

    // ---- 出力構築 ----
    bitset<400> covered;
    for (int idx : selected)
        covered |= cands[idx].patrol;

    set<int> uncov_set;
    for (int i = 0; i < N * N; i++)
        if (!covered.test(i))
            uncov_set.insert(i);

    // 2x2周回で残りマスを効率的にカバー (2状態で3+マスカバー → 定点より得)
    vector<array<int, 4>> sq2_trans = {{0, 1, 1, 1}, {1, 0, 1, 0}};
    vector<array<int, 3>> extra; // {r, c, d}
    {
        vector<int> uncov_list(uncov_set.begin(), uncov_set.end());
        for (int cell : uncov_list) {
            if (!uncov_set.count(cell))
                continue;
            int r = cell / N, c = cell % N;
            int best_d = -1, best_new = 0;
            for (int d = 0; d < 4; d++) {
                auto bs = simulate_bs(r, c, d, sq2_trans);
                int new_cov = 0;
                for (int i = 0; i < N * N; i++)
                    if (bs.test(i) && uncov_set.count(i))
                        new_cov++;
                if (new_cov > best_new) {
                    best_new = new_cov;
                    best_d = d;
                }
            }
            if (best_new >= 3) {
                auto bs = simulate_bs(r, c, best_d, sq2_trans);
                for (int i = 0; i < N * N; i++)
                    if (bs.test(i))
                        uncov_set.erase(i);
                extra.push_back({r, c, best_d});
            }
        }
    }

    vector<pair<int, int>> remaining_uncov;
    for (int cell : uncov_set)
        remaining_uncov.push_back({cell / N, cell % N});

    char dir_ch[] = {'U', 'R', 'D', 'L'};
    const char *act_ch[] = {"F", "R", "L"};

    int total_robots =
        (int)selected.size() + (int)extra.size() + (int)remaining_uncov.size();
    cout << total_robots << "\n";

    for (int idx : selected) {
        auto &a = all_autos[cands[idx].auto_idx];
        cout << a.cost << " " << cands[idx].r << " " << cands[idx].c << " "
             << dir_ch[cands[idx].d] << "\n";
        for (auto &tr : a.trans)
            cout << act_ch[tr[0]] << " " << tr[1] << " " << act_ch[tr[2]] << " "
                 << tr[3] << "\n";
    }

    for (auto &e : extra) {
        cout << "2 " << e[0] << " " << e[1] << " " << dir_ch[e[2]] << "\n";
        cout << "F 1 R 1\n";
        cout << "R 0 R 0\n";
    }

    for (auto &[i, j] : remaining_uncov) {
        cout << "1 " << i << " " << j << " U\n";
        cout << "R 0 R 0\n";
    }

    for (int i = 0; i < N; i++)
        cout << string(N - 1, '0') << "\n";
    for (int i = 0; i < N - 1; i++)
        cout << string(N, '0') << "\n";

    return 0;
}
