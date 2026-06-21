// AHC066 お片付けロボット — D2.cc
// D.cc の TLE 修正版。アルゴリズムは同じ。
// 違い:
//   - TIME_LIMIT = 1.85 (本番ぶれ対応の余裕 0.15s)
//   - SA1 を 0.4s で締める
//   - SA2 締切を「候補1個の build+sim 実測 × 想定候補数」から動的に決定
//   - 最終候補集合を {bestSAperm, naive, nn} × ml ∈ [best_ml±2] に絞る

#include <bits/stdc++.h>
#include <chrono>
using namespace std;

int N, M, T;
vector<string> v_wall, h_wall;
const int DI[] = {-1, 0, 1, 0};   // 0=up 1=right 2=down 3=left
const int DJ[] = {0, 1, 0, -1};
vector<pair<int,int>> ball_init, cage_pos;

int NN, NN4;

inline bool canMove(int r, int c, int d) {
    if (d == 0) return r > 0 && h_wall[r-1][c] == '0';
    if (d == 1) return c < N-1 && v_wall[r][c] == '0';
    if (d == 2) return r < N-1 && h_wall[r][c] == '0';
    return c > 0 && v_wall[r][c-1] == '0';
}

// 標準BFS(セル距離のみ)
vector<vector<vector<vector<short>>>> bfs_dist;
void precomputeBFS() {
    bfs_dist.assign(N, vector<vector<vector<short>>>(N, vector<vector<short>>(N, vector<short>(N, -1))));
    for (int sr = 0; sr < N; sr++) for (int sc = 0; sc < N; sc++) {
        auto& dist = bfs_dist[sr][sc];
        dist[sr][sc] = 0;
        queue<pair<int,int>> q;
        q.push({sr, sc});
        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                if (!canMove(r, c, d)) continue;
                int nr = r + DI[d], nc = c + DJ[d];
                if (dist[nr][nc] != -1) continue;
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
}

// 方向aware Dijkstra テーブル
// dijk_table[(src_idx*4+src_dir)*NN + dst_idx] = (cost, end_dir)
struct DijkEntry { short cost; unsigned char end_dir; unsigned char pad; };
vector<DijkEntry> dijk_table;

void precomputeDijk() {
    NN = N * N; NN4 = NN * 4;
    dijk_table.assign((size_t)NN4 * NN, {32000, 0, 0});

    vector<int> dist(NN4);
    for (int sr = 0; sr < N; sr++) for (int sc = 0; sc < N; sc++) for (int sd = 0; sd < 4; sd++) {
        int src_state = (sr * N + sc) * 4 + sd;
        fill(dist.begin(), dist.end(), INT_MAX);
        dist[src_state] = 0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({0, src_state});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            int cell = u / 4, dir = u % 4;
            int r = cell / N, c = cell % N;
            if (canMove(r, c, dir)) {
                int nr = r + DI[dir], nc = c + DJ[dir];
                int v = (nr * N + nc) * 4 + dir;
                if (d + 1 < dist[v]) { dist[v] = d + 1; pq.push({d + 1, v}); }
            }
            { // R
                int nd = (dir + 1) & 3;
                int v = cell * 4 + nd;
                if (d + 1 < dist[v]) { dist[v] = d + 1; pq.push({d + 1, v}); }
            }
            { // L
                int nd = (dir + 3) & 3;
                int v = cell * 4 + nd;
                if (d + 1 < dist[v]) { dist[v] = d + 1; pq.push({d + 1, v}); }
            }
        }
        size_t base = (size_t)src_state * NN;
        for (int dst_idx = 0; dst_idx < NN; dst_idx++) {
            int best = INT_MAX, bd = 0;
            for (int dd = 0; dd < 4; dd++) {
                int v = dst_idx * 4 + dd;
                if (dist[v] < best) { best = dist[v]; bd = dd; }
            }
            dijk_table[base + dst_idx] = {(short)min(best, 32000), (unsigned char)bd, 0};
        }
    }
}

