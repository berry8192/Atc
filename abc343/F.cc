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
// using mint = modint998244353;
//  ll mod=998244353;
//  ll mod=1000000007;

template <class T> ll gcdv(vector<T> gv) {
    assert(gv.size() > 0);
    ll tmp = gv[0];
    for (int i = 1; i < (int)gv.size(); i++)
        tmp = gcd(tmp, gv[i]);
    return tmp;
}

template <class T> ll lcmv(vector<T> gv) {
    assert(gv.size() > 0);
    ll tmp = gv[0];
    for (ll i = 1; i < (int)gv.size(); i++)
        tmp = tmp / gcd(tmp, gv[i]) * gv[i];
    return tmp;
}

template <class T> ll sumv(vector<T> gv) {
    assert(gv.size() > 0);
    ll tmp = gv[0];
    for (ll i = 1; i < (int)gv.size(); i++)
        tmp += gv[i];
    return tmp;
}

template <class T> vector<T> subv(vector<T> gv) {
    assert(gv.size() > 0);
    vector<T> tmp;
    for (ll i = 1; i < (int)gv.size(); i++)
        tmp.push_back(abs(gv[i - 1] - gv[i]));
    return tmp;
}

// int型vectorを出力
template <class T> void PV(T pvv) {
    if (!pvv.size())
        return;
    rep(i, pvv.size() - 1) cout << pvv[i] SP;
    cout << pvv[pvv.size() - 1] << endl;
}

// LLi型vectorを出力
template <class T> void PVV(T pvv) {
    rep(i, pvv.size()) {
        rep(j, pvv[i].size()) { cout << pvv[i][j] SP; }
        cout << endl;
    }
}

template <class T> void PS(T ps) {
    // cout<< "{";
    for (auto s : ps)
        cout << s SP;
    // cout<< "}";
    cout << endl;
}

template <class T> void PM(T pm) {
    // cout<< "{";
    for (auto m : pm) {
        cout << "(" << m.first << "->" << m.second << "), ";
    }
    // cout<< "}";
    cout << endl;
}

struct Edge {
    int from;
    int to;
    ll cost;

    bool operator<(const Edge &in) const {
        return cost != in.cost ? cost < in.cost
               : to < in.to    ? to < in.to
                               : from < in.from;
    };
};
// 長い文字列を数列として解釈してmodで抑えた整数にする
ll stollmod(string ss, ll MOD) {
    ll rtn = 0;
    ll base = 1;
    repr(i, ss.size()) {
        int d = int(ss[i] - '0');
        rtn += base * d;
        rtn %= MOD;
        base *= 10;
        base %= MOD;
    }
    return rtn;
}

// 進数変換10->2 桁指定 10進->2進
string tob(ll n, int lng = 0, string fil = "0") {
    string r, rtn = "";
    while (n != 0) {
        r += (n % 2 == 0 ? "0" : "1");
        n /= 2;
    }
    while (lng > r.size())
        r += fil;
    return r;
}

void all_perm(vector<int> vv) {
    vector<int> perm;
    rep(i, vv.size()) perm.push_back(i);
    do {
        PV(perm);
    } while (next_permutation(all(perm)));
}

// ランレングス圧縮、連長圧縮
// 文字列を何の文字が何連続というかたまりに分解する
void rle(string s, vector<pair<char, int>> &vec) {
    int cnt = 1;
    for (int i = 1; i < (int)s.size(); i++) {
        if (s[i] != s[i - 1]) {
            vec.push_back({s[i - 1], cnt});
            cnt = 0;
        }
        cnt++;
    }
    vec.push_back({s.back(), cnt});
}

// 累積和
template <class T> vector<ll> ruiseki(T vv) {
    vector<ll> xx;
    xx.resize(vv.size() + 1);
    xx[0] = 0;
    for (int i = 0; i < (int)vv.size(); i++) {
        xx[i + 1] = xx[i] + vv[i];
        // xx[i+1]=xx[i+1]%mod;
    }
    return xx;
}

// いもす法1D, imos1D
vector<int> imos(vector<int> vv) {
    rep3(i, vv.size(), 1) vv[i] += vv[i - 1];
    return vv;
}

template <class T> void addbit(vector<T> vv) {
    int sz = vv.size();
    for (int bit = 0; bit < (1 << sz); ++bit) {
        // 全ての桁に対する処理
        for (int i = 0; i < sz; ++i) {
            // 探索対象となっているbitかどうかを判定
            if (bit & (1 << i)) {
                // ここに処理を書く
            }
        }
    }
}

int biggest = 1;

int op1(int a, int b) { return max(a, b); }
int op2(int a, int b) { return max(a % biggest, b % biggest); }

int e() { return -1; }

int target;

bool f(int v) { return v < target; }

int main() {
    // cout << fixed
    int n, q;
    vector<int> a;
    map<int, set<int>> mp;

    cin >> n >> q;
    a.resize(n);

    rep(i, n) {
        cin >> a[i];
        mp[a[i]].insert(i);
    }

    segtree<int, op1, e> seg1(a);
    segtree<int, op2, e> seg2(a);

    rep(i, q) {
        int t, p, x, l, r;
        cin >> t;
        if (t == 1) {
            cin >> p >> x;
            p--;
            seg1.set(p, x);
            seg2.set(p, x);

            mp[a[p]].erase(p);
            a[p] = x;
            mp[x].insert(p);
        } else {
            cin >> l >> r;
            l--;
            biggest = seg1.prod(l, r);
            biggest = max(1, biggest);
            int second = seg2.prod(l, r);
            auto lb = mp[second].lower_bound(l);
            auto rb = mp[second].lower_bound(r);
            cout << biggest SP << second << endl;
            int cnt = 0;
            cout << "set ";
            PS(mp[second]);
            cout << "# ";
            for (auto it = lb; it != rb; it++) {
                cout << *it SP;
                cnt++;
            }
            cout << *rb << endl;
            cout << cnt << endl;
            // cout << distance(lb, rb) << endl;
        }
    }

    return 0;
}