// AHC066 お片付けロボット — C.cc
// B.cc(訪問順SA) に、固定マクロ F^ml の登録 + 本体 F-run の P置換を後段で重ね、
// さらに ml を固定した2段目SAを行う構成。
//
// 構成:
//   1. 全点間BFSキャッシュ
//   2. 訪問順SA(マクロなし評価) … 1段目
//   3. 1段目 bestPerm に対して ml ∈ [2..K] を試して最適 ml を見つける
//      評価軸: M + F^ml + M + back-path + 本体(F-run置換後)
//   4. ml を固定した2段目SA(置換後の評価関数で長さを最小化)
//   5. 全候補をシミュレータで検証し、V=M を満たす中で A 最小を出力
//   6. A>T のときは切り詰め

#include <bits/stdc++.h>
#include <chrono>
using namespace std;

int N, M, T;
vector<string> v_wall, h_wall;
const int DI[] = {-1, 0, 1, 0};
const int DJ[] = {0, 1, 0, -1};
vector<pair<int,int>> ball_init, cage_pos;

inline bool canMove(int r, int c, int d) {
    if (d == 0) return r > 0 && h_wall[r-1][c] == '0';
    if (d == 1) return c < N-1 && v_wall[r][c] == '0';
    if (d == 2) return r < N-1 && h_wall[r][c] == '0';
    return c > 0 && v_wall[r][c-1] == '0';
}

vector<vector<vector<vector<short>>>> bfs_dist;
vector<vector<vector<vector<char>>>> bfs_prev_d;

void precomputeBFS() {
    bfs_dist.assign(N, vector<vector<vector<short>>>(N, vector<vector<short>>(N, vector<short>(N, -1))));
    bfs_prev_d.assign(N, vector<vector<vector<char>>>(N, vector<vector<char>>(N, vector<char>(N, -1))));
    for (int sr = 0; sr < N; sr++) for (int sc = 0; sc < N; sc++) {
        auto& dist = bfs_dist[sr][sc];
        auto& prev = bfs_prev_d[sr][sc];
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
                prev[nr][nc] = (char)d;
                q.push({nr, nc});
            }
        }
    }
}

vector<int> path_buf;
void getPath(int sr, int sc, int tr, int tc) {
    path_buf.clear();
    auto& prev = bfs_prev_d[sr][sc];
    int cr = tr, cc = tc;
    while (!(cr == sr && cc == sc)) {
        int d = prev[cr][cc];
        if (d < 0) break;
        path_buf.push_back(d);
        cr -= DI[d]; cc -= DJ[d];
    }
    reverse(path_buf.begin(), path_buf.end());
}

struct SegRes { int len; int dir; };

SegRes segLenDir(int sr, int sc, int sdir, int tr, int tc) {
    getPath(sr, sc, tr, tc);
    int len = 0, curDir = sdir;
    int n = (int)path_buf.size();
    int i = 0;
    while (i < n) {
        int d = path_buf[i];
        int run = 1;
        while (i + run < n && path_buf[i + run] == d) run++;
        int rD = (d - curDir + 4) & 3;
        int lD = (curDir - d + 4) & 3;
        len += min(rD, lD) + run;
        curDir = d;
        i += run;
    }
    return {len, curDir};
}

// ml >= 2 で F-run を P置換した長さを返す
SegRes segLenDirML(int sr, int sc, int sdir, int tr, int tc, int ml) {
    getPath(sr, sc, tr, tc);
    int len = 0, curDir = sdir;
    int n = (int)path_buf.size();
    int i = 0;
    while (i < n) {
        int d = path_buf[i];
        int run = 1;
        while (i + run < n && path_buf[i + run] == d) run++;
        int rD = (d - curDir + 4) & 3;
        int lD = (curDir - d + 4) & 3;
        len += min(rD, lD);
        if (ml >= 2) len += run / ml + run % ml;
        else len += run;
        curDir = d;
        i += run;
    }
    return {len, curDir};
}

string buildSegment(int sr, int sc, int sdir, int tr, int tc, int& finalDir) {
    getPath(sr, sc, tr, tc);
    string ops;
    int curDir = sdir;
    int n = (int)path_buf.size();
    int i = 0;
    while (i < n) {
        int d = path_buf[i];
        int run = 1;
        while (i + run < n && path_buf[i + run] == d) run++;
        int rD = (d - curDir + 4) & 3;
        int lD = (curDir - d + 4) & 3;
        int turns = min(rD, lD);
        char tch = (rD <= lD) ? 'R' : 'L';
        for (int j = 0; j < turns; j++) ops += tch;
        for (int j = 0; j < run; j++) ops += 'F';
        curDir = d;
        i += run;
    }
    finalDir = curDir;
    return ops;
}