// セグメント評価(ml置換の近似)
inline pair<int,int> segApprox(int sr, int sc, int sd, int tr, int tc, int ml) {
    int src_state = (sr * N + sc) * 4 + sd;
    int dst_idx = tr * N + tc;
    auto& e = dijk_table[(size_t)src_state * NN + dst_idx];
    int cost = e.cost;
    int end_dir = e.end_dir;
    if (ml < 2) return {cost, end_dir};
    int Fs = bfs_dist[sr][sc][tr][tc];
    int turns = cost - Fs;
    if (Fs == 0) return {cost, end_dir};
    int nruns = turns + 1;
    int avg = Fs / nruns;
    int rem = Fs % nruns;
    int sub = 0;
    for (int i = 0; i < nruns; i++) {
        int L = avg + (i < rem ? 1 : 0);
        sub += L / ml + L % ml;
    }
    return {turns + sub, end_dir};
}

int evalPermLenApprox(const vector<int>& perm, int ml) {
    int len = 0;
    int cr = 0, cc = 0, cdir = 1;
    for (int k : perm) {
        auto [c1, d1] = segApprox(cr, cc, cdir, ball_init[k].first, ball_init[k].second, ml);
        len += c1 + 1;
        cr = ball_init[k].first; cc = ball_init[k].second; cdir = d1;
        auto [c2, d2] = segApprox(cr, cc, cdir, cage_pos[k].first, cage_pos[k].second, ml);
        len += c2 + 1;
        cr = cage_pos[k].first; cc = cage_pos[k].second; cdir = d2;
    }
    return len;
}

// 出力用に Dijkstra を再実行して経路復元
vector<int> dijk_buf_dist;
vector<int> dijk_buf_par;
vector<char> dijk_buf_op;
string buildSegmentDijk(int sr, int sc, int sd, int tr, int tc, int& end_dir) {
    if ((int)dijk_buf_dist.size() != NN4) {
        dijk_buf_dist.assign(NN4, 0);
        dijk_buf_par.assign(NN4, 0);
        dijk_buf_op.assign(NN4, 0);
    }
    fill(dijk_buf_dist.begin(), dijk_buf_dist.end(), INT_MAX);
    fill(dijk_buf_par.begin(), dijk_buf_par.end(), -1);
    int src_state = (sr * N + sc) * 4 + sd;
    dijk_buf_dist[src_state] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, src_state});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dijk_buf_dist[u]) continue;
        int cell = u / 4, dir = u % 4;
        int r = cell / N, c = cell % N;
        if (canMove(r, c, dir)) {
            int nr = r + DI[dir], nc = c + DJ[dir];
            int v = (nr * N + nc) * 4 + dir;
            if (d + 1 < dijk_buf_dist[v]) {
                dijk_buf_dist[v] = d + 1;
                dijk_buf_par[v] = u;
                dijk_buf_op[v] = 'F';
                pq.push({d + 1, v});
            }
        }
        { int nd = (dir + 1) & 3; int v = cell * 4 + nd;
          if (d + 1 < dijk_buf_dist[v]) { dijk_buf_dist[v] = d + 1; dijk_buf_par[v] = u; dijk_buf_op[v] = 'R'; pq.push({d + 1, v}); } }
        { int nd = (dir + 3) & 3; int v = cell * 4 + nd;
          if (d + 1 < dijk_buf_dist[v]) { dijk_buf_dist[v] = d + 1; dijk_buf_par[v] = u; dijk_buf_op[v] = 'L'; pq.push({d + 1, v}); } }
    }
    int dst_idx = tr * N + tc;
    int best = INT_MAX, bd = 0;
    for (int dd = 0; dd < 4; dd++) {
        int v = dst_idx * 4 + dd;
        if (dijk_buf_dist[v] < best) { best = dijk_buf_dist[v]; bd = dd; }
    }
    end_dir = bd;
    string ops;
    int cur = dst_idx * 4 + bd;
    while (dijk_buf_par[cur] != -1) {
        ops += dijk_buf_op[cur];
        cur = dijk_buf_par[cur];
    }
    reverse(ops.begin(), ops.end());
    return ops;
}

string buildOps(const vector<int>& perm) {
    string ops;
    int cr = 0, cc = 0, cdir = 1;
    for (int k : perm) {
        int nd;
        ops += buildSegmentDijk(cr, cc, cdir, ball_init[k].first, ball_init[k].second, nd);
        ops += 'S';
        cr = ball_init[k].first; cc = ball_init[k].second; cdir = nd;
        ops += buildSegmentDijk(cr, cc, cdir, cage_pos[k].first, cage_pos[k].second, nd);
        ops += 'S';
        cr = cage_pos[k].first; cc = cage_pos[k].second; cdir = nd;
    }
    return ops;
}

