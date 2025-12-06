// 競技プログラミング用テンプレート

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

// ========== マクロ ==========
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i <= (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define rrep(i, n) for (int i = (int)(n) - 1; i >= 0; i--)
#define rrep1(i, n) for (int i = (int)(n); i >= 1; i--)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

// ========== デバッグ ==========
#ifdef LOCAL
#define debug(...) debug_print(#__VA_ARGS__, __VA_ARGS__)
template <typename T> void debug_print(const char *name, T &&arg) {
    cerr << name << " = " << arg << endl;
}
template <typename T, typename... Args>
void debug_print(const char *names, T &&arg, Args &&...args) {
    const char *comma = strchr(names, ',');
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
template <typename T> bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template <typename T> bool chmin(T &a, const T &b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

// GCD・LCM
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// 累乗（mod付き）
ll pow_mod(ll x, ll n, ll mod = MOD) {
    ll res = 1;
    x %= mod;
    while (n > 0) {
        if (n & 1)
            res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

// 逆元（フェルマーの小定理）
ll inv_mod(ll x, ll mod = MOD) { return pow_mod(x, mod - 2, mod); }

// 階乗とその逆元（前計算）
struct Factorial {
    int n;
    vector<ll> fact, inv_fact;

    Factorial(int n, ll mod = MOD) : n(n), fact(n + 1), inv_fact(n + 1) {
        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i % mod;
        }
        inv_fact[n] = inv_mod(fact[n], mod);
        for (int i = n - 1; i >= 0; i--) {
            inv_fact[i] = inv_fact[i + 1] * (i + 1) % mod;
        }
    }

    ll nCr(int n, int r, ll mod = MOD) {
        if (r < 0 || r > n)
            return 0;
        return fact[n] * inv_fact[r] % mod * inv_fact[n - r] % mod;
    }

    ll nPr(int n, int r, ll mod = MOD) {
        if (r < 0 || r > n)
            return 0;
        return fact[n] * inv_fact[n - r] % mod;
    }
};

// ========== 入出力補助 ==========

// vector出力
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
    for (int i = 0; i < sz(v); i++) {
        os << v[i];
        if (i < sz(v) - 1)
            os << " ";
    }
    return os;
}

// pair出力
template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

// vector入力
template <typename T> istream &operator>>(istream &is, vector<T> &v) {
    for (T &x : v)
        is >> x;
    return is;
}

// pair入力
template <typename T, typename U>
istream &operator>>(istream &is, pair<T, U> &p) {
    is >> p.first >> p.second;
    return is;
}

// Yes/No出力
void Yes(bool flag = true) { cout << (flag ? "Yes" : "No") << "\n"; }

void YES(bool flag = true) { cout << (flag ? "YES" : "NO") << "\n"; }

// 座標圧縮（簡易版）
template <typename T> vector<int> compress(vector<T> &v) {
    vector<T> vals = v;
    sort(all(vals));
    vals.erase(unique(all(vals)), vals.end());

    vector<int> res(sz(v));
    rep(i, sz(v)) { res[i] = lower_bound(all(vals), v[i]) - vals.begin(); }
    return res;
}

// グリッド用の4方向・8方向
const vi dx4 = {0, 1, 0, -1};
const vi dy4 = {1, 0, -1, 0};
const vi dx8 = {0, 1, 1, 1, 0, -1, -1, -1};
const vi dy8 = {1, 1, 0, -1, -1, -1, 0, 1};

struct Edge {
    int to;
    long long cost;
    Edge(int to, long long cost) : to(to), cost(cost) {}
};

// グラフクラス（隣接リスト表現 + エッジリスト）
struct Graph {
    int n;                              // 頂点数
    vector<vector<int>> adj_unweighted; // 重みなし用
    set<int> black_list;

    Graph(int n) : n(n), adj_unweighted(n) {}

    // 重みなし有向辺を追加
    void add_unweighted_edge(int from, int to) {
        cerr << from << " " << to << endl;
        adj_unweighted[from].push_back(to);
    }

    void paint(int v) {
        if (black_list.find(v) != black_list.end()) {
            return;
        }
        black_list.insert(v);
        cerr << "! " << v << endl;
        vector<int> stack = {v};
        while (!stack.empty()) {
            int vv = stack[stack.size() - 1];
            stack.pop_back();
            rep(i, adj_unweighted[vv].size()) {
                int w = adj_unweighted[vv][i];
                if (black_list.find(w) != black_list.end()) {
                    continue;
                }
                black_list.insert(w);
                stack.push_back(w);
            }
        }
    }
};

// ========== メイン関数 ==========

void solve() {
    int n, m;
    cin >> n >> m;
    // cerr << "start1" << endl;
    Graph g(n);
    // cerr << "start2" << endl;

    rep(i, m) {
        int xx, yy;
        cin >> xx >> yy;
        g.add_unweighted_edge(int(yy - 1), int(xx - 1));
    }

    // cerr << "start3" << endl;
    int q;
    cin >> q;
    rep(i, q) {
        int t, v;
        cin >> t >> v;
        v--;

        if (t == 1) {
            g.paint(v);
        } else {
            if (g.black_list.find(v) != g.black_list.end()) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
}

int main() {
    // 単一テストケース
    solve();

    // 複数テストケース用（コメントアウト）

    // int t;
    // cin >> t;
    // while (t--) {
    //     solve();
    // }

    return 0;
}