int evalPermLen(const vector<int>& perm) {
    int len = 0;
    int cr = 0, cc = 0, cdir = 1;
    for (int k : perm) {
        auto s1 = segLenDir(cr, cc, cdir, ball_init[k].first, ball_init[k].second);
        len += s1.len + 1;
        cr = ball_init[k].first; cc = ball_init[k].second; cdir = s1.dir;
        auto s2 = segLenDir(cr, cc, cdir, cage_pos[k].first, cage_pos[k].second);
        len += s2.len + 1;
        cr = cage_pos[k].first; cc = cage_pos[k].second; cdir = s2.dir;
    }
    return len;
}

int evalPermLenML(const vector<int>& perm, int ml) {
    int len = 0;
    int cr = 0, cc = 0, cdir = 1;
    for (int k : perm) {
        auto s1 = segLenDirML(cr, cc, cdir, ball_init[k].first, ball_init[k].second, ml);
        len += s1.len + 1;
        cr = ball_init[k].first; cc = ball_init[k].second; cdir = s1.dir;
        auto s2 = segLenDirML(cr, cc, cdir, cage_pos[k].first, cage_pos[k].second, ml);
        len += s2.len + 1;
        cr = cage_pos[k].first; cc = cage_pos[k].second; cdir = s2.dir;
    }
    return len;
}

string buildOps(const vector<int>& perm) {
    string ops;
    int cr = 0, cc = 0, cdir = 1;
    for (int k : perm) {
        int nd;
        ops += buildSegment(cr, cc, cdir, ball_init[k].first, ball_init[k].second, nd);
        ops += 'S';
        cr = ball_init[k].first; cc = ball_init[k].second; cdir = nd;
        ops += buildSegment(cr, cc, cdir, cage_pos[k].first, cage_pos[k].second, nd);
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

// マクロを登録 → (0,0)へ復帰 → 向きを右(=1)に戻して本体を貼る
string buildWithMacro(const vector<int>& perm, int ml) {
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
    ops += buildSegment(cr, cc, cdir, 0, 0, nd);
    cdir = nd;

    // 向きを右(=1)に戻す(本体は dir=1 想定で構築されているため)
    int rD = (1 - cdir + 4) & 3;
    int lD = (cdir - 1 + 4) & 3;
    int turns = min(rD, lD);
    char tch = (rD <= lD) ? 'R' : 'L';
    string head(turns, tch);

    string body = buildOps(perm);
    return ops + substituteMacro(head + body, ml);
}

// シミュレータ
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
        for (int k = 0; k < M; k++)
            ball_at[ball_init[k].first][ball_init[k].second] = k;
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
        if (op == 'F') {
            if (canMove(r, c, dir)) { r += DI[dir]; c += DJ[dir]; }
        } else if (op == 'R') {
            dir = (dir + 1) & 3;
        } else if (op == 'L') {
            dir = (dir + 3) & 3;
        } else if (op == 'S') {
            int on = ball_at[r][c];
            int new_at = holding;
            ball_at[r][c] = new_at;
            holding = on;
            if (on != -1 && cage_pos[on].first == r && cage_pos[on].second == c && done[on]) {
                done[on] = false; placed--;
            }
            if (new_at != -1 && cage_pos[new_at].first == r && cage_pos[new_at].second == c && !done[new_at]) {
                done[new_at] = true; placed++;
            }
        }
    }

    void execOp(char op) {
        if (halted) return;
        if (op == 'F' || op == 'R' || op == 'L' || op == 'S') {
            execBasic(op);
        } else if (op == 'M') {
            if (!recording) { recording = true; rec_buffer.clear(); }
            else { recording = false; macro = rec_buffer; macro_registered = true; }
        } else if (op == 'P') {
            if (macro_registered) {
                string m = macro;
                for (char ch : m) { if (halted) break; execBasic(ch); }
            }
        }
    }

    void run(const string& s) {
        for (char op : s) { if (halted) break; execOp(op); }
    }
};

double get_time() {
    static auto start = chrono::steady_clock::now();
    return chrono::duration<double>(chrono::steady_clock::now() - start).count();
}