string substituteMacro(const string& s, int ml) {
    if (ml < 2) return s;
    string out;
    out.reserve(s.size());
    int i = 0, n = (int)s.size();
    while (i < n) {
        if (s[i] == 'F') {
            int j = i;
            while (j < n && s[j] == 'F') j++;
            int run = j - i;
            int ps = run / ml, rem = run % ml;
            out.append(ps, 'P');
            out.append(rem, 'F');
            i = j;
        } else {
            out += s[i++];
        }
    }
    return out;
}

// プロローグ方式: M F^ml M + (0,0)復帰 + 向き戻し + 本体置換
string buildWithMacroProlog(const vector<int>& perm, int ml) {
    if (ml < 2) return buildOps(perm);
    int cr = 0, cc = 0, cdir = 1;
    string ops;
    ops += 'M';
    for (int i = 0; i < ml; i++) {
        ops += 'F';
        if (canMove(cr, cc, cdir)) { cr += DI[cdir]; cc += DJ[cdir]; }
    }
    ops += 'M';
    int nd;
    ops += buildSegmentDijk(cr, cc, cdir, 0, 0, nd);
    cdir = nd;
    int rD = (1 - cdir + 4) & 3;
    int lD = (cdir - 1 + 4) & 3;
    int turns = min(rD, lD);
    char tch = (rD <= lD) ? 'R' : 'L';
    string head(turns, tch);
    string body = buildOps(perm);
    return ops + substituteMacro(head + body, ml);
}

// インライン方式: 本体の最初のlen>=mlのF-runを M..M で囲み、それ以降を置換
string buildWithMacroInline(const vector<int>& perm, int ml) {
    if (ml < 2) return buildOps(perm);
    string body = buildOps(perm);
    int n = (int)body.size();
    int run_start = -1;
    for (int i = 0; i < n; ) {
        if (body[i] == 'F') {
            int j = i;
            while (j < n && body[j] == 'F') j++;
            if (j - i >= ml) { run_start = i; break; }
            i = j;
        } else i++;
    }
    if (run_start == -1) return buildWithMacroProlog(perm, ml);
    string result;
    result.reserve(n + 2);
    result.append(body, 0, run_start);
    result += 'M';
    result.append(body, run_start, ml);
    result += 'M';
    string tail = body.substr(run_start + ml);
    result += substituteMacro(tail, ml);
    return result;
}

// シミュレータ(検証用)
struct Sim {
    int r, c, dir, holding;
    vector<vector<int>> ball_at;
    vector<bool> done;
    int placed;
    string macro, rec_buffer;
    bool macro_registered, recording;
    int basic_count;
    bool halted;
    void init() {
        r = 0; c = 0; dir = 1; holding = -1;
        ball_at.assign(N, vector<int>(N, -1));
        for (int k = 0; k < M; k++) ball_at[ball_init[k].first][ball_init[k].second] = k;
        done.assign(M, false);
        placed = 0;
        macro.clear(); rec_buffer.clear();
        macro_registered = false; recording = false;
        basic_count = 0; halted = false;
    }
    void execBasic(char op) {
        if (halted) return;
        if (basic_count >= T) { halted = true; return; }
        basic_count++;
        if (recording) rec_buffer += op;
        if (op == 'F') { if (canMove(r, c, dir)) { r += DI[dir]; c += DJ[dir]; } }
        else if (op == 'R') dir = (dir + 1) & 3;
        else if (op == 'L') dir = (dir + 3) & 3;
        else if (op == 'S') {
            int on = ball_at[r][c];
            int new_at = holding;
            ball_at[r][c] = new_at;
            holding = on;
            if (on != -1 && cage_pos[on].first == r && cage_pos[on].second == c && done[on]) { done[on] = false; placed--; }
            if (new_at != -1 && cage_pos[new_at].first == r && cage_pos[new_at].second == c && !done[new_at]) { done[new_at] = true; placed++; }
        }
    }
    void execOp(char op) {
        if (halted) return;
        if (op == 'F' || op == 'R' || op == 'L' || op == 'S') execBasic(op);
        else if (op == 'M') {
            if (!recording) { recording = true; rec_buffer.clear(); }
            else { recording = false; macro = rec_buffer; macro_registered = true; }
        } else if (op == 'P') {
            if (macro_registered) {
                string m = macro;
                for (char ch : m) { if (halted) break; execBasic(ch); }
            }
        }
    }
    void run(const string& s) { for (char op : s) { if (halted) break; execOp(op); } }
};

