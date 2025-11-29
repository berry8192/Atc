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

template <typename T> class imos_2d {
  private:
    vector<vector<T>> diff;
    int h, w;

  public:
    imos_2d(int height, int width)
        : h(height), w(width), diff(height + 1, vector<T>(width + 1, 0)) {}

    // 矩形領域(r1,c1)から(r2,c2)にvalueを加算（両端含む）
    void add(int r1, int c1, int r2, int c2, T value) {
        if (r1 < 0 || r2 >= h || c1 < 0 || c2 >= w || r1 > r2 || c1 > c2)
            return;
        diff[r1][c1] += value;
        diff[r1][c2 + 1] -= value;
        diff[r2 + 1][c1] -= value;
        diff[r2 + 1][c2 + 1] += value;
    }

    // 実際の配列を構築
    vector<vector<T>> build() {
        vector<vector<T>> result(h, vector<T>(w, 0));

        // 横方向の累積和
        for (int i = 0; i < h; i++) {
            result[i][0] = diff[i][0];
            for (int j = 1; j < w; j++) {
                result[i][j] = result[i][j - 1] + diff[i][j];
            }
        }

        // 縦方向の累積和
        for (int j = 0; j < w; j++) {
            for (int i = 1; i < h; i++) {
                result[i][j] += result[i - 1][j];
            }
        }

        return result;
    }
};

template <typename T> class cumsum_2d {
  private:
    vector<vector<T>> sum;

  public:
    cumsum_2d(const vector<vector<T>> &grid) {
        int h = grid.size();
        int w = grid[0].size();
        sum.assign(h + 1, vector<T>(w + 1, 0));

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                sum[i + 1][j + 1] =
                    sum[i][j + 1] + sum[i + 1][j] - sum[i][j] + grid[i][j];
            }
        }
    }

    // 矩形領域(r1,c1)から(r2,c2)の和（両端含む）
    T query(int r1, int c1, int r2, int c2) {
        if (r1 < 0 || r2 >= sum.size() - 1 || c1 < 0 ||
            c2 >= sum[0].size() - 1 || r1 > r2 || c1 > c2)
            return 0;
        return sum[r2 + 1][c2 + 1] - sum[r1][c2 + 1] - sum[r2 + 1][c1] +
               sum[r1][c1];
    }
};

// ========== メイン関数 ==========

void solve() {
    // ここに問題を解くコードを書く

    // 例: 入力
    int n;
    cin >> n;
    vector<int> u(n), d(n), l(n), r(n);
    rep(i, n) {
        cin >> u[i] >> d[i] >> l[i] >> r[i];
        u[i]--;
        d[i]--;
        l[i]--;
        r[i]--;
    }

    imos_2d<int> imos2d(2000, 2000);
    rep(i, n) { imos2d.add(u[i], l[i], d[i], r[i], 1); }

    auto result2 = imos2d.build();
    // cout << "結果:" << endl;
    // rep(i, 10) {
    //     rep(j, 10) { cout << result2[i][j] << " "; }
    //     cout << endl;
    // }

    imos_2d<int> imos2d2(2000, 2000);
    int empty_count = 0;
    rep(i, 2000) {
        rep(j, 2000) {
            if (result2[i][j] == 0) {
                empty_count++;
            }
            if (result2[i][j] == 1) {
                imos2d2.add(i, j, i, j, 1);
            }
        }
    }
    auto result3 = imos2d2.build();

    cumsum_2d<int> cs2d(result3);

    rep(i, n) {
        int cnt = cs2d.query(u[i], l[i], d[i], r[i]);
        cout << cnt + empty_count << endl;
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