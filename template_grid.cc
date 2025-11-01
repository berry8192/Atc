// 競技プログラミング用テンプレート（入力ヘルパー付き）

#include <bits/stdc++.h>
using namespace std;

// ========== 型定義 ==========
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vi>;
using vvll = vector<vll>;
using vs = vector<string>;
using vpii = vector<pii>;
using vpll = vector<pll>;

// ========== 定数 ==========
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1000000007;
const int MOD2 = 998244353;
const double EPS = 1e-9;
const double PI = acos(-1.0);

// ========== 基本マクロ ==========
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i <= (int)(n); i++)
#define rrep(i, n) for (int i = (int)(n) - 1; i >= 0; i--)
#define rrep1(i, n) for (int i = (int)(n); i >= 1; i--)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

// ========== 入力ヘルパーマクロ ==========

// 単一変数の宣言と入力
#define INPUT(type, ...) type __VA_ARGS__; input(__VA_ARGS__)
#define INT(...) INPUT(int, __VA_ARGS__)
#define LL(...) INPUT(ll, __VA_ARGS__)
#define STR(...) INPUT(string, __VA_ARGS__)
#define DBL(...) INPUT(double, __VA_ARGS__)
#define CHAR(...) INPUT(char, __VA_ARGS__)

// ベクトルの宣言と入力
#define VEC(type, name, size) vector<type> name(size); input(name)
#define VVI(name, h, w) vector<vector<int>> name(h, vector<int>(w)); input(name)
#define VVL(name, h, w) vector<vector<ll>> name(h, vector<ll>(w)); input(name)

// グリッドの宣言と入力
#define GRID(name, h) vector<string> name(h); input(name)

// ペアの宣言と入力
#define PAIR(type1, type2, name) pair<type1, type2> name; input(name)

// 複数要素の同時入力
#define INPUT2(type, a, b) type a, b; input(a, b)
#define INPUT3(type, a, b, c) type a, b, c; input(a, b, c)
#define INPUT4(type, a, b, c, d) type a, b, c, d; input(a, b, c, d)

// ========== 入力関数（テンプレート） ==========

// 基本型の入力
template<typename T>
void input(T& x) {
    cin >> x;
}

// 複数引数の入力
template<typename T, typename... Args>
void input(T& x, Args&... args) {
    cin >> x;
    input(args...);
}

// vector の入力
template<typename T>
void input(vector<T>& v) {
    for (auto& x : v) input(x);
}

// 2次元vector の入力
template<typename T>
void input(vector<vector<T>>& v) {
    for (auto& row : v) input(row);
}

// pair の入力
template<typename T, typename U>
void input(pair<T, U>& p) {
    input(p.first, p.second);
}

// ========== 便利な入力関数 ==========

// N個の要素を持つvectorを作成して入力
template<typename T = int>
vector<T> input_vec(int n) {
    vector<T> v(n);
    input(v);
    return v;
}

// H×Wのグリッドを入力
vector<string> input_grid(int h) {
    vector<string> grid(h);
    input(grid);
    return grid;
}

// N個のペアを入力
template<typename T = int, typename U = int>
vector<pair<T, U>> input_pairs(int n) {
    vector<pair<T, U>> v(n);
    input(v);
    return v;
}

// グラフの辺を入力（1-indexed を 0-indexed に変換）
vector<pair<int, int>> input_edges(int m, bool one_indexed = true) {
    vector<pair<int, int>> edges(m);
    for (auto& [a, b] : edges) {
        input(a, b);
        if (one_indexed) {
            a--; b--;
        }
    }
    return edges;
}

// 重み付きグラフの辺を入力
vector<tuple<int, int, ll>> input_weighted_edges(int m, bool one_indexed = true) {
    vector<tuple<int, int, ll>> edges(m);
    for (auto& [a, b, w] : edges) {
        input(a, b, w);
        if (one_indexed) {
            a--; b--;
        }
    }
    return edges;
}

// ========== デバッグ ==========
#ifdef LOCAL
    #define debug(...) debug_print(#__VA_ARGS__, __VA_ARGS__)
    template<typename T>
    void debug_print(const char* name, T&& arg) {
        cerr << name << " = " << arg << endl;
    }
    template<typename T, typename... Args>
    void debug_print(const char* names, T&& arg, Args&&... args) {
        const char* comma = strchr(names, ',');
        cerr.write(names, comma - names) << " = " << arg << ", ";
        debug_print(comma + 1, args...);
    }
#else
    #define debug(...) void(0)
#endif

// ========== 入出力高速化 ==========
struct FastIO {
    FastIO() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout << fixed << setprecision(10);
    }
} fast_io;

// ========== 便利関数 ==========

// 最大・最小値更新
template<typename T>
bool chmax(T& a, const T& b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template<typename T>
bool chmin(T& a, const T& b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

// Yes/No出力
void Yes(bool flag = true) {
    cout << (flag ? "Yes" : "No") << "\n";
}

void YES(bool flag = true) {
    cout << (flag ? "YES" : "NO") << "\n";
}

// グリッド用の4方向・8方向
const vi dx4 = {0, 1, 0, -1};
const vi dy4 = {1, 0, -1, 0};
const vi dx8 = {0, 1, 1, 1, 0, -1, -1, -1};
const vi dy8 = {1, 1, 0, -1, -1, -1, 0, 1};

// ========== グリッドグラフヘルパー ==========

// 簡易版グリッドグラフクラス
struct GridGraph {
    int h, w;
    vs grid;
    string passable = ".SG";  // 通過可能文字

    GridGraph(int h, int w) : h(h), w(w), grid(h) {
        input(grid);
    }

    GridGraph(vs& g, string pass = ".SG") : h(sz(g)), w(sz(g[0])), grid(g), passable(pass) {}

    bool valid(int x, int y) {
        return 0 <= x && x < h && 0 <= y && y < w;
    }

    bool can_pass(int x, int y) {
        return valid(x, y) && passable.find(grid[x][y]) != string::npos;
    }

    pii find_char(char c) {
        rep(i, h) rep(j, w) if (grid[i][j] == c) return {i, j};
        return {-1, -1};
    }

    // BFSで最短経路
    int bfs(int sx, int sy, int gx, int gy) {
        vvi dist(h, vi(w, -1));
        queue<pii> q;
        dist[sx][sy] = 0;
        q.push({sx, sy});

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            if (x == gx && y == gy) return dist[x][y];

            rep(d, 4) {
                int nx = x + dx4[d];
                int ny = y + dy4[d];
                if (can_pass(nx, ny) && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
        return -1;
    }

    // S から G への最短経路
    int solve() {
        auto [sx, sy] = find_char('S');
        auto [gx, gy] = find_char('G');
        if (sx == -1 || gx == -1) return -1;
        return bfs(sx, sy, gx, gy);
    }
};

// ========== メイン関数 ==========

void solve() {
    // ========== 使用例 ==========

    // 例1: 単一変数の入力
    // INT(n);  // int n; cin >> n; と同じ

    // 例2: 複数変数の入力
    // INT(n, m, k);  // int n, m, k; cin >> n >> m >> k; と同じ

    // 例3: ベクトルの入力
    // INT(n);
    // VEC(int, a, n);  // vector<int> a(n); rep(i,n) cin >> a[i]; と同じ

    // 例4: グリッドの入力
    // INT(h, w);
    // GRID(s, h);  // vector<string> s(h); rep(i,h) cin >> s[i]; と同じ

    // 例5: グラフの入力
    // INT(n, m);
    // auto edges = input_edges(m);  // m本の辺を入力（1-indexed -> 0-indexed）

    // 例6: クエリ処理
    // INT(q);
    // rep(_, q) {
    //     INT(type);
    //     if (type == 1) {
    //         INT(x, y);
    //         // 処理
    //     } else {
    //         INT(z);
    //         // 処理
    //     }
    // }

    // 実際のコードをここに書く
}

int main() {
    // 単一テストケース
    solve();

    // 複数テストケース用
    /*
    INT(t);
    while (t--) {
        solve();
    }
    */

    return 0;
}