double get_time() {
    static auto start = chrono::steady_clock::now();
    return chrono::duration<double>(chrono::steady_clock::now() - start).count();
}

template<typename Eval>
void runSA(vector<int>& perm, int& curLen, vector<int>& bestPerm, int& bestLen,
           Eval eval, double time_limit, mt19937& rng,
           double startTemp = 5.0, double endTemp = 0.1) {
    double Temp = startTemp;
    long long iter = 0;
    double t0 = get_time();
    double dur = time_limit - t0;
    if (dur <= 0) return;
    while (true) {
        if ((iter & 0xFFF) == 0) {
            double t = get_time();
            if (t > time_limit) break;
            double progress = (t - t0) / dur;
            Temp = startTemp * pow(endTemp / startTemp, progress);
        }
        iter++;
        int i = (int)(rng() % M), j = (int)(rng() % M);
        if (i == j) continue;
        int op = (int)(rng() % 3);
        int pi = i, pj = j;
        if (op == 0) {
            swap(perm[i], perm[j]);
        } else if (op == 1) {
            if (i > j) swap(i, j);
            reverse(perm.begin() + i, perm.begin() + j + 1);
            pi = i; pj = j;
        } else {
            int v = perm[i];
            perm.erase(perm.begin() + i);
            perm.insert(perm.begin() + j, v);
        }
        int newLen = eval(perm);
        int delta = newLen - curLen;
        bool accept = false;
        if (delta <= 0) accept = true;
        else {
            double r = (double)(rng() & 0xFFFFFF) / 16777216.0;
            if (Temp > 1e-9 && r < exp(-(double)delta / Temp)) accept = true;
        }
        if (accept) {
            curLen = newLen;
            if (curLen < bestLen) { bestLen = curLen; bestPerm = perm; }
        } else {
            if (op == 0) {
                swap(perm[pi], perm[pj]);
            } else if (op == 1) {
                reverse(perm.begin() + pi, perm.begin() + pj + 1);
            } else {
                int v = perm[pj];
                perm.erase(perm.begin() + pj);
                perm.insert(perm.begin() + pi, v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    get_time();

    cin >> N >> M >> T;
    v_wall.resize(N);
    for (auto& s : v_wall) cin >> s;
    h_wall.resize(N - 1);
    for (auto& s : h_wall) cin >> s;
    ball_init.resize(M);
    cage_pos.resize(M);
    for (int k = 0; k < M; k++) {
        int b, c, d, e;
        cin >> b >> c >> d >> e;
        ball_init[k] = {b, c};
        cage_pos[k] = {d, e};
    }

    precomputeBFS();
    precomputeDijk();

    vector<int> nn_perm;
    {
        vector<bool> used(M, false);
        int cr = 0, cc = 0;
        for (int step = 0; step < M; step++) {
            int best = -1, bestDist = INT_MAX;
            for (int k = 0; k < M; k++) {
                if (used[k]) continue;
                int d = bfs_dist[cr][cc][ball_init[k].first][ball_init[k].second];
                if (d < bestDist) { bestDist = d; best = k; }
            }
            used[best] = true;
            nn_perm.push_back(best);
            cr = cage_pos[best].first; cc = cage_pos[best].second;
        }
    }
    vector<int> naive_perm(M);
    iota(naive_perm.begin(), naive_perm.end(), 0);

    vector<int> perm = (evalPermLenApprox(nn_perm, 0) <= evalPermLenApprox(naive_perm, 0)) ? nn_perm : naive_perm;
    int curLen = evalPermLenApprox(perm, 0);
    vector<int> bestPerm = perm;
    int bestLen = curLen;

    mt19937 rng(20260530);

    const double TIME_LIMIT = 1.85;   // 本番ぶれ対応で 0.15s 安全余裕

    // SA1: マクロなし評価。短めに切ってSA2と後処理に余裕を残す
    const double T_SA1 = 0.4;
    runSA(perm, curLen, bestPerm, bestLen,
          [](const vector<int>& p){ return evalPermLenApprox(p, 0); },
          T_SA1, rng);

    // 各 ml に対し bestPerm のインライン構築結果のうち最小Aを採る
    int max_run = 0;
    {
        string base = buildOps(bestPerm);
        int cur = 0;
        for (char c : base) {
            if (c == 'F') { cur++; max_run = max(max_run, cur); }
            else cur = 0;
        }
    }
    int ml_max = max(2, min(2 * N, max_run + 2));

    int best_ml = 0;
    int best_A = INT_MAX;
    {
        string ops0 = buildOps(bestPerm);
        if ((int)ops0.size() <= T) {
            Sim sim; sim.init(); sim.run(ops0);
            if (sim.placed == M) { best_A = (int)ops0.size(); best_ml = 0; }
        }
    }
    for (int ml = 2; ml <= ml_max; ml++) {
        string ops = buildWithMacroInline(bestPerm, ml);
        if ((int)ops.size() > T) continue;
        Sim sim; sim.init(); sim.run(ops);
        if (sim.placed == M && (int)ops.size() < best_A) {
            best_A = (int)ops.size();
            best_ml = ml;
        }
    }

    // 後処理の単価を実測 (buildOps + Sim を1回)
    double t_meas = get_time();
    {
        string measure_ops = buildOps(bestPerm);
        Sim msim; msim.init(); msim.run(measure_ops);
    }
    double per_cand_cost = get_time() - t_meas;
    if (per_cand_cost < 1e-4) per_cand_cost = 1e-4;  // 下限ガード

    // 最終候補集合の規模を見積もる: 3 perm × (1 + 5 ml) = 18
    const int N_FINAL_CAND = 18;
    double est_phase4 = per_cand_cost * N_FINAL_CAND * 1.3;  // 30% safety

    double SA2_DEADLINE = TIME_LIMIT - est_phase4 - 0.05;
    if (SA2_DEADLINE < get_time() + 0.15) SA2_DEADLINE = get_time() + 0.15;

    // SA2: 最良 ml で再焼き
    vector<int> bestPerm2 = bestPerm;
    int bestLen2 = evalPermLenApprox(bestPerm, best_ml);
    int curLen2 = bestLen2;
    vector<int> perm2 = bestPerm;
    int ml_lock = best_ml;
    runSA(perm2, curLen2, bestPerm2, bestLen2,
          [&ml_lock](const vector<int>& p){ return evalPermLenApprox(p, ml_lock); },
          SA2_DEADLINE, rng);

    cerr << "N=" << N << " M=" << M << " T=" << T
         << " best_ml=" << best_ml << " bestLen2=" << bestLen2
         << " per_cand_ms=" << (int)(per_cand_cost*1000)
         << " sa2_dl=" << SA2_DEADLINE << endl;

    // 候補集合: bestPerm2 / naive / nn × {no-macro, ml ∈ [best_ml-2..best_ml+2]}
    vector<vector<int>> perm_set = {bestPerm2, naive_perm, nn_perm};
    int ml_lo = max(2, best_ml - 2);
    int ml_hi = min(ml_max, best_ml + 2);
    vector<string> candidates;
    for (auto& pp : perm_set) {
        candidates.push_back(buildOps(pp));
        for (int ml = ml_lo; ml <= ml_hi; ml++) {
            candidates.push_back(buildWithMacroInline(pp, ml));
        }
    }

    // 選択: V=M で A 最小
    string finalOps;
    int bestV = -1, bestAA = INT_MAX, bestBasic = INT_MAX;
    for (auto& ops_full : candidates) {
        string ops = ops_full;
        if ((int)ops.size() > T) ops = ops.substr(0, T);
        Sim sim; sim.init(); sim.run(ops);
        int V = sim.placed, A = (int)ops.size(), bc = sim.basic_count;
        bool better = false;
        if (V > bestV) better = true;
        else if (V == bestV) {
            if (V == M) { if (A < bestAA) better = true; }
            else { if (bc < bestBasic) better = true; }
        }
        if (better) {
            finalOps = ops;
            bestV = V; bestAA = A; bestBasic = bc;
        }
    }

    cerr << "FINAL V=" << bestV << "/" << M << " A=" << bestAA << endl;
    for (char c : finalOps) cout << c << '\n';
    return 0;
}
