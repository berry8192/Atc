// AHC066 お片付けロボット
// 構成:
//   1. 正確なシミュレータ(M/P/ネスト・打ち切り対応)
//   2. 全点間BFSキャッシュ
//   3. 区間補完(壁BFS最短 + 同方向ラン圧縮 + 最小回転)
//   4. 1個ずつ運搬戦略(初期位置→かご)
//   5. 訪問順の焼きなまし(swap / 2-opt / or-opt)
//   6. フォールバック: ナイーブ(入力順)・最近傍貪欲
// 出力前に A<=T を保証(超過時は切り詰め)

#include <bits/stdc++.h>
#include <chrono>
using namespace std;

int N, M, T;
vector<string> v_wall, h_wall;
const int DI[] = {-1, 0, 1, 0};   // 0=up 1=right 2=down 3=left
const int DJ[] = {0, 1, 0, -1};
vector<pair<int,int>> ball_init, cage_pos;

inline bool canMove(int r, int c, int d) {
    if (d == 0) return r > 0 && h_wall[r-1][c] == '0';
    if (d == 1) return c < N-1 && v_wall[r][c] == '0';
    if (d == 2) return r < N-1 && h_wall[r][c] == '0';
    return c > 0 && v_wall[r][c-1] == '0';
}

// 全点BFS: bfs_dist[sr][sc][r][c], bfs_prev_d[sr][sc][r][c]
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

// 経路を path_buf に格納(方向列)
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

// 文字列を構築せずに長さ + 終了向きだけ返す(SA高速評価用)
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

// 操作文字列を構築
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

// 順列に対する総操作長(各種Sを含む)を計算
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

// 順列から操作文字列を構築
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

// シミュレータ: 仕様の正確な写し
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
                // マクロは登録完了後の不変文字列。再生中はそれをそのまま走らせる。
                // 記録中なら execBasic 側で rec_buffer に追加される。
                string m = macro;
                for (char ch : m) {
                    if (halted) break;
                    execBasic(ch);
                }
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

    // 初期順列1: 最近傍貪欲(現在位置→次のボール初期位置で近い物)
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
    // 初期順列2: 入力順
    vector<int> naive_perm(M);
    iota(naive_perm.begin(), naive_perm.end(), 0);

    // 短い方をSA初期解に
    vector<int> perm = (evalPermLen(nn_perm) <= evalPermLen(naive_perm)) ? nn_perm : naive_perm;

    int curLen = evalPermLen(perm);
    vector<int> bestPerm = perm;
    int bestLen = curLen;

    // SA
    mt19937 rng(20260530);
    const double TIME_LIMIT = 1.8;
    const double startTemp = 5.0, endTemp = 0.1;
    double Temp = startTemp;

    long long iter = 0;
    while (true) {
        if ((iter & 0xFFF) == 0) {
            double t = get_time();
            if (t > TIME_LIMIT) break;
            double progress = t / TIME_LIMIT;
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

        int newLen = evalPermLen(perm);
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
            // Undo
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

    cerr << "iter=" << iter << " bestLen=" << bestLen << " T=" << T << " M=" << M << " N=" << N << endl;

    // 出力候補を集めて V=M を満たす中で A 最小を選ぶ
    auto eval_final = [&](const string& ops) -> pair<int,int> {
        Sim sim;
        sim.init();
        sim.run(ops);
        return {sim.placed, (int)ops.size()};
    };

    vector<string> candidates;
    candidates.push_back(buildOps(bestPerm));
    candidates.push_back(buildOps(naive_perm));
    candidates.push_back(buildOps(nn_perm));

    // A<=T で V=M を満たす中で A 最小、なければ V 最大→basic_count最小
    string finalOps;
    int bestV = -1, bestA = INT_MAX;
    int bestBasic = INT_MAX;
    for (auto& ops : candidates) {
        string clipped = ops;
        if ((int)clipped.size() > T) clipped = clipped.substr(0, T);
        auto [V, A] = eval_final(clipped);
        Sim sim; sim.init(); sim.run(clipped);
        int bc = sim.basic_count;
        bool better = false;
        if (V > bestV) better = true;
        else if (V == bestV) {
            if (V == M) { if (A < bestA) better = true; }
            else { if (bc < bestBasic) better = true; }
        }
        if (better) {
            finalOps = clipped;
            bestV = V; bestA = A; bestBasic = bc;
        }
    }

    cerr << "FINAL V=" << bestV << "/" << M << " A=" << bestA << " bc=" << bestBasic << endl;

    for (char c : finalOps) cout << c << '\n';
    return 0;
}
