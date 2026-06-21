#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define ll long long

// ===== タイマー =====
double TIME_LIMIT = 1850.0;
struct Timer {
    chrono::system_clock::time_point start;
    Timer() { start = chrono::system_clock::now(); }
    double ms() {
        auto cur = chrono::system_clock::now();
        return chrono::duration_cast<chrono::microseconds>(cur - start).count() / 1000.0;
    }
    double progress() { return ms() / TIME_LIMIT; }
};
Timer timer;

// ===== 乱数 =====
int seed = 1;
mt19937 mt(seed);
uniform_real_distribution<double> uni(0.0, 1.0);

// ===== 入力 =====
int N, M, K;
vector<string> c;

struct Pos {
    int h, w;
    Pos() : h(-1), w(-1) {}
    Pos(int hh, int ww) : h(hh), w(ww) {}
    int index() const { return h * N + w; }
    bool operator==(const Pos &o) const { return h == o.h && w == o.w; }
};
Pos d4[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

struct Door { int d, i, j, g; };
struct Switch { int p, q, s; };

inline bool isopen(int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < N && c[i][j] == '.';
}
inline int deg(int i, int j) {
    int dd = 0;
    for (Pos dp : d4) if (isopen(i + dp.h, j + dp.w)) dd++;
    return dd;
}
// 隣接2マス間の扉キー (0..2*N*N-1)
inline int edgeKey(int ah, int aw, int bh, int bw) {
    int d, i, j;
    if (aw == bw) { d = 0; i = min(ah, bh); j = aw; }
    else { d = 1; i = ah; j = min(aw, bw); }
    return d * N * N + i * N + j;
}
inline Door mkDoor(int ah, int aw, int bh, int bw, int g) {
    int d, i, j;
    if (aw == bw) { d = 0; i = min(ah, bh); j = aw; }
    else { d = 1; i = ah; j = min(aw, bw); }
    return {d, i, j, g};
}

// ===== 盤面解析(グローバル) =====
int DD;          // 使うスイッチ数(0..DD-1)。トップ = DD-1
int wallTypeG;   // 未使用スイッチ DD の閉扉 = 永久壁
Pos startP, goal;
vector<vector<int>> depthG, parentG;
vector<Pos> deadends;
vector<array<int, 4>> goalEdges;

// ===== スクラッチ配列(高速化) =====
static char claimedA[400];
static char usedEdgeA[800];
static char wallA[800];
static int distScratch[400];
static int bfsq[400];
static char visScratch[400];
static char seenScratch[400];

// BFS木の Euler in/out(部分木判定 O(1))と非木辺(サイクル辺)リスト
static int eulerIn[400], eulerOut[400];
vector<int> ntU, ntV, ntKey;
inline bool isDesc(int x, int a) { return eulerIn[a] <= eulerIn[x] && eulerIn[x] <= eulerOut[a]; }

// 開放盤面(扉・壁を無視)の BFS。dist[] にコピー(サイズ N*N)
void bfsOpenInto(Pos src, int *dist) {
    fill(dist, dist + N * N, -1);
    int head = 0, tail = 0;
    dist[src.index()] = 0;
    bfsq[tail++] = src.index();
    while (head < tail) {
        int id = bfsq[head++];
        int i = id / N, j = id % N;
        for (Pos dp : d4) {
            int ni = i + dp.h, nj = j + dp.w;
            if (!isopen(ni, nj)) continue;
            int nid = ni * N + nj;
            if (dist[nid] != -1) continue;
            dist[nid] = dist[id] + 1;
            bfsq[tail++] = nid;
        }
    }
}

// 永久壁(wA)を通れないとして入口から required 全てに到達できるか
bool connOK(const vector<Pos> &required, const char *wA) {
    fill(visScratch, visScratch + N * N, 0);
    int head = 0, tail = 0;
    visScratch[startP.index()] = 1;
    bfsq[tail++] = startP.index();
    while (head < tail) {
        int id = bfsq[head++];
        int i = id / N, j = id % N;
        for (Pos dp : d4) {
            int ni = i + dp.h, nj = j + dp.w;
            if (!isopen(ni, nj)) continue;
            int nid = ni * N + nj;
            if (visScratch[nid]) continue;
            if (wA[edgeKey(i, j, ni, nj)]) continue;
            visScratch[nid] = 1;
            bfsq[tail++] = nid;
        }
    }
    for (const Pos &r : required) if (!visScratch[r.index()]) return false;
    return true;
}

// コリドー幾何(純粋): 親チェーン cc[0..n], 条件扉, 壁エッジ を生成
bool genCorridor(int n, Pos P, Pos cc[], int condKey[], int condType[],
                 int wKey[], int wE[][4], int &nwall) {
    cc[0] = P;
    Pos cur = P;
    for (int s = 0; s < n; s++) {
        int par = parentG[cur.h][cur.w];
        if (par < 0) return false;
        cur = Pos(par / N, par % N);
        cc[s + 1] = cur;
    }
    for (int i = 0; i < n; i++) {
        int j = n - 1 - i;
        int g = (j == n - 1) ? (2 * j + 1) : (2 * j);
        condKey[i] = edgeKey(cc[i].h, cc[i].w, cc[i + 1].h, cc[i + 1].w);
        condType[i] = g;
    }
    nwall = 0;
    for (int i = 1; i < n; i++) {
        Pos x = cc[i], pv = cc[i - 1], nx = cc[i + 1];
        for (Pos dp : d4) {
            int yi = x.h + dp.h, yj = x.w + dp.w;
            if (!isopen(yi, yj)) continue;
            if ((yi == pv.h && yj == pv.w) || (yi == nx.h && yj == nx.w)) continue;
            wKey[nwall] = edgeKey(x.h, x.w, yi, yj);
            wE[nwall][0] = x.h; wE[nwall][1] = x.w; wE[nwall][2] = yi; wE[nwall][3] = yj;
            nwall++;
        }
    }
    return true;
}

// 割当 P[0..DD-1] から構築。feasible なら true、Thalf を返す。
// outDoors/outSw 非nullで実際の扉・スイッチを出力。
// k = ゴール終端コリドー長(1=half: トップ押下のみ, DD=full: 終端パターン全条件)
bool buildAssign(const vector<Pos> &P, int k, ll &Thalf,
                 vector<Door> *outDoors = nullptr, vector<Switch> *outSw = nullptr) {
    if (k < 1) k = 1;
    // 妥当性・重複
    fill(seenScratch, seenScratch + N * N, 0);
    rep(n, DD) {
        Pos p = P[n];
        if (p.h < 0 || p.h >= N || p.w < 0 || p.w >= N) return false;
        if (c[p.h][p.w] != '.') return false;
        if (seenScratch[p.index()]) return false;
        seenScratch[p.index()] = 1;
    }
    fill(claimedA, claimedA + N * N, 0);
    fill(usedEdgeA, usedEdgeA + 2 * N * N, 0);
    fill(wallA, wallA + 2 * N * N, 0);

    if (outDoors) outDoors->clear();
    int doorCount = 0;

    // ゲート child セル(=各ゲート扉の木の子側)を集める。これを跨ぐ非木辺だけ後で封鎖。
    int gateCells[80]; int nGate = 0;

    // ===== ゴール終端コリドー(長さ k): ゲート扉のみ =====
    // 親チェーン gc[0]=goal .. gc[k]=mouth。i=0:トップ押下(2(DD-1)+1)、i>=1:bit(DD-1-i)未押下(2(DD-1-i))。
    Pos gc[16];
    gc[0] = goal;
    {
        Pos gcur = goal;
        for (int s = 0; s < k; s++) {
            int par = parentG[gcur.h][gcur.w];
            if (par < 0) return false;
            gcur = Pos(par / N, par % N);
            gc[s + 1] = gcur;
        }
    }
    for (int i = 0; i < k; i++) {
        int key = edgeKey(gc[i].h, gc[i].w, gc[i + 1].h, gc[i + 1].w);
        int g = (i == 0) ? (2 * (DD - 1) + 1) : (2 * (DD - 1 - i));
        if (usedEdgeA[key]) return false;
        usedEdgeA[key] = 1; doorCount++;
        gateCells[nGate++] = gc[i].index();
        if (outDoors) outDoors->push_back(mkDoor(gc[i].h, gc[i].w, gc[i + 1].h, gc[i + 1].w, g));
    }
    for (int i = 0; i < k; i++) claimedA[gc[i].index()] = 1;  // mouth gc[k] は claim しない
    int goalMouthIdx = gc[k].index();
    int outGateGoal = gc[k - 1].index();  // ゴール終端コリドーの最外ゲート child

    // ===== スイッチコリドー: 条件扉のみ(横道壁は張らない) =====
    Pos cc[16];
    int condKey[16], condType[16], wKey[40], wE[40][4], nwall;
    int outGate[16];  // 各スイッチコリドーの最外ゲート child セル
    for (int n = 1; n < DD; n++) {
        if (!genCorridor(n, P[n], cc, condKey, condType, wKey, wE, nwall)) return false;
        for (int i = 0; i < n; i++) {
            if (claimedA[cc[i].index()]) return false;
            if (cc[i] == goal) return false;
        }
        if (claimedA[cc[n].index()]) return false;  // mouth 未claim
        for (int i = 0; i < n; i++) if (usedEdgeA[condKey[i]]) return false;
        for (int i = 0; i < n; i++) {
            usedEdgeA[condKey[i]] = 1;
            doorCount++;
            gateCells[nGate++] = cc[i].index();
            if (outDoors) outDoors->push_back(mkDoor(cc[i].h, cc[i].w, cc[i + 1].h, cc[i + 1].w, condType[i]));
        }
        outGate[n] = cc[n - 1].index();
        for (int i = 0; i < n; i++) claimedA[cc[i].index()] = 1;
    }
    // ハブ(switch0)が他のコリドー内部にめり込んでいないか
    if (claimedA[P[0].index()]) return false;

    // ===== デッドロック回避: 各ゲート部分木に「他者」を入れない =====
    // (入れると勇者がその閉扉を通らされ、必要状態が作れず到達不能になる)
    for (int n = 1; n < DD; n++) {
        int a = outGate[n];
        for (int m = 0; m < DD; m++) {
            if (m == n) continue;
            if (isDesc(P[m].index(), a)) return false;  // 他ポケット/ハブが奥に
        }
        if (isDesc(goal.index(), a)) return false;
        if (isDesc(goalMouthIdx, a)) return false;  // ゴール接近路が奥に
    }
    for (int m = 0; m < DD; m++)
        if (isDesc(P[m].index(), outGateGoal)) return false;  // ポケット/ハブがゴール終端奥に

    // ===== 非木辺の壁パス: ゲート(木辺)を跨ぐサイクル辺だけを封鎖 =====
    // 木の枝/行止りは自動で封じられる。非木辺除去は連結を壊さない(connOK 不要)。
    for (size_t e = 0; e < ntKey.size(); e++) {
        int u = ntU[e], v = ntV[e];
        bool cross = false;
        for (int g = 0; g < nGate; g++) {
            int a = gateCells[g];
            if (isDesc(u, a) != isDesc(v, a)) { cross = true; break; }
        }
        if (!cross) continue;
        int key = ntKey[e];
        if (usedEdgeA[key]) continue;
        usedEdgeA[key] = 1; wallA[key] = 1; doorCount++;
        if (outDoors) outDoors->push_back(mkDoor(u / N, u % N, v / N, v % N, wallTypeG));
    }

    // 予算
    if (doorCount > M) return false;

    if (outSw) {
        outSw->clear();
        rep(n, DD) outSw->push_back({P[n].h, P[n].w, n});
    }

    // ===== Thalf(開放盤面距離) =====
    bfsOpenInto(P[0], distScratch);
    auto D0 = [&](Pos p) { return (ll)distScratch[p.index()]; };
    ll T = D0(startP) + (1LL << (DD - 1));
    for (int m = 1; m < DD - 1; m++) T += (1LL << (DD - 1 - m)) * D0(P[m]);
    T += D0(P[DD - 1]);
    // dTop[goal]
    static int distTopArr[400];
    bfsOpenInto(P[DD - 1], distTopArr);
    T += (ll)distTopArr[goal.index()];
    Thalf = T;
    return true;
}

// 貪欲初期解(難しい順 7→1, hub 最後)。connを毎回チェック。失敗時 topSw<DD-1。
// 返り値: 配置できた switch 数(= topSw+1)。P を埋める。
int greedyInit(vector<Pos> &P) {
    P.assign(DD, Pos(-1, -1));
    fill(claimedA, claimedA + N * N, 0);
    fill(usedEdgeA, usedEdgeA + 2 * N * N, 0);
    fill(wallA, wallA + 2 * N * N, 0);
    for (auto &e : goalEdges) usedEdgeA[edgeKey(e[0], e[1], e[2], e[3])] = 1;
    vector<char> usedDead(deadends.size(), 0);
    int doorCount = 0;
    int goalGate = (int)goalEdges.size();
    vector<Pos> placed;

    Pos cc[16];
    int condKey[16], condType[16], wKey[40], wE[40][4], nwall;

    int placedCnt = 0;
    // 1..DD-1 を難しい順
    for (int n = DD - 1; n >= 1; n--) {
        int bestIdx = -1, bestWalls = INT_MAX, bestDepth = -1;
        Pos bestCC[16]; int bcondKey[16], bcondType[16], bwKey[40], bwE[40][4], bnwall = 0;
        rep(di, deadends.size()) {
            if (usedDead[di]) continue;
            Pos cand = deadends[di];
            if (depthG[cand.h][cand.w] < n) continue;
            if (!genCorridor(n, cand, cc, condKey, condType, wKey, wE, nwall)) continue;
            bool ok = true;
            for (int i = 0; i < n && ok; i++) {
                if (claimedA[cc[i].index()] || cc[i] == goal) ok = false;
            }
            if (!ok || claimedA[cc[n].index()]) continue;
            for (int i = 0; i < n && ok; i++) if (usedEdgeA[condKey[i]]) ok = false;
            for (int i = 0; i < nwall && ok; i++) if (usedEdgeA[wKey[i]]) ok = false;
            if (!ok) continue;
            if (doorCount + n + nwall + goalGate > M) continue;
            // 連結性(壁を一時追加して判定)
            for (int i = 0; i < nwall; i++) wallA[wKey[i]] = 1;
            vector<Pos> req = placed; req.push_back(goal); req.push_back(cand);
            bool cok = connOK(req, wallA);
            for (int i = 0; i < nwall; i++) wallA[wKey[i]] = 0;
            if (!cok) continue;
            int dep = depthG[cand.h][cand.w];
            // 深い行き止まり優先(高位の長コリドー用に深さを使い切る)
            if (nwall < bestWalls || (nwall == bestWalls && dep > bestDepth)) {
                bestWalls = nwall; bestDepth = dep; bestIdx = di;
                for (int i = 0; i <= n; i++) bestCC[i] = cc[i];
                for (int i = 0; i < n; i++) { bcondKey[i] = condKey[i]; bcondType[i] = condType[i]; }
                bnwall = nwall;
                for (int i = 0; i < nwall; i++) { bwKey[i] = wKey[i]; for (int k = 0; k < 4; k++) bwE[i][k] = wE[i][k]; }
            }
        }
        if (bestIdx < 0) break;  // 配置失敗 → チェーン途切れ
        // commit
        for (int i = 0; i < n; i++) { usedEdgeA[bcondKey[i]] = 1; doorCount++; }
        for (int i = 0; i < bnwall; i++) { usedEdgeA[bwKey[i]] = 1; wallA[bwKey[i]] = 1; doorCount++; }
        for (int i = 0; i < n; i++) claimedA[bestCC[i].index()] = 1;
        P[n] = deadends[bestIdx];
        usedDead[bestIdx] = 1;
        placed.push_back(P[n]);
        placedCnt++;
    }
    // hub(switch0): 未使用・未claim のデッドエンドで P[1] から最遠
    {
        int refIdx = (DD >= 2 && P[1].h >= 0) ? P[1].index() : startP.index();
        bfsOpenInto(Pos(refIdx / N, refIdx % N), distScratch);
        int bestIdx = -1, bestD = -1;
        rep(di, deadends.size()) {
            if (usedDead[di]) continue;
            Pos cand = deadends[di];
            if (claimedA[cand.index()]) continue;
            int dd = distScratch[cand.index()];
            if (dd > bestD) { bestD = dd; bestIdx = di; }
        }
        if (bestIdx >= 0) { P[0] = deadends[bestIdx]; placedCnt++; }
    }
    return placedCnt;
}

// judge と同等の実 BFS で最小ターン数 T を計算(リーク検証用)
ll calc_T(const vector<Door> &doors, const vector<Switch> &sw) {
    vector<vector<int>> dh(N, vector<int>(N, -1)), dv(N, vector<int>(N, -1)), sg(N, vector<int>(N, -1));
    for (auto &d : doors) { if (d.d == 0) dh[d.i][d.j] = d.g; else dv[d.i][d.j] = d.g; }
    for (auto &s : sw) sg[s.p][s.q] = s.s;
    auto is_open = [&](int g, int mask) {
        if (g == -1) return true;
        int k = g / 2;
        return ((mask >> k) & 1) == (g & 1);
    };
    int SZ = 1 << K;
    vector<int> dist((size_t)SZ * N * N, -1);
    auto idx = [&](int m, int i, int j) { return ((size_t)m * N + i) * N + j; };
    deque<array<int, 3>> que;
    dist[idx(0, 0, 0)] = 0;
    que.push_back({0, 0, 0});
    while (!que.empty()) {
        auto [mask, i, j] = que.front(); que.pop_front();
        int d = dist[idx(mask, i, j)];
        if (i == N - 1 && j == N - 1) return d;
        for (auto [di, dj] : {array<int,2>{-1,0}, {1,0}, {0,-1}, {0,1}}) {
            int ni = i + di, nj = j + dj;
            if (!(0 <= ni && ni < N && 0 <= nj && nj < N)) continue;
            if (c[ni][nj] == '#') continue;
            int g;
            if (di == 1) g = dh[i][j];
            else if (di == -1) g = dh[ni][nj];
            else if (dj == 1) g = dv[i][j];
            else g = dv[ni][nj];
            if (!is_open(g, mask)) continue;
            if (dist[idx(mask, ni, nj)] == -1) {
                dist[idx(mask, ni, nj)] = d + 1;
                que.push_back({mask, ni, nj});
            }
        }
        int s = sg[i][j];
        if (s != -1) {
            int nmask = mask ^ (1 << s);
            if (dist[idx(nmask, i, j)] == -1) {
                dist[idx(nmask, i, j)] = d + 1;
                que.push_back({nmask, i, j});
            }
        }
    }
    return 0;
}

ll scoreOf(ll T) { return T > 0 ? (ll)llround(1e6 * log2((double)T / N)) : 1; }

// ゴール終端コリドー長 k による T 倍率(ルーラー到達ランク比)
//  k=1:1.0(half), k=2:1.5, k=3:1.75, ..., →2.0(full)
double ratioK(int k) { return k <= 1 ? 1.0 : (2.0 - pow(2.0, -(double)(k - 1))); }
const int KCAP = 6;  // k はこの辺で頭打ち(ratio(6)=1.969、full 2.0 とほぼ同じ)

// 割当の実効エネルギー = Thalf × ratio(最大feasible k)。
// 「距離(Thalf)」と「full化(k)」を同時最適化(壁を減らして k を稼ぐ等)。
bool evalEnergy(const vector<Pos> &asg, ll &energy) {
    int mk = -1; ll th = 0;
    int kmax = min(DD, KCAP);
    for (int kk = kmax; kk >= 1; kk--) {
        if (buildAssign(asg, kk, th)) { mk = kk; break; }
    }
    if (mk < 0) return false;
    energy = (ll)(th * ratioK(mk));
    return true;
}

// dd 段の焼きなましを deadline_ms まで実行。best 割当と Thalf を返す。
bool runAnneal(int dd, int wtype, double deadline_ms, vector<Pos> &best, ll &bestT) {
    DD = dd; wallTypeG = wtype;
    vector<Pos> P;
    int placed = greedyInit(P);
    ll curE;
    if (placed < dd || (int)P.size() < dd || !evalEnergy(P, curE)) {
        // ランダム探索で feasible 初期解を探す
        bool found = false;
        if ((int)deadends.size() >= dd) {
            vector<int> idxs(deadends.size());
            iota(all(idxs), 0);
            for (int tries = 0; tries < 100000 && !found; tries++) {
                shuffle(all(idxs), mt);
                P.assign(dd, Pos(-1, -1));
                rep(n, dd) P[n] = deadends[idxs[n]];
                if (evalEnergy(P, curE)) found = true;
            }
        }
        if (!found) return false;
    }
    best = P; bestT = curE;
    vector<Pos> cur = P;
    double start_temp = 2000.0, end_temp = 5.0;
    int nd = (int)deadends.size();
    double start0 = timer.ms();
    double span = max(1.0, deadline_ms - start0);
    while (true) {
        double now = timer.ms();
        if (now >= deadline_ms) break;
        double prog = (now - start0) / span;
        if (prog > 1.0) prog = 1.0;
        vector<Pos> nx = cur;
        if (mt() % 2 == 0) { int t = mt() % dd; nx[t] = deadends[mt() % nd]; }
        else { int a = mt() % dd, b = mt() % dd; swap(nx[a], nx[b]); }
        ll nE;
        if (!evalEnergy(nx, nE)) continue;
        double temp = start_temp * pow(end_temp / start_temp, prog);
        if (nE >= curE || uni(mt) < exp((double)(nE - curE) / temp)) {
            cur = nx; curE = nE;
            if (curE > bestT) { bestT = curE; best = cur; }
        }
    }
    return true;
}

int main() {
    cin >> N >> M >> K;
    c.resize(N);
    rep(i, N) cin >> c[i];
    startP = Pos(0, 0);
    goal = Pos(N - 1, N - 1);

    DD = 8;
    wallTypeG = 2 * DD + 1;  // 未使用スイッチ DD(=8)の閉扉 = 17

    // 入口からの BFS 木
    depthG.assign(N, vector<int>(N, -1));
    parentG.assign(N, vector<int>(N, -1));
    {
        int head = 0, tail = 0;
        depthG[0][0] = 0;
        bfsq[tail++] = 0;
        while (head < tail) {
            int id = bfsq[head++];
            int i = id / N, j = id % N;
            for (Pos dp : d4) {
                int ni = i + dp.h, nj = j + dp.w;
                if (!isopen(ni, nj) || depthG[ni][nj] != -1) continue;
                depthG[ni][nj] = depthG[i][j] + 1;
                parentG[ni][nj] = id;
                bfsq[tail++] = ni * N + nj;
            }
        }
    }
    // BFS木の Euler in/out(反復DFS)
    {
        vector<vector<int>> children(N * N);
        rep(i, N) rep(j, N) {
            if (c[i][j] != '.') continue;
            int p = parentG[i][j];
            if (p >= 0) children[p].push_back(i * N + j);
        }
        fill(eulerIn, eulerIn + N * N, 0);
        fill(eulerOut, eulerOut + N * N, -1);
        int t = 0;
        vector<pair<int, int>> st;
        eulerIn[0] = t++;
        st.push_back({0, 0});
        while (!st.empty()) {
            auto &pr = st.back();
            if (pr.second < (int)children[pr.first].size()) {
                int ch = children[pr.first][pr.second++];
                eulerIn[ch] = t++;
                st.push_back({ch, 0});
            } else {
                eulerOut[pr.first] = t - 1;
                st.pop_back();
            }
        }
    }
    // 非木辺(サイクル辺)リスト
    rep(i, N) rep(j, N) {
        if (c[i][j] != '.') continue;
        int id = i * N + j;
        if (isopen(i, j + 1)) {
            int nid = i * N + (j + 1);
            if (!(parentG[i][j] == nid || parentG[i][j + 1] == id)) {
                ntU.push_back(id); ntV.push_back(nid); ntKey.push_back(edgeKey(i, j, i, j + 1));
            }
        }
        if (isopen(i + 1, j)) {
            int nid = (i + 1) * N + j;
            if (!(parentG[i][j] == nid || parentG[i + 1][j] == id)) {
                ntU.push_back(id); ntV.push_back(nid); ntKey.push_back(edgeKey(i, j, i + 1, j));
            }
        }
    }
    // ゴールを通らずに入口から到達できるマス
    vector<vector<int>> reachNoGoal(N, vector<int>(N, 0));
    {
        int head = 0, tail = 0;
        reachNoGoal[0][0] = 1;
        bfsq[tail++] = 0;
        while (head < tail) {
            int id = bfsq[head++];
            int i = id / N, j = id % N;
            for (Pos dp : d4) {
                int ni = i + dp.h, nj = j + dp.w;
                if (!isopen(ni, nj) || reachNoGoal[ni][nj]) continue;
                if (ni == goal.h && nj == goal.w) continue;
                reachNoGoal[ni][nj] = 1;
                bfsq[tail++] = ni * N + nj;
            }
        }
    }
    // 行き止まり列挙
    rep(i, N) rep(j, N) {
        if (c[i][j] != '.') continue;
        if ((i == 0 && j == 0) || (i == N - 1 && j == N - 1)) continue;
        if (!reachNoGoal[i][j]) continue;
        if (deg(i, j) == 1) deadends.push_back({i, j});
    }
    // ゴール隣接エッジ
    for (Pos dp : d4) {
        int ni = goal.h + dp.h, nj = goal.w + dp.w;
        if (isopen(ni, nj)) goalEdges.push_back({goal.h, goal.w, ni, nj});
    }

    // ===== d=9 と d=8 を時間分割で焼きなまし、MEASURED で良い方を採用 =====
    vector<Pos> best9, best8;
    ll t9 = -1, t8 = -1;
    bool ok9 = runAnneal(9, 19, 950.0, best9, t9);
    bool ok8 = runAnneal(8, 17, 1800.0, best8, t8);

    ll bestMeasured = -1, bestThalf = 0;
    int bestDD = 0, bestK = 1;
    vector<Door> bestDoors;
    vector<Switch> bestSw;
    auto consider = [&](bool ok, vector<Pos> &asg, int dd, int wtype) {
        if (!ok) return;
        DD = dd; wallTypeG = wtype;
        ll th;
        // 高→低で、build可能かつ calc_T>0(実ゲームで到達可能)な最大 k を採用。
        // k=DD(完全終端状態)は最終経路がゲートで塞がれ到達不能になり得るため calc_T で検証。
        int kcapL = min(dd, KCAP);
        for (int kk = kcapL; kk >= 1; kk--) {
            if (!buildAssign(asg, kk, th)) continue;
            vector<Door> doors;
            vector<Switch> sw;
            buildAssign(asg, kk, th, &doors, &sw);
            ll meas = calc_T(doors, sw);
            if (meas <= 0) continue;  // 到達不能はスキップ
            if (meas > bestMeasured) {
                bestMeasured = meas; bestThalf = th; bestDD = dd;
                bestDoors = doors; bestSw = sw; bestK = kk;
            }
            break;  // 最大の到達可能 k
        }
    };
    consider(ok8, best8, 8, 17);
    consider(ok9, best9, 9, 19);

    if (bestMeasured < 0) {  // 最終手段
        cout << 0 << "\n" << 0 << "\n";
        return 0;
    }
    cerr << "CHOSEN DD=" << bestDD << " K=" << bestK << " doors=" << bestDoors.size()
         << " THEORY_half T=" << bestThalf << " score=" << scoreOf(bestThalf)
         << " | MEASURED T=" << bestMeasured << " score=" << scoreOf(bestMeasured)
         << " | d9ok=" << ok9 << "(T" << t9 << ") d8ok=" << ok8 << "(T" << t8 << ")\n";

    cout << bestDoors.size() << "\n";
    for (auto &d : bestDoors) cout << d.d << " " << d.i << " " << d.j << " " << d.g << "\n";
    cout << bestSw.size() << "\n";
    for (auto &s : bestSw) cout << s.p << " " << s.q << " " << s.s << "\n";
    return 0;
}
