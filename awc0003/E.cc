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

// ========== メイン関数 ==========
int n, m;
vector<int> w, c;
vector<int> v;
vector<long long> remW;

void dfs(int idx) {
    if (idx == n) {
        cout << "Yes\n";
        exit(0);
    }

    // ★ 総量による枝刈り
    long long sumV = 0;
    for (int i = 0; i < m; i++)
        sumV += v[i];
    if (sumV < remW[idx])
        return;

    set<int> st;
    for (int i = 0; i < m; i++) {
        if (v[i] < w[idx])
            continue;
        if (st.count(v[i]))
            continue;
        st.insert(v[i]);

        v[i] -= w[idx];
        dfs(idx + 1);
        v[i] += w[idx];
    }
}

void solve() {
    cin >> n >> m;
    w.resize(n);
    c.resize(m);

    for (int i = 0; i < n; i++)
        cin >> w[i];
    for (int i = 0; i < m; i++)
        cin >> c[i];

    sort(w.begin(), w.end(), greater<int>());
    sort(c.begin(), c.end(), greater<int>());

    // 事前チェック
    if (w[0] > c[0]) {
        cout << "No\n";
        return;
    }

    long long sumW = 0, sumC = 0;
    for (int x : w)
        sumW += x;
    for (int x : c)
        sumC += x;
    if (sumW > sumC) {
        cout << "No\n";
        return;
    }

    v = c;

    // 残り荷物の総和
    remW.resize(n + 1);
    remW[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        remW[i] = remW[i + 1] + w[i];
    }

    dfs(0);
    cout << "No\n";
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