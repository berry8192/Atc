#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define ll long long

// ===== 入力 =====
int N, M, K;
vector<string> c;

struct Pos {
    int h, w;
    Pos() : h(-1), w(-1) {}
    Pos(int a, int b) : h(a), w(b) {}
    int index() const { return h * N + w; }
    bool operator==(const Pos &o) const { return h == o.h && w == o.w; }
};
Pos d4[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
struct Door { int d, i, j, g; };
struct Switch { int p, q, s; };

inline bool isopen(int i, int j) { return 0 <= i && i < N && 0 <= j && j < N && c[i][j] == '.'; }
inline int deg(int i, int j) { int dd = 0; for (Pos dp : d4) if (isopen(i + dp.h, j + dp.w)) dd++; return dd; }
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

// ===== judge 同等 BFS で真の最小ターン数 T =====
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
        for (auto [di, dj] : {array<int, 2>{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
            int ni = i + di, nj = j + dj;
            if (!(0 <= ni && ni < N && 0 <= nj && nj < N)) continue;
            if (c[ni][nj] == '#') continue;
            int g;
            if (di == 1) g = dh[i][j];
            else if (di == -1) g = dh[ni][nj];
            else if (dj == 1) g = dv[i][j];
            else g = dv[ni][nj];
            if (!is_open(g, mask)) continue;
            if (dist[idx(mask, ni, nj)] == -1) { dist[idx(mask, ni, nj)] = d + 1; que.push_back({mask, ni, nj}); }
        }
        int s = sg[i][j];
        if (s != -1) {
            int nm = mask ^ (1 << s);
            if (dist[idx(nm, i, j)] == -1) { dist[idx(nm, i, j)] = d + 1; que.push_back({nm, i, j}); }
        }
    }
    return 0;
}
ll scoreOf(ll T) { return T > 0 ? (ll)llround(1e6 * log2((double)T / N)) : 1; }

// ===== 盤面解析 =====
Pos startP, goal;
vector<vector<int>> parentG, depthG;
vector<vector<int>> childrenL;  // index -> child indices
vector<int> tin, tout, subDep, subLeaf, subSize;
vector<array<int, 2>> nonTree;

bool inSub(int anc, int x) { return tin[anc] <= tin[x] && tin[x] <= tout[anc]; }

// ===== コーム構築(switches 0..DD-1, 1..DD-1 はゲート付き) =====
// k = 目標終端コリドー長(1=half, DD=full)。返り値: 成功なら true。
bool buildComb(int DD, int kGoal, vector<Door> &doors, vector<Switch> &switches) {
    doors.clear(); switches.clear();
    int S = DD - 1;  // ゲート付きスイッチ 1..DD-1
    bool haveWall = (DD < K);                 // bit DD..K-1 が未使用
    int wallType = haveWall ? (2 * DD + 1) : -1;  // 未使用 bit DD の閉扉 = 永久壁

    vector<char> usedEdge(2 * N * N, 0);
    auto addDoor = [&](int ah, int aw, int bh, int bw, int g) -> bool {
        int k = edgeKey(ah, aw, bh, bw);
        if (usedEdge[k]) return false;
        usedEdge[k] = 1; doors.push_back(mkDoor(ah, aw, bh, bw, g)); return true;
    };

    int goalIdx = goal.index(), hubIdx = startP.index();
    vector<int> gatedChildren;  // ゲート扉の「深い側」セル(非木辺の straddle 判定用)
    vector<char> claimed(N * N, 0);

    // --- goal 鎖(hub..goal)を予約: ここにはコーム扉を置かない ---
    vector<char> onGoalChain(N * N, 0);
    { int u = goalIdx; while (u >= 0) { onGoalChain[u] = 1; u = parentG[u / N][u % N]; } }
    int goalDepth = depthG[goal.h][goal.w];

    // --- 目標終端ゲート(長さ k): 親チェーンに終端パターン扉を直列 ---
    // i=0: トップ押下要求(2(DD-1)+1)。i>=1: bit(DD-1-i) 未押下(2(DD-1-i))。
    int k = min(kGoal, goalDepth);
    if (k < 1) k = 1;
    static int gc[24];
    gc[0] = goalIdx;
    { int gcur = goalIdx; for (int s = 0; s < k; s++) { int par = parentG[gc[s] / N][gc[s] % N]; if (par < 0) return false; gc[s + 1] = par; } }
    for (int i = 0; i < k; i++) {
        int g = (i == 0) ? (2 * (DD - 1) + 1) : (2 * (DD - 1 - i));
        addDoor(gc[i] / N, gc[i] % N, gc[i + 1] / N, gc[i + 1] % N, g);
        gatedChildren.push_back(gc[i]);
    }
    // goal 他進入辺封鎖
    for (Pos dp : d4) {
        int ni = goal.h + dp.h, nj = goal.w + dp.w;
        if (!isopen(ni, nj) || ni * N + nj == gc[1]) continue;
        if (wallType >= 0) addDoor(goal.h, goal.w, ni, nj, wallType);
    }
    // 内部 gc[1..k-1] 横道封鎖
    for (int i = 1; i < k; i++) {
        int x = gc[i], pv = gc[i - 1], nx = gc[i + 1];
        for (Pos dp : d4) {
            int yi = x / N + dp.h, yj = x % N + dp.w;
            if (!isopen(yi, yj)) continue;
            int y = yi * N + yj;
            if (y == pv || y == nx) continue;
            if (wallType >= 0) addDoor(x / N, x % N, yi, yj, wallType);
        }
    }
    for (int i = 0; i < k; i++) claimed[gc[i]] = 1;  // mouth gc[k] は claim しない

    // --- コーム根: goal 鎖の終端ゾーン外から分岐する非goal部分木で最大のもの ---
    int combRoot = -1, bestSD = -1;
    rep(i, N) rep(j, N) {
        if (!isopen(i, j)) continue;
        int id = i * N + j;
        if (onGoalChain[id] || claimed[id]) continue;
        int p = parentG[i][j];
        if (p < 0 || !onGoalChain[p]) continue;          // goal 鎖から枝分かれする根のみ
        if (depthG[p / N][p % N] >= goalDepth - k) continue;  // 終端ゾーンより浅い所のみ
        if (subSize[id] > bestSD) { bestSD = subSize[id]; combRoot = id; }
    }
    if (combRoot < 0) return false;

    // --- スパイン greedy: combRoot から木を降りながら分岐点でスイッチを枝出し ---
    vector<int> pocketRoots;
    auto usable = [&](int ch) {
        for (int pr : pocketRoots) if (inSub(pr, ch) || inSub(ch, pr)) return false;
        return true;
    };

    int cur = combRoot, placed = 0;
    while (placed < S) {
        vector<int> cand;
        for (int ch : childrenL[cur]) if (usable(ch)) cand.push_back(ch);
        if (cand.empty()) break;
        if ((int)cand.size() == 1) { cur = cand[0]; continue; }  // 自由廊下(扉なし)
        sort(all(cand), [&](int a, int b) { return subDep[a] > subDep[b]; });
        int bp = cur;  // 分岐点
        int cont = cand[0], pocket = cand[1];
        int m = placed + 1, bit = m - 1;
        addDoor(bp / N, bp % N, pocket / N, pocket % N, 2 * bit + 1);  // 枝: bit=1
        gatedChildren.push_back(pocket);
        int leaf = subLeaf[pocket];
        switches.push_back({leaf / N, leaf % N, m});
        pocketRoots.push_back(pocket);
        placed++;
        if (placed < S) {  // 最深スイッチの後ろには続行扉不要
            addDoor(bp / N, bp % N, cont / N, cont % N, 2 * bit);  // 続行: bit=0
            gatedChildren.push_back(cont);
        }
        cur = cont;
    }
    cerr << "  [DD=" << DD << "] combRoot depth=" << (combRoot>=0?depthG[combRoot/N][combRoot%N]:-1)
         << " spine placed=" << placed << "/" << S << " doors=" << doors.size() << "\n";
    if (placed < S) return false;

    // --- switch0(ゲートなし): 自由域の最深デッドエンド ---
    int best = -1, bestd = -1;
    rep(i, N) rep(j, N) {
        if (!isopen(i, j)) continue;
        int id = i * N + j;
        if (id == goalIdx || deg(i, j) != 1) continue;
        bool inPocket = false;
        for (int pr : pocketRoots) if (inSub(pr, id)) { inPocket = true; break; }
        if (inPocket) continue;
        bool isSw = false;
        for (auto &s : switches) if (s.p == i && s.q == j) { isSw = true; break; }
        if (isSw) continue;
        if (depthG[i][j] > bestd) { bestd = depthG[i][j]; best = id; }
    }
    if (best < 0) {  // フォールバック: 任意の自由マス
        rep(i, N) rep(j, N) if (isopen(i, j)) {
            int id = i * N + j; if (id == goalIdx) continue;
            bool bad = false; for (auto &s : switches) if (s.p == i && s.q == j) bad = true;
            for (int pr : pocketRoots) if (inSub(pr, id)) bad = true;
            if (!bad) { best = id; goto done; }
        }
        done:;
    }
    if (best < 0) return false;
    switches.push_back({best / N, best % N, 0});

    // --- ゲートを跨ぐ非木辺だけ永久壁で封鎖(A.cc方式)。wallType<0 は封鎖不可 ---
    int straddle = 0;
    for (auto &e : nonTree) {
        int u = e[0], v = e[1];
        bool cross = false;
        for (int g : gatedChildren) if (inSub(g, u) != inSub(g, v)) { cross = true; break; }
        if (!cross) continue;
        straddle++;
        if (usedEdge[edgeKey(u / N, u % N, v / N, v % N)]) continue;
        if (wallType >= 0) addDoor(u / N, u % N, v / N, v % N, wallType);
    }
    cerr << "  [DD=" << DD << "] straddle(nonTree across gates)=" << straddle
         << " wallType=" << wallType << " finalDoors=" << doors.size() << "\n";

    if ((int)doors.size() > M) return false;
    return true;
}

int main() {
    cin >> N >> M >> K;
    c.resize(N);
    rep(i, N) cin >> c[i];
    startP = Pos(0, 0); goal = Pos(N - 1, N - 1);

    // BFS 木
    parentG.assign(N, vector<int>(N, -1));
    depthG.assign(N, vector<int>(N, -1));
    {
        vector<int> q; int head = 0;
        depthG[0][0] = 0; q.push_back(0);
        while (head < (int)q.size()) {
            int id = q[head++], i = id / N, j = id % N;
            for (Pos dp : d4) {
                int ni = i + dp.h, nj = j + dp.w;
                if (!isopen(ni, nj) || depthG[ni][nj] != -1) continue;
                depthG[ni][nj] = depthG[i][j] + 1;
                parentG[ni][nj] = id; q.push_back(ni * N + nj);
            }
        }
    }
    // children
    childrenL.assign(N * N, {});
    rep(i, N) rep(j, N) if (isopen(i, j)) {
        int p = parentG[i][j];
        if (p >= 0) childrenL[p].push_back(i * N + j);
    }
    // Euler tin/tout
    tin.assign(N * N, -1); tout.assign(N * N, -1);
    {
        int tm = 0; vector<int> idx(N * N, 0), st;
        st.push_back(startP.index()); tin[startP.index()] = tm++;
        while (!st.empty()) {
            int u = st.back();
            if (idx[u] < (int)childrenL[u].size()) {
                int ch = childrenL[u][idx[u]++]; tin[ch] = tm++; st.push_back(ch);
            } else { tout[u] = tm++; st.pop_back(); }
        }
    }
    // subtree 最深葉
    subDep.assign(N * N, -1); subLeaf.assign(N * N, -1); subSize.assign(N * N, 0);
    {
        vector<int> order;
        rep(i, N) rep(j, N) if (isopen(i, j)) order.push_back(i * N + j);
        sort(all(order), [&](int a, int b) { return depthG[a / N][a % N] > depthG[b / N][b % N]; });
        for (int u : order) {
            subDep[u] = depthG[u / N][u % N]; subLeaf[u] = u; subSize[u] = 1;
            for (int ch : childrenL[u]) {
                if (subDep[ch] > subDep[u]) { subDep[u] = subDep[ch]; subLeaf[u] = subLeaf[ch]; }
                subSize[u] += subSize[ch];
            }
        }
    }
    // 非木辺
    rep(i, N) rep(j, N) {
        if (!isopen(i, j)) continue;
        int u = i * N + j;
        if (i + 1 < N && isopen(i + 1, j)) {
            int v = (i + 1) * N + j;
            if (parentG[i][j] != v && parentG[i + 1][j] != u) nonTree.push_back({u, v});
        }
        if (j + 1 < N && isopen(i, j + 1)) {
            int v = i * N + (j + 1);
            if (parentG[i][j] != v && parentG[i][j + 1] != u) nonTree.push_back({u, v});
        }
    }

    // DD・k を試して実測ベストを採用
    ll bestT = -1; vector<Door> bestDoors; vector<Switch> bestSw; int bestDD = 0, bestK = 0;
    for (int DD : {10, 9, 8}) {
        for (int k = DD; k >= 1; k--) {
            vector<Door> doors; vector<Switch> sw;
            if (!buildComb(DD, k, doors, sw)) continue;
            ll T = calc_T(doors, sw);
            cerr << "DD=" << DD << " k=" << k << " doors=" << doors.size() << " T=" << T << " score=" << scoreOf(T) << "\n";
            if (T > bestT) { bestT = T; bestDoors = doors; bestSw = sw; bestDD = DD; bestK = k; }
            break;  // k は大きいほど T 大(単調)。最初に build 成功した k を採用。
        }
    }

    if (bestT <= 0) { cout << 0 << "\n" << 0 << "\n"; return 0; }
    cerr << "CHOSEN DD=" << bestDD << " T=" << bestT << " score=" << scoreOf(bestT) << "\n";

    cout << bestDoors.size() << "\n";
    for (auto &d : bestDoors) cout << d.d << " " << d.i << " " << d.j << " " << d.g << "\n";
    cout << bestSw.size() << "\n";
    for (auto &s : bestSw) cout << s.p << " " << s.q << " " << s.s << "\n";
    return 0;
}
