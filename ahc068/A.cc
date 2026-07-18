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

// 入力データ
// a[i][j]: 初期状態でマス(i,j)に置かれているカードの番号
vector<vector<int>> a;
// vwall[i][j]==1: マス(i,j)とマス(i,j+1)の間に壁がある (0<=j<N-1)
vector<vector<int>> vwall;
// hwall[i][j]==1: マス(i,j)とマス(i+1,j)の間に壁がある (0<=i<N-1)
vector<vector<int>> hwall;

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

void inpt() {
    cin >> N;
    HEIGHT = WIDTH = N;

    a.assign(N, vector<int>(N));
    rep(i, N) rep(j, N) cin >> a[i][j];

    // V_0 .. V_{N-1}: 各長さ N-1 の 01 文字列
    vwall.assign(N, vector<int>(N - 1));
    rep(i, N) {
        string s;
        cin >> s;
        rep(j, N - 1) vwall[i][j] = s[j] - '0';
    }

    // H_0 .. H_{N-2}: 各長さ N の 01 文字列
    hwall.assign(N - 1, vector<int>(N));
    rep(i, N - 1) {
        string s;
        cin >> s;
        rep(j, N) hwall[i][j] = s[j] - '0';
    }
}

// ---- 前計算・評価用 ----
int b[20][20];       // 現在の盤面（可変）
int dst[400][400];   // 壁を考慮した全マス間距離（cell index 間）
int PV[21][21];      // vwall の2次元累積和
int PH[21][21];      // hwall の2次元累積和
int NN;              // N*N

void precompute() {
    NN = N * N;
    rep(i, N) rep(j, N) b[i][j] = a[i][j];

    // 全マス起点 BFS（壁のない辺のみ通行可）
    rep(s, N * N) {
        int *d = dst[s];
        rep(t, N * N) d[t] = -1;
        queue<int> q;
        d[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            int ci = cur / N, cj = cur % N, dc = d[cur];
            if (ci > 0 && !hwall[ci - 1][cj] && d[cur - N] < 0) {
                d[cur - N] = dc + 1;
                q.push(cur - N);
            }
            if (ci < N - 1 && !hwall[ci][cj] && d[cur + N] < 0) {
                d[cur + N] = dc + 1;
                q.push(cur + N);
            }
            if (cj > 0 && !vwall[ci][cj - 1] && d[cur - 1] < 0) {
                d[cur - 1] = dc + 1;
                q.push(cur - 1);
            }
            if (cj < N - 1 && !vwall[ci][cj] && d[cur + 1] < 0) {
                d[cur + 1] = dc + 1;
                q.push(cur + 1);
            }
        }
    }

    // 壁の2次元累積和
    rep(i, N + 1) rep(j, N + 1) {
        PV[i][j] = 0;
        PH[i][j] = 0;
    }
    rep(i, N) rep(j, N - 1)
        PV[i + 1][j + 1] = PV[i][j + 1] + PV[i + 1][j] - PV[i][j] + vwall[i][j];
    rep(i, N - 1) rep(j, N)
        PH[i + 1][j + 1] = PH[i][j + 1] + PH[i + 1][j] - PH[i][j] + hwall[i][j];
}

// 長方形 (r,c,h,w) の内部に壁が無ければ true
bool rectValid(int r, int c, int h, int w) {
    if (w >= 2) {  // 内部縦壁: 行[r,r+h) × 列[c,c+w-1)
        int c2 = c + w - 1;
        if (PV[r + h][c2] - PV[r][c2] - PV[r + h][c] + PV[r][c]) return false;
    }
    if (h >= 2) {  // 内部横壁: 行[r,r+h-1) × 列[c,c+w)
        int r2 = r + h - 1;
        if (PH[r2][c + w] - PH[r][c + w] - PH[r2][c] + PH[r][c]) return false;
    }
    return true;
}