// SA 共通ループ。eval は perm 全体の評価。time_limit までに最良を返す。
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
            if (curLen < bestLen) {
                bestLen = curLen;
                bestPerm = perm;
            }
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
    path_buf.reserve(N * N);

    // 初期順列: 最近傍貪欲(ボール初期位置基準)とナイーブ(入力順)
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

    vector<int> perm = (evalPermLen(nn_perm) <= evalPermLen(naive_perm)) ? nn_perm : naive_perm;
    int curLen = evalPermLen(perm);
    vector<int> bestPerm1 = perm;
    int bestLen1 = curLen;

    mt19937 rng(20260530);

    // 1段目SA: マクロなし評価で訪問順を縮める
    const double T_SA1 = 0.9;
    runSA(perm, curLen, bestPerm1, bestLen1,
          [](const vector<int>& p){ return evalPermLen(p); },
          T_SA1, rng);

    // 1段目 bestPerm を起点に最良 ml を探索
    auto candA = [&](const string& ops, int* basic_out = nullptr, int* V_out = nullptr) -> int {
        Sim sim; sim.init(); sim.run(ops);
        if (basic_out) *basic_out = sim.basic_count;
        if (V_out) *V_out = sim.placed;
        return (int)ops.size();
    };

    int max_run = 0;
    {
        string base = buildOps(bestPerm1);
        int cur = 0;
        for (char c : base) {
            if (c == 'F') { cur++; max_run = max(max_run, cur); }
            else cur = 0;
        }
    }

    int best_ml_for_perm1 = 0;
    int best_A_for_perm1 = (int)buildOps(bestPerm1).size();
    int ml_max = max(2, min(2 * N, max_run + 2));
    for (int ml = 2; ml <= ml_max; ml++) {
        string ops = buildWithMacro(bestPerm1, ml);
        int V; int basic;
        int A = candA(ops, &basic, &V);
        if ((int)ops.size() > T) continue;
        if (V == M && A < best_A_for_perm1) {
            best_A_for_perm1 = A;
            best_ml_for_perm1 = ml;
        }
    }

    // 2段目SA: best_ml で評価する(perm はSA1の最終状態を続けて使う)
    vector<int> bestPerm2 = bestPerm1;
    int bestLen2 = (best_ml_for_perm1 >= 2)
                       ? evalPermLenML(bestPerm1, best_ml_for_perm1)
                       : bestLen1;
    int curLen2 = bestLen2;
    vector<int> perm2 = bestPerm1;

    if (best_ml_for_perm1 >= 2) {
        const double T_SA2 = 1.75;
        int ml = best_ml_for_perm1;
        runSA(perm2, curLen2, bestPerm2, bestLen2,
              [&](const vector<int>& p){ return evalPermLenML(p, ml); },
              T_SA2, rng);
    }

    cerr << "N=" << N << " M=" << M << " T=" << T
         << " bestLen1=" << bestLen1 << " best_ml=" << best_ml_for_perm1
         << " A_ml1=" << best_A_for_perm1
         << " bestLen2=" << bestLen2 << endl;

    // 候補集合: 3初期(SA1 / SA2 / naive / nn) × {no-macro, multiple ml}
    vector<vector<int>> perm_set = {bestPerm1, bestPerm2, naive_perm, nn_perm};
    vector<string> candidates;
    for (auto& pp : perm_set) {
        candidates.push_back(buildOps(pp));
        for (int ml = 2; ml <= ml_max; ml++) {
            candidates.push_back(buildWithMacro(pp, ml));
        }
    }

    // V=M を満たす中で A 最小、なければ V 最大→basic_count 最小
    string finalOps;
    int bestV = -1, bestA = INT_MAX, bestBasic = INT_MAX;
    for (auto& ops_full : candidates) {
        string ops = ops_full;
        if ((int)ops.size() > T) ops = ops.substr(0, T);
        Sim sim; sim.init(); sim.run(ops);
        int V = sim.placed, A = (int)ops.size(), bc = sim.basic_count;
        bool better = false;
        if (V > bestV) better = true;
        else if (V == bestV) {
            if (V == M) { if (A < bestA) better = true; }
            else { if (bc < bestBasic) better = true; }
        }
        if (better) {
            finalOps = ops;
            bestV = V; bestA = A; bestBasic = bc;
        }
    }

    cerr << "FINAL V=" << bestV << "/" << M << " A=" << bestA << " bc=" << bestBasic << endl;

    for (char c : finalOps) cout << c << '\n';
    return 0;
}
