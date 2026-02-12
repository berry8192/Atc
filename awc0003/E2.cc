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

void solve() {
    cin >> n >> m;
    w.resize(n);
    c.resize(m);

    ll sumw = 0, sumc = 0;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        sumw += w[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> c[i];
        sumc += c[i];
    }

    sort(w.begin(), w.end(), greater<int>());
    sort(c.begin(), c.end(), greater<int>());

    if (m > n) {
        c.resize(n);
        m = n;
    }

    // 事前チェック
    if (sumw > sumc) {
        cout << "No" << endl;
        return;
    }

    int FULL = (1 << n);
    vector<int> dp_k(FULL, m + 1);
    vector<ll> dp_rem(FULL, -1);

    dp_k[0] = 0;
    dp_rem[0] = c[0];

    rep(mask, FULL) {
        int k = dp_k[mask];
        ll rem = dp_rem[mask];
        if (k >= m) {
            continue;
        }

        rep(i, n) {
            if (mask & (1 << i)) {
                continue;
            }

            int new_mask = (mask | (1 << i));
            int nk;
            ll nrem;

            if (w[i] <= rem) {
                nk = k;
                nrem = rem - w[i];
            } else if (k + 1 < m && w[i] <= c[k + 1]) {
                nk = k + 1;
                nrem = c[k + 1] - w[i];
            } else {
                continue;
            }

            if (nk < dp_k[new_mask] ||
                (nk == dp_k[new_mask] && nrem > dp_rem[new_mask])) {
                dp_k[new_mask] = nk;
                dp_rem[new_mask] = nrem;
            }
        }
    }
    if (dp_k[FULL - 1] < m) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
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