inline ll sq(int x) { return (ll)x * x; }
inline ll cube(int x) { return (ll)x * x * x; }
// 盤面評価に使う 1マスあたりのコスト（現状は距離の1乗＝線形）
inline ll cost(int d) { return d; }

// 縦操作(上半分↔下半分)の距離二乗和の変化量
ll deltaV(int r, int c, int h, int w) {
    int hh = h / 2;
    ll dl = 0;
    rep(x, hh) rep(y, w) {
        int j = c + y, i1 = r + x, i2 = r + hh + x;
        int p1 = i1 * N + j, p2 = i2 * N + j;
        int v1 = b[i1][j], v2 = b[i2][j];
        dl += cost(dst[p1][v2]) + cost(dst[p2][v1]) - cost(dst[p1][v1]) -
              cost(dst[p2][v2]);
    }
    return dl;
}

// 横操作(左半分↔右半分)の距離二乗和の変化量
ll deltaH(int r, int c, int h, int w) {
    int ww = w / 2;
    ll dl = 0;
    rep(x, h) rep(y, ww) {
        int i = r + x, j1 = c + y, j2 = c + ww + y;
        int p1 = i * N + j1, p2 = i * N + j2;
        int v1 = b[i][j1], v2 = b[i][j2];
        dl += cost(dst[p1][v2]) + cost(dst[p2][v1]) - cost(dst[p1][v1]) -
              cost(dst[p2][v2]);
    }
    return dl;
}

void applyV(int r, int c, int h, int w) {
    int hh = h / 2;
    rep(x, hh) rep(y, w) swap(b[r + x][c + y], b[r + hh + x][c + y]);
}
void applyH(int r, int c, int h, int w) {
    int ww = w / 2;
    rep(x, h) rep(y, ww) swap(b[r + x][c + y], b[r + x][c + ww + y]);
}

struct Op {
    char d;
    int r, c, h, w;
};

// ---- leaf-elimination で E=0 まで仕上げる（隣接互換のみ） ----
// 現在の盤面 b を完成させ、使った操作を ops に追記する。
// 総手数が 100000 を超えないよう打ち切る。
void finish(vector<Op> &ops) {
    static int where[400];  // where[value] = そのカードの現在セル index
    rep(i, N) rep(j, N) where[b[i][j]] = i * N + j;

    // 壁のない隣接グラフの全域木を BFS で構築
    vector<vector<int>> tadj(NN);
    {
        vector<int> vis(NN, 0);
        queue<int> q;
        q.push(0);
        vis[0] = 1;
        auto addEdge = [&](int cur, int nx) {
            if (!vis[nx]) {
                vis[nx] = 1;
                tadj[cur].push_back(nx);
                tadj[nx].push_back(cur);
                q.push(nx);
            }
        };
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            int ci = cur / N, cj = cur % N;
            if (ci > 0 && !hwall[ci - 1][cj]) addEdge(cur, cur - N);
            if (ci < N - 1 && !hwall[ci][cj]) addEdge(cur, cur + N);
            if (cj > 0 && !vwall[ci][cj - 1]) addEdge(cur, cur - 1);
            if (cj < N - 1 && !vwall[ci][cj]) addEdge(cur, cur + 1);
        }
    }

    // 葉から順に確定
    vector<int> deg(NN), active(NN, 1);
    rep(p, NN) deg[p] = (int)tadj[p].size();
    queue<int> leaves;
    rep(p, NN) if (deg[p] <= 1) leaves.push(p);

    int remaining = NN;
    vector<int> bpar(NN);  // target を根とする BFS 親
    while (remaining > 0) {
        int leaf = -1;
        while (!leaves.empty()) {
            int c = leaves.front();
            leaves.pop();
            if (active[c] && deg[c] <= 1) {
                leaf = c;
                break;
            }
        }
        if (leaf == -1) rep(p, NN) if (active[p]) {
                leaf = p;
                break;
            }

        // カード(値 leaf) をセル leaf まで、残り木の中で運ぶ
        int target = leaf, pos = where[leaf];
        if (pos != target) {
            rep(p, NN) bpar[p] = -2;
            queue<int> q;
            q.push(target);
            bpar[target] = -1;
            while (!q.empty()) {
                int cur = q.front();
                q.pop();
                for (int nx : tadj[cur])
                    if (active[nx] && bpar[nx] == -2) {
                        bpar[nx] = cur;
                        q.push(nx);
                    }
            }
            // pos から target へ1歩ずつ、カード leaf を移動
            while (pos != target) {
                int nxt = bpar[pos];
                int pi = pos / N, pj = pos % N, ni = nxt / N, nj = nxt % N;
                Op op;
                if (pi != ni)
                    op = {'V', min(pi, ni), pj, 2, 1};
                else
                    op = {'H', pi, min(pj, nj), 1, 2};
                int vpos = b[pi][pj], vnxt = b[ni][nj];
                swap(b[pi][pj], b[ni][nj]);
                where[vpos] = nxt;
                where[vnxt] = pos;
                ops.push_back(op);
                pos = nxt;
                if ((int)ops.size() >= 100000) return;  // 手数上限
            }
        }

        // leaf を確定・除去
        active[leaf] = 0;
        remaining--;
        for (int nx : tadj[leaf])
            if (active[nx]) {
                deg[nx]--;
                if (deg[nx] <= 1) leaves.push(nx);
            }
        deg[leaf] = 0;
    }
}

int main() {
    start = chrono::system_clock::now();

    inpt();
    precompute();

    vector<Op> ops;

    // 1乗和グリーディ（最良改善、局所最適で停止）
    while ((int)ops.size() < 100000) {
        current = chrono::system_clock::now();
        double el =
            chrono::duration_cast<chrono::milliseconds>(current - start)
                .count();
        if (el > TIME_LIMIT) break;

        ll bestDelta = 0;  // 厳密改善(<0)のみ採用
        int bestArea = -1;
        Op best;
        bool found = false;

        // 縦: h は偶数
        rep(r, N) rep(c, N) {
            for (int h = 2; r + h <= N; h += 2) {
                bool rowBroke = false;
                for (int w = 1; c + w <= N; w++) {
                    if (!rectValid(r, c, h, w)) {
                        if (w == 1) rowBroke = true;
                        break;
                    }
                    ll dl = deltaV(r, c, h, w);
                    int area = h * w;
                    if (dl < bestDelta ||
                        (dl == bestDelta && dl < 0 && area > bestArea)) {
                        bestDelta = dl;
                        bestArea = area;
                        best = {'V', r, c, h, w};
                        found = true;
                    }
                }
                if (rowBroke) break;
            }
        }
        // 横: w は偶数
        rep(r, N) rep(c, N) {
            for (int w = 2; c + w <= N; w += 2) {
                bool colBroke = false;
                for (int h = 1; r + h <= N; h++) {
                    if (!rectValid(r, c, h, w)) {
                        if (h == 1) colBroke = true;
                        break;
                    }
                    ll dl = deltaH(r, c, h, w);
                    int area = h * w;
                    if (dl < bestDelta ||
                        (dl == bestDelta && dl < 0 && area > bestArea)) {
                        bestDelta = dl;
                        bestArea = area;
                        best = {'H', r, c, h, w};
                        found = true;
                    }
                }
                if (colBroke) break;
            }
        }

        if (!found) break;  // 局所最適: グリーディ停止
        if (best.d == 'V')
            applyV(best.r, best.c, best.h, best.w);
        else
            applyH(best.r, best.c, best.h, best.w);
        ops.push_back(best);
    }

    // 停滞後: leaf-elimination で E=0 まで仕上げる
    finish(ops);

    // 出力
    string out;
    for (auto &o : ops) {
        out += o.d;
        out += ' ';
        out += to_string(o.r);
        out += ' ';
        out += to_string(o.c);
        out += ' ';
        out += to_string(o.h);
        out += ' ';
        out += to_string(o.w);
        out += '\n';
    }
    cout << out;

    return 0;
}
