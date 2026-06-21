#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

using namespace std;
// using namespace atcoder;

// std::ofstream outputFile("log.csv");

// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) outputFile << pvv[i] << ", ";
// 	outputFile<< pvv[pvv.size()-1] <<endl;
// }
// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) cout << pvv[i] << ", ";
// 	// rep(i, pvv.size()-1) cout<< pvv[i]/20 SP << pvv[i]%20 <<endl;
// 	cout<< pvv[pvv.size()-1] <<endl;
// }

// template <class T>void PVV(T pvv) {
// 	rep(i, pvv.size()){
//         // outputFile<< "i: " << i <<endl;
// 		rep(j, pvv[i].size()-1){
// 			outputFile<< pvv[i][j] << ", ";
// 		}
// 		if(pvv[i].size()) outputFile<< pvv[i][pvv[i].size()-1] <<endl;
// 	}
// }
// template <class T> void PM(T pm) {
//     // cout<< "{";
// 	for(auto m : pm){
// 		outputFile<< "(" << m.first << "->" << m.second << "), ";
// 	}
// 	// cout<< "}";
// 	outputFile<<endl;
// }

int imax = 2147483647;
long long llimax = 9223372036854775807;

// 焼きなましの定数
chrono::system_clock::time_point start, current;
double TIME_LIMIT = 1900.0;
// double TIME_LIMIT=190.0;
double start_temp = 10000000.0;
double end_temp = 10000.0;

struct Timer {
    chrono::_V2::system_clock::time_point start;

    Timer() { start = chrono::system_clock::now(); }
    double progress() {
        chrono::_V2::system_clock::time_point current =
            chrono::system_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(current - start)
                   .count() /
               TIME_LIMIT;
    }
};
Timer timer;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed = 1;
mt19937 mt(seed);

int N;
int HEIGHT, WIDTH;

// 構造体
struct Pos {
    int h;
    int w;

    Pos() {};
    Pos(int hh, int ww) {
        h = hh;
        w = ww;
    }

    bool is_oob() {
        // assert(0<=h);
        // assert(h<n);
        // assert(0<=w);
        // assert(w<=h);
        return !(0 <= h && h < HEIGHT && 0 <= w && w < WIDTH);
    }
    int manhattan(Pos pos) { return abs(h - pos.h) + abs(w - pos.w); }
    int index() { return h * WIDTH + w; }
    void print() { cout << "(" << h << ", " << w << ")" << endl; }
    // 受け取った近傍でPosを作る
    vector<Pos> around_pos(const vector<Pos> &dir) {
        vector<Pos> rtn;
        Pos new_pos;
        for (int i = 0; i < dir.size(); i++) {
            new_pos = {h + dir[i].h, w + dir[i].w};
            if (!new_pos.is_oob())
                rtn.emplace_back(new_pos);
        }
        return rtn;
    }

    bool operator<(const Pos &in) const {
        return h != in.h ? h < in.h : w < in.w;
    };
    bool operator==(const Pos &cpos) const {
        return (h == cpos.h && w == cpos.w);
    };
    Pos operator+(const Pos pos) {
        Pos rtn;
        rtn.h = h + pos.h;
        rtn.w = w + pos.w;
        return rtn;
    }
    Pos operator-(const Pos pos) {
        Pos rtn;
        rtn.h = h - pos.h;
        rtn.w = w - pos.w;
        return rtn;
    }
};

struct Grid {};

Pos itop(int idx) { return {idx / WIDTH, idx % WIDTH}; }

Pos d4[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

int M, K;          // M: 扉の最大枚数(=50), K: スイッチの種類数(=10)
vector<string> c;  // 盤面

void inpt() {
    cin >> N >> M >> K;
    HEIGHT = WIDTH = N;
    c.resize(N);
    rep(i, N) cin >> c[i];
}

// 1本の扉
struct Door {
    int d, i, j, g;  // 向き, 座標, 型
};
// 1つのスイッチ
struct Switch {
    int p, q, s;  // 座標, 種類
};

// 隣接2マス間の扉の (d,i,j) を求める
int edgeKey(int ah, int aw, int bh, int bw) {
    int d, i, j;
    if (aw == bw) { d = 0; i = min(ah, bh); j = aw; }
    else { d = 1; i = ah; j = min(aw, bw); }
    return d * N * N + i * N + j;
}

int gK;  // スイッチ種類数(=K)を calcT 用に保持

// 真の最小行動回数 T を BFS で計算(状態 = (mask, 位置))。到達不能は 0。
long long calcT(const vector<Door> &doors, const vector<Switch> &switches) {
    int NN = N * N, SZ = 1 << gK;
    static vector<int> door_h, door_v, swg, dist, vis;
    static int stamp = 0;
    if ((int)dist.size() != SZ * NN) {
        dist.assign(SZ * NN, 0);
        vis.assign(SZ * NN, 0);
        door_h.assign(NN, -1);
        door_v.assign(NN, -1);
        swg.assign(NN, -1);
    }
    fill(door_h.begin(), door_h.end(), -1);
    fill(door_v.begin(), door_v.end(), -1);
    fill(swg.begin(), swg.end(), -1);
    for (auto &d : doors) {
        if (d.d == 0) door_h[d.i * N + d.j] = d.g;
        else door_v[d.i * N + d.j] = d.g;
    }
    for (auto &s : switches) swg[s.p * N + s.q] = s.s;
    stamp++;
    auto openg = [&](int g, int mask) {
        if (g < 0) return true;
        int k = g >> 1;
        return ((mask >> k) & 1) == (g & 1);
    };
    static vector<int> que;
    que.clear();
    vis[0] = stamp;
    dist[0] = 0;
    que.push_back(0);
    int goalpos = (N - 1) * N + (N - 1);
    for (size_t h = 0; h < que.size(); h++) {
        int st = que[h];
        int mask = st / NN, pos = st % NN;
        int i = pos / N, j = pos % N, d = dist[st];
        if (pos == goalpos) return d;
        if (i + 1 < N && c[i + 1][j] == '.') {
            if (openg(door_h[pos], mask)) {
                int np = st + N;
                if (vis[np] != stamp) { vis[np] = stamp; dist[np] = d + 1; que.push_back(np); }
            }
        }
        if (i - 1 >= 0 && c[i - 1][j] == '.') {
            if (openg(door_h[pos - N], mask)) {
                int np = st - N;
                if (vis[np] != stamp) { vis[np] = stamp; dist[np] = d + 1; que.push_back(np); }
            }
        }
        if (j + 1 < N && c[i][j + 1] == '.') {
            if (openg(door_v[pos], mask)) {
                int np = st + 1;
                if (vis[np] != stamp) { vis[np] = stamp; dist[np] = d + 1; que.push_back(np); }
            }
        }
        if (j - 1 >= 0 && c[i][j - 1] == '.') {
            if (openg(door_v[pos - 1], mask)) {
                int np = st - 1;
                if (vis[np] != stamp) { vis[np] = stamp; dist[np] = d + 1; que.push_back(np); }
            }
        }
        int s = swg[pos];
        if (s >= 0) {
            int np = (mask ^ (1 << s)) * NN + pos;
            if (vis[np] != stamp) { vis[np] = stamp; dist[np] = d + 1; que.push_back(np); }
        }
    }
    return 0;
}

int main() {
    start = chrono::system_clock::now();
    inpt();
    gK = K;

    const int D = 9;  // 有効スイッチ数(0..8)。型 K-1=9 は未使用(壁予備)

    auto isopen = [&](int i, int j) {
        return 0 <= i && i < N && 0 <= j && j < N && c[i][j] == '.';
    };
    auto deg = [&](int i, int j) {
        int dd = 0;
        for (Pos dp : d4)
            if (isopen(i + dp.h, j + dp.w)) dd++;
        return dd;
    };

    Pos startP(0, 0), goal(N - 1, N - 1);

    // 入口からの BFS 木(depth, parent)
    vector<vector<int>> depth(N, vector<int>(N, -1));
    vector<vector<int>> parent(N, vector<int>(N, -1));  // 親マスの index、無しは -1
    {
        queue<Pos> que;
        depth[0][0] = 0;
        que.push(startP);
        while (!que.empty()) {
            Pos p = que.front();
            que.pop();
            for (Pos dp : d4) {
                int ni = p.h + dp.h, nj = p.w + dp.w;
                if (!isopen(ni, nj) || depth[ni][nj] != -1) continue;
                depth[ni][nj] = depth[p.h][p.w] + 1;
                parent[ni][nj] = p.h * N + p.w;
                que.push({ni, nj});
            }
        }
    }

    // ゴールを通らずに入口から到達できるマスを求める(ゴール裏のポケットを除外するため)
    vector<vector<int>> reachNoGoal(N, vector<int>(N, 0));
    {
        queue<Pos> que;
        reachNoGoal[0][0] = 1;
        que.push(startP);
        while (!que.empty()) {
            Pos p = que.front();
            que.pop();
            for (Pos dp : d4) {
                int ni = p.h + dp.h, nj = p.w + dp.w;
                if (!isopen(ni, nj) || reachNoGoal[ni][nj]) continue;
                if (ni == goal.h && nj == goal.w) continue;  // ゴールは通らない
                reachNoGoal[ni][nj] = 1;
                que.push({ni, nj});
            }
        }
    }

    // 行き止まり(deg1)を列挙(入口・ゴール・ゴール裏を除く)
    vector<Pos> deadends;
    rep(i, N) rep(j, N) {
        if (c[i][j] != '.') continue;
        if (i == 0 && j == 0) continue;
        if (i == N - 1 && j == N - 1) continue;
        if (!reachNoGoal[i][j]) continue;  // ゴール裏は使わない
        if (deg(i, j) == 1) deadends.push_back({i, j});
    }

    const int wallType = 2 * D + 1;  // 未使用スイッチ D(=K-1)の閉扉 = 永久壁
    int goalIdx = goal.h * N + goal.w;
    int startIdx = 0;

    // BFS木の children と Euler in/out(部分木判定用)
    vector<vector<int>> children(N * N);
    rep(i, N) rep(j, N) {
        if (!isopen(i, j)) continue;
        int p = parent[i][j];
        if (p >= 0) children[p].push_back(i * N + j);
    }
    vector<int> tin(N * N, -1), tout(N * N, -1);
    {
        int tm = 0;
        vector<int> idx(N * N, 0), st;
        st.push_back(startIdx);
        tin[startIdx] = tm++;
        while (!st.empty()) {
            int u = st.back();
            if (idx[u] < (int)children[u].size()) {
                int c = children[u][idx[u]++];
                tin[c] = tm++;
                st.push_back(c);
            } else {
                tout[u] = tm++;
                st.pop_back();
            }
        }
    }
    auto inSub = [&](int anc, int x) {
        return tin[anc] <= tin[x] && tin[x] <= tout[anc];
    };

    // 非木辺(サイクル辺)を列挙
    vector<array<int, 2>> nonTree;
    rep(i, N) rep(j, N) {
        if (!isopen(i, j)) continue;
        int u = i * N + j;
        if (i + 1 < N && isopen(i + 1, j)) {
            int v = (i + 1) * N + j;
            if (parent[i][j] != v && parent[i + 1][j] != u) nonTree.push_back({u, v});
        }
        if (j + 1 < N && isopen(i, j + 1)) {
            int v = i * N + (j + 1);
            if (parent[i][j] != v && parent[i][j + 1] != u) nonTree.push_back({u, v});
        }
    }

    // ===== 構築試行(ランダム化)。返り値 topSw、out に doors/switches =====
    auto attempt = [&](mt19937 &rng, int jit, const vector<int> &forced,
                       vector<Door> &outDoors, vector<Switch> &outSwitches,
                       vector<int> &outAssign) -> int {
        outAssign.assign(D, -1);
        vector<Door> doors;
        set<int> usedEdge;
        auto addDoor = [&](int ah, int aw, int bh, int bw, int g) -> bool {
            int d, i, j;
            if (aw == bw) { d = 0; i = min(ah, bh); j = aw; }
            else { d = 1; i = ah; j = min(aw, bw); }
            int key = d * N * N + i * N + j;
            if (usedEdge.count(key)) return false;
            usedEdge.insert(key);
            doors.push_back({d, i, j, g});
            return true;
        };
        vector<char> claimedIdx(N * N, 0), usedDeadIdx(N * N, 0);
        set<int> wallSet;
        vector<Switch> switches;

    // ターゲット T へ向かう排他コリドーを構築。gtypes[i] = 内側から i 番目のゲートの型。
    // 壁 = コリドー辺 e_i を跨ぐ非木辺のみ(深い枝の再接続もこれで検出)。
    auto buildCorridor = [&](int T, const vector<int> &gtypes, vector<int> &chain,
                             vector<array<int, 5>> &gates, vector<array<int, 4>> &walls) -> bool {
        int need = (int)gtypes.size();
        chain.assign(1, T);
        int cur = T;
        for (int s = 0; s < need; s++) {
            int p = parent[cur / N][cur % N];
            if (p < 0) return false;
            chain.push_back(p);
            cur = p;
        }
        for (int i = 0; i < need; i++) {
            int ci = chain[i];
            if (claimedIdx[ci]) return false;
            if (ci == startIdx) return false;
            if (ci == goalIdx && !(i == 0 && T == goalIdx)) return false;
        }
        if (claimedIdx[chain[need]]) return false;  // 入口が他コリドー内部なら不可
        gates.clear();
        for (int i = 0; i < need; i++) {
            int a = chain[i], b = chain[i + 1];
            if (usedEdge.count(edgeKey(a / N, a % N, b / N, b % N))) return false;
            gates.push_back({a / N, a % N, b / N, b % N, gtypes[i]});
        }
        walls.clear();
        for (auto &e : nonTree) {
            int u = e[0], v = e[1];
            bool straddle = false;
            for (int i = 0; i < need; i++)
                if (inSub(chain[i], u) != inSub(chain[i], v)) { straddle = true; break; }
            if (!straddle) continue;
            int k = edgeKey(u / N, u % N, v / N, v % N);
            if (usedEdge.count(k) && !wallSet.count(k)) return false;  // 非壁扉と衝突
            walls.push_back({u / N, u % N, v / N, v % N});
        }
        return true;
    };
    auto newWallCount = [&](vector<array<int, 4>> &walls) {
        int c = 0;
        for (auto &w : walls)
            if (!wallSet.count(edgeKey(w[0], w[1], w[2], w[3]))) c++;
        return c;
    };
    auto commitCorridor = [&](vector<int> &chain, vector<array<int, 5>> &gates,
                              vector<array<int, 4>> &walls) {
        for (auto &g : gates) addDoor(g[0], g[1], g[2], g[3], g[4]);
        for (auto &w : walls) {
            int k = edgeKey(w[0], w[1], w[2], w[3]);
            if (!wallSet.count(k)) { addDoor(w[0], w[1], w[2], w[3], wallType); wallSet.insert(k); }
        }
        for (int i = 0; i + 1 < (int)chain.size(); i++) claimedIdx[chain[i]] = 1;
    };

    // スイッチ n のゲート型(ハノイ規則): 内側 i=0 → bit_{n-1} 押下, それ以外 → 未押下
    auto switchTypes = [&](int n) {
        vector<int> g;
        for (int i = 0; i < n; i++) {
            int j = n - 1 - i;
            g.push_back(j == n - 1 ? (2 * j + 1) : (2 * j));
        }
        return g;
    };
    // ゴール終端ゲート型(チェーン 0..t): switch t 押下 + switch 0..t-1 未押下(t+1枚)
    auto goalTypes = [&](int t) {
        vector<int> g;
        for (int k = 0; k <= t; k++) g.push_back(k == t ? (2 * k + 1) : (2 * k));
        return g;
    };

    // 行き止まりを深さ降順に(極大点優先)。ローカルコピー da で試行ごとに使う
    vector<Pos> da = deadends;
    sort(all(da),
         [&](const Pos &a, const Pos &b) { return depth[a.h][a.w] > depth[b.h][b.w]; });

    // --- ゴール優先: ゴールのスパイン(終端ゲート領域)を予約。スイッチはここを避ける ---
    vector<char> goalReserved(N * N, 0);
    {
        vector<int> gch;
        gch.push_back(goalIdx);
        int cur = goalIdx;
        for (int s = 0; s < D; s++) {  // 最大 D=9 ゲート分
            int p = parent[cur / N][cur % N];
            if (p < 0) break;
            gch.push_back(p);
            cur = p;
        }
        int outer = gch.back();
        if (outer == startIdx && gch.size() >= 2) outer = gch[gch.size() - 2];
        rep(idx, N * N)
            if (isopen(idx / N, idx % N) && inSub(outer, idx)) goalReserved[idx] = 1;
    }
    vector<int> placedOuter;  // 各スイッチの最外ゲートセル(部分木の互いに素判定用)

    // --- スイッチ 1..t をガード(switch0 は need=0 なので最後に最適配置) ---
    int topSw = 0;  // switch 0 は最後に必ず配置
    for (int n = 1; n < D; n++) {
        vector<int> gt = switchTypes(n);
        long long bestKey = LLONG_MAX;
        int bestT = -1;
        vector<int> bch;
        vector<array<int, 5>> bg;
        vector<array<int, 4>> bw;
        for (Pos P : da) {
            int Pi = P.h * N + P.w;
            if (forced[n] >= 0 && Pi != forced[n]) continue;  // 摂動: 固定ポケット
            if (usedDeadIdx[Pi] || claimedIdx[Pi] || goalReserved[Pi]) continue;
            vector<int> chain;
            vector<array<int, 5>> gates;
            vector<array<int, 4>> walls;
            if (!buildCorridor(Pi, gt, chain, gates, walls)) continue;
            // コリドーセルがゴール予約域に入らない
            bool inReserved = false;
            for (int i = 0; i < n; i++)
                if (goalReserved[chain[i]]) { inReserved = true; break; }
            if (inReserved) continue;
            // 最外ゲートセル Cn の部分木が ゴール / 他スイッチ と互いに素か
            int Cn = (n >= 1) ? chain[n - 1] : Pi;
            if (inSub(Cn, goalIdx)) continue;  // ゴールを n のゲート奥に閉じ込めない
            bool bad = false;
            for (int Cm : placedOuter)
                if (inSub(Cm, Cn) || inSub(Cn, Cm)) { bad = true; break; }
            if (bad) continue;
            int cost = n + newWallCount(walls);
            // ゴールゲート(t+1 枚)分を残して予算判定
            if ((int)doors.size() + cost + (n + 1) > M) continue;
            int dep = depth[P.h][P.w];
            // 選択キー: 壁本数(=cost)優先・深い順、jit でランダム摂動
            long long key = (long long)cost * 1000 + dep + (jit ? (int)(rng() % jit) : 0);
            if (key < bestKey) {
                bestKey = key; bestT = Pi;
                bch = chain; bg = gates; bw = walls;
            }
        }
        if (bestT < 0) break;  // 連番打ち切り
        commitCorridor(bch, bg, bw);
        usedDeadIdx[bestT] = 1;
        switches.push_back({bestT / N, bestT % N, n});
        placedOuter.push_back((n >= 1) ? bch[n - 1] : bestT);
        outAssign[n] = bestT;
        topSw = n;
    }

    // --- ゴール終端ゲート ---
    // ゴールの親チェーン上で、部分木にスイッチ(claim 済みセル)を含まない安全な範囲 maxSafe まで
    // ゲートを並べる(超えるとスイッチをゴールゲートの奥に閉じ込めデッドロックするため)。
    // m ゲート = switch topSw 押下 + 高位スイッチ unpressed(full に届かなくても partial)。
    int goalOuter = -1;  // ゴール最外ゲートセル(部分木 = ゴールゲート奥)
    if (topSw >= 0) {
        vector<int> claimedCells;
        rep(idx, N * N) if (claimedIdx[idx]) claimedCells.push_back(idx);
        int want = topSw + 1;
        vector<int> chain;
        chain.push_back(goalIdx);
        int cur = goalIdx, maxLen = 0;
        for (int s = 0; s < want; s++) {
            int p = parent[cur / N][cur % N];
            if (p < 0) break;
            chain.push_back(p);
            cur = p;
            maxLen++;
        }
        int maxSafe = 0;
        for (int i = 0; i < maxLen; i++) {
            int ci = chain[i];
            if (ci == startIdx) break;
            if (claimedIdx[ci] && ci != goalIdx) break;
            bool hasSwitch = false;
            for (int cc : claimedCells)
                if (inSub(ci, cc)) { hasSwitch = true; break; }
            if (hasSwitch) break;
            maxSafe++;
        }
        for (int m = min(want, maxSafe); m >= 1; m--) {
            vector<int> types;
            types.push_back(2 * topSw + 1);                       // switch topSw 押下
            for (int i = 1; i < m; i++) types.push_back(2 * (topSw - i));  // 高位 unpressed
            vector<int> ch;
            vector<array<int, 5>> gates;
            vector<array<int, 4>> walls;
            if (buildCorridor(goalIdx, types, ch, gates, walls) &&
                (int)doors.size() + (int)types.size() + newWallCount(walls) <= M) {
                commitCorridor(ch, gates, walls);
                goalOuter = ch[(int)ch.size() - 2];
                break;
            }
        }
    }

    // --- switch0(need=0)を最後に最適配置 ---
    // 目的: Σ_{m=1}^{topSw} 2^{dd-m} dist(P0,Pm) + dist(S,P0) + dist(P0,G) を最大化。
    // ただし初期状態(mask0)で到達可能(reach0)・未claim なマスのみ。
    {
        int ddl = topSw + 1;
        // ゲート奥(部分木)に入らない = 入口からの経路がゲートを跨がない安全マス。
        // ここなら switch0 を押した状態でも出入りでき、Hanoi が詰まない。
        vector<char> gatedMark(N * N, 0);
        for (int Cm : placedOuter)
            rep(idx, N * N) if (inSub(Cm, idx)) gatedMark[idx] = 1;
        if (goalOuter >= 0)
            rep(idx, N * N) if (inSub(goalOuter, idx)) gatedMark[idx] = 1;
        auto bfsF = [&](Pos s) {
            vector<vector<int>> d(N, vector<int>(N, -1));
            queue<Pos> q;
            d[s.h][s.w] = 0;
            q.push(s);
            while (!q.empty()) {
                Pos p = q.front();
                q.pop();
                for (Pos dp : d4) {
                    int ni = p.h + dp.h, nj = p.w + dp.w;
                    if (!isopen(ni, nj) || d[ni][nj] != -1) continue;
                    d[ni][nj] = d[p.h][p.w] + 1;
                    q.push({ni, nj});
                }
            }
            return d;
        };
        vector<Pos> Pm(ddl, Pos(-1, -1));
        for (auto &sw : switches) if (sw.s >= 1 && sw.s < ddl) Pm[sw.s] = Pos(sw.p, sw.q);
        vector<vector<vector<int>>> dPm(ddl);
        for (int m = 1; m < ddl; m++) if (Pm[m].h >= 0) dPm[m] = bfsF(Pm[m]);
        auto dS = bfsF(startP), dG = bfsF(goal);

        Pos best(-1, -1);
        long long bestObj = -1;
        rep(i, N) rep(j, N) {
            if (!isopen(i, j) || gatedMark[i * N + j] || claimedIdx[i * N + j]) continue;
            if (i == goal.h && j == goal.w) continue;
            bool isSite = false;
            for (auto &sw : switches) if (sw.p == i && sw.q == j) { isSite = true; break; }
            if (isSite) continue;
            long long obj = dS[i][j] + dG[i][j];
            bool ok = true;
            for (int m = 1; m < ddl; m++) {
                if (Pm[m].h < 0) continue;
                if (dPm[m][i][j] < 0) { ok = false; break; }
                obj += (1LL << (ddl - m)) * dPm[m][i][j];
            }
            if (ok && obj > bestObj) { bestObj = obj; best = Pos(i, j); }
        }
        if (best.h < 0) best = Pos(0, 0);  // フォールバック
        switches.push_back({best.h, best.w, 0});
    }

        outDoors = doors;
        outSwitches = switches;
        return topSw;
    };  // ===== end attempt =====

    // ===== 時間いっぱい探索: ランダム多スタート + 最良割当の接尾辞摂動(山登り) =====
    mt19937 rng(20260621u);
    vector<Door> bestD;
    vector<Switch> bestS;
    vector<int> bestAssign(D, -1);
    long long bestT = -1;
    int iters = 0, bestTop = 0, lastImp = 0;
    while (true) {
        current = chrono::system_clock::now();
        double el =
            chrono::duration_cast<chrono::milliseconds>(current - start).count();
        if (el > TIME_LIMIT) break;
        // forced 割当を決定: 最良があれば 3/4 の確率で「接尾辞から再構築」(摂動)
        vector<int> forced(D, -1);
        if (bestT >= 0 && (iters % 4 != 0)) {
            int m = 1 + (int)(rng() % max(1, bestTop));  // m 以降を再 greedy
            for (int k = 1; k < m; k++) forced[k] = bestAssign[k];
        }
        vector<Door> d;
        vector<Switch> s;
        vector<int> assign(D, -1);
        int top = attempt(rng, iters == 0 ? 0 : 2000, forced, d, s, assign);
        long long T = calcT(d, s);
        if (T > bestT) {
            bestT = T; bestD = d; bestS = s; bestTop = top;
            bestAssign = assign; lastImp = iters;
        }
        iters++;
    }
    cerr << "iters=" << iters << " bestT=" << bestT << " bestTop=" << bestTop
         << " lastImp=" << lastImp << "\n";

    // 出力
    cout << bestD.size() << "\n";
    for (auto &dr : bestD)
        cout << dr.d SP << dr.i SP << dr.j SP << dr.g << "\n";
    cout << bestS.size() << "\n";
    for (auto &sw : bestS)
        cout << sw.p SP << sw.q SP << sw.s << "\n";

    return 0;
}
