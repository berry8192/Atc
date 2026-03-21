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

vector<ll> tmp(2), xfib(2), yfib(2);
string x, y;
vector<vector<ll>> xr, yr;

ll cnt(ll n, char c) {
    // cout << "in: " << n << " " << c << endl;
    if (n <= x.size()) {
        // cout << "yy " << yr[n][c - 'a'] << endl;
        return xr[n][c - 'a'];
    } else if (n <= x.size() + y.size()) {
        // cout << "xy " << yr[y.size()][c - 'a'] + xr[n - y.size()][c - 'a']
        //      << endl;
        return yr[y.size()][c - 'a'] + xr[n - y.size()][c - 'a'];
    }
    int idx = lower_bound(all(tmp), n) - tmp.begin() - 1;
    // cout << "fix: " << yfib[idx] << " " << yr[y.size()][c - 'a'] << " "
    //      << xfib[idx] << " " << xr[x.size()][c - 'a'] << endl;
    return yfib[idx] * yr[y.size()][c - 'a'] +
           xfib[idx] * xr[x.size()][c - 'a'] + cnt(n - tmp[idx], c);
}

void solve() {
    // ここに問題を解くコードを書く

    // 例: 入力
    cin >> x >> y;
    xr.resize(x.size() + 1, vector<ll>(26));
    yr.resize(y.size() + 1, vector<ll>(26));
    rep(i, x.size()) {
        xr[i + 1] = xr[i];
        rep(j, 26) {
            if (x[i] == ('a' + j)) {
                xr[i + 1][j]++;
            }
        }
    }
    rep(i, y.size()) {
        yr[i + 1] = yr[i];
        rep(j, 26) {
            if (y[i] == ('a' + j)) {
                yr[i + 1][j]++;
            }
        }
    }
    int q;
    cin >> q;
    vector<ll> l(q), r(q);
    vector<char> c(q);
    rep(i, q) { cin >> l[i] >> r[i] >> c[i]; }

    tmp[0] = x.size();
    tmp[1] = y.size();
    xfib[1] = 1;
    yfib[0] = 1;
    rep3(i, 808, 2) {
        tmp.push_back(tmp[i - 1] + tmp[i - 2]);
        xfib.push_back(xfib[i - 1] + xfib[i - 2]);
        yfib.push_back(yfib[i - 1] + yfib[i - 2]);
        // cout << tmp[i] << endl;
        if (tmp[tmp.size() - 1] > 2000000000000000000LL) {
            break;
        }
    } // reverse(all(tmp));

    rep(i, q) {
        // cout << i << endl;
        // cout << cnt(r[i], c[i]) << " " << cnt(l[i] - 1, c[i]) << endl;
        cout << cnt(r[i], c[i]) - cnt(l[i] - 1, c[i]) << endl;
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