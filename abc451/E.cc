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
using tii = tuple<int, int>;
using tiii = tuple<int, int, int>;
using tiiii = tuple<int, int, int, int>;
using tll = tuple<ll, ll>;
using tlll = tuple<ll, ll, ll>;
using tllll = tuple<ll, ll, ll, ll>;
using vtii = vector<tii>;
using vtiii = vector<tiii>;
using vtiiii = vector<tiiii>;
using vtll = vector<tll>;
using vtlll = vector<tlll>;
using vtllll = vector<tllll>;

// ========== 定数 ==========
const int INF = 2e9;
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

// tuple入力（2要素）
template <typename T1, typename T2>
istream &operator>>(istream &is, tuple<T1, T2> &t) {
    is >> get<0>(t) >> get<1>(t);
    return is;
}

// tuple入力（3要素）
template <typename T1, typename T2, typename T3>
istream &operator>>(istream &is, tuple<T1, T2, T3> &t) {
    is >> get<0>(t) >> get<1>(t) >> get<2>(t);
    return is;
}

// tuple入力（4要素）
template <typename T1, typename T2, typename T3, typename T4>
istream &operator>>(istream &is, tuple<T1, T2, T3, T4> &t) {
    is >> get<0>(t) >> get<1>(t) >> get<2>(t) >> get<3>(t);
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

// ========== メイン関数 ==========

struct Edge {
    int from;
    int to;
    ll cost;

    Edge() {};
    Edge(int ifrom, int ito, ll icost) {
        from = ifrom;
        to = ito;
        cost = icost;
    }

    bool operator<(const Edge &in) const {
        return cost != in.cost ? cost < in.cost
               : to != in.to   ? to < in.to
                               : from < in.from;
    };
    bool operator>(const Edge &in) const {
        return cost != in.cost ? cost > in.cost
               : to != in.to   ? to > in.to
                               : from > in.from;
    };
};
struct Graph {
    int n, m;
    vector<vector<Edge>> g;
    vector<Edge> edges;
    vector<vector<ll>> dist;

    Graph() {};

    void init(int nn, int mm) {
        n = nn;
        m = mm;
        // n頂点、m辺、重み有無、有向無向
        int uu, vv, ww;
        g.resize(nn);
    }
    void add_edge(int uu, int vv, int ww) {
        g[uu].push_back({uu, vv, ww});
        g[vv].push_back({uu, vv, ww});
    }
    void board_init(vector<string> &bb) {
        // #.形式のboardを想定
        // 頂点番号は2重forの順に0から
        int hei = bb.size();
        int wid = bb[0].size();
        g.resize(hei * wid);

        // まだちゃんと書けていない
        for (int i = 0; i < hei - 1; i++) {
            for (int j = 0; j < wid; j++) {
                if (bb[i][j] == '.' && bb[i + 1][j] == '.') {
                    int ww = 1;
                    g[i * wid + j].push_back(
                        {i * wid + j, (i + 1) * wid + j, ww});
                    g[(i + 1) * wid + j].push_back(
                        {(i + 1) * wid + j, i * wid + j, ww});
                    // edges.push_back({i*wid+j, (i+1)*wid+j, 1}); // edges
                    // edges.push_back({(i+1)*wid+j, i*wid+j, 1}); // edges
                }
            }
        }
        for (int i = 0; i < hei; i++) {
            for (int j = 0; j < wid - 1; j++) {
                if (bb[i][j] == '.' && bb[i][j + 1] == '.') {
                    int ww = 1;
                    g[i * wid + j].push_back(
                        {i * wid + j, i * wid + j + 1, ww});
                    g[i * wid + j + 1].push_back(
                        {i * wid + j + 1, i * wid + j, ww});
                    // edges.push_back({i*wid+j, (i+1)*wid+j, 1}); // edges
                    // edges.push_back({(i+1)*wid+j, i*wid+j, 1}); // edges
                }
            }
        }
    }

    vector<int> bfs(int x) {
        vector<int> rtn(n, INF);
        rtn[x] = 0;
        queue<int> que;
        que.push(x);
        while (!que.empty()) {
            int y = que.front();
            int d = rtn[x];
            que.pop();
            for (int i = 0; i < g[y].size(); i++) {
                int to_x = g[y][i].to;
                if (d + g[y][i].cost < rtn[to_x]) {
                    rtn[to_x] = d + g[y][i].cost;
                    que.push(to_x);
                }
            }
        }
        return rtn;
    }
    // ダイクストラ法
    void djikstra(int startIndex) {
        dist.clear();
        dist.resize(n);
        dist[startIndex][startIndex] = 0;
        priority_queue<Edge, vector<Edge>, greater<Edge>> q;
        q.emplace(0, 0, startIndex);

        while (!q.empty()) {
            const long long distance = q.top().cost;
            const int from = q.top().from;
            q.pop();

            // 最短距離でなければ処理しない
            if (dist[startIndex][from] < distance) {
                continue;
            }

            // 現在の頂点からの各辺について
            for (const auto &edge : g[from]) {
                // to までの新しい距離
                const long long d = (dist[startIndex][from] + edge.cost);

                // d が現在の記録より小さければ更新
                if (d < dist[startIndex][edge.to]) {
                    dist[startIndex][edge.to] = d;
                    q.emplace(d, 0, edge.to);
                }
            }
        }
    }
    // ワーシャルフロイド法
    void worshalfroid() {}
    // 閉路検出
    bool has_cycle() { return false; }
    // 連結成分に分解
    void decomp(vector<Graph> vg) {}
    void euler_tour(int x) {}
};

void solve() {
    // ここに問題を解くコードを書く

    // 例: 入力
    int n;
    cin >> n;

    Graph g;
    g.init(n, n - 1);
    int a;

    vector<vector<Edge>> v(n);
    rep(i, n - 1) {
        rep(j, n - 1 - i) {
            cin >> a;
            v[i].push_back({i, i + j + 1, a});
            v[i + j + 1].push_back({i + j + 1, i, a});
            // g.add_edge(i, i + j + 1, a);
            // cout << i << " " << i + j + 1 << " ";
        }
        // cout << endl;
    }

    rep(i, n) {
        sort(all(v[i]));
        ll min_weight = v[i][0].cost;
        assert(v[i].size() == n - 1);
        cout << "i: " << i << endl;
        rep(j, v[i].size()) {
            if (v[i][j].cost == min_weight) {
                g.add_edge(i, v[i][j].to, min_weight);
                cout << i << " " << v[i][j].to << endl;
            } else {
                break;
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