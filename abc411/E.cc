#include <atcoder/all>
#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define rep3r(i, n, m) for (int i = n - 1; i >= m; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

using namespace std;
using namespace atcoder;

int imax = 2147483647;
ll lmax = 9223372036854775807;
// using mint = modint1000000007;
using mint = modint998244353;
//  ll mod=998244353;
//  ll mod=1000000007;

struct Men {
    int val;
    int idx;

    bool operator<(const Men &in) const { return val < in.val; };
};

mint op(mint a, mint b) { return a * b; }

mint e() { return 0; }

int main() {
    int n;
    cin >> n;
    vector<vector<int>> v(n, vector<int>(6));
    vector<Men> mens;
    vector<mint> fac(6 * n);
    fac[0] = 1;
    rep(i, 6 * n) { fac[i + 1] = fac[i] * (i + 1); }

    rep(i, n) {
        rep(j, 6) {
            cin >> v[i][j];
            mens.push_back({v[i][j], i});
        }
    }
    sort(all(mens));

    mint ans = 0;
    mint div = 1;
    rep(i, n) { div *= 6; }
    segtree<mint, op, e> seg(n);
    Men prev_men;
    int prev_count = -1;
    rep(i, mens.size()) {
        int lim_idx = i + 1;
        while (lim_idx < mens.size() && mens[i].val == mens[lim_idx].val) {
            lim_idx++;
        }
        set<int> st;
        rep3(j, lim_idx, i) {
            st.insert(mens[j].idx);
            seg.set(mens[j].idx, seg.get(mens[j].idx) + 1);
        }

        rep3(j, lim_idx, i) {
            mint tmp = seg.all_prod();
            if (seg.get(mens[j].idx) != 0) {
                tmp /= seg.get(mens[j].idx);
            }
            cout << "all_prod: " << tmp.val() << " mens[j].val: " << mens[j].val
                 << "/div: " << div.val() << endl;
            tmp *= mens[j].val;
            tmp /= div;
            tmp /= fac[st.size()];
            ans += tmp;
        }

        i = lim_idx - 1;
    }

    cout << ans.val() << endl;

    return 0;
}