#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define rep3r(i, n, m) for (int i = n - 1; i >= m; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

using namespace std;
// using namespace atcoder;

int imax = 2147483647;
ll lmax = 9223372036854775807;
// using mint = modint1000000007;
// using mint = modint998244353;
//  ll mod=998244353;
//  ll mod=1000000007;

template <class T> ll gcdv(vector<T> gv) {
    assert(gv.size() > 0);
    T tmp = gv[0];
    for (int i = 1; i < (int)gv.size(); i++)
        tmp = __gcd(tmp, gv[i]);
    return tmp;
}

template <class T> ll lcmv(vector<T> gv) {
    assert(gv.size() > 0);
    T tmp = gv[0];
    for (ll i = 1; i < (int)gv.size(); i++)
        tmp = tmp / __gcd(tmp, gv[i]) * gv[i];
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

struct edge {
    int to;
    int co;

    bool operator<(const edge &in) const {
        return co != in.co ? co < in.co : to < in.to;
    };
};
// クラスカル法とかやりたいときに使う
struct s_edge {
    int to;
    int from;
    int co;

    bool operator<(const s_edge &in) const {
        return co != in.co  ? co < in.co
               : to < in.to ? to < in.to
                            : from < in.from;
    };
};
struct Graph {
    int n, m;
    vector<vector<edge>> g;
    vector<s_edge> edges;
    vector<s_edge> euler_e;
    vector<int> used;
    int fir = -1;

    void init(int nn, int mm, bool weight = false, bool directed = false) {
        n = nn;
        m = mm;
        // n頂点、m辺、重み有無、有向無向
        int uu, vv, ww;
        g.resize(nn);
        used.resize(nn);

        for (int i = 0; i < mm; i++) {
            cin >> uu >> vv;
            uu--;
            vv--;
            if (fir == -1)
                fir = uu;
            if (weight)
                cin >> ww;
            else
                ww = 1;

            g[uu].push_back({vv, ww});
            edges.push_back({uu, vv, ww}); // edges
            if (!directed) {
                g[vv].push_back({uu, ww});
                edges.push_back({vv, uu, ww}); // edges
            }
        }
    }
    void board_init(vector<string> &bb) {
        // #.形式のboardを想定
        // 頂点番号は2重forの順に0から
        int hei = bb.size();
        int wid = bb[0].size();
        g.resize(hei * wid);

        for (int i = 0; i < hei - 1; i++) {
            for (int j = 0; j < wid - 1; j++) {
                if (bb[i][j] == '.' && bb[i + 1][j] == '.') {
                    int ww = 1;
                    g[i * wid + j].push_back({(i + 1) * wid + j, ww});
                    g[(i + 1) * wid + j].push_back({i * wid + j, ww});
                    // edges.push_back({i*wid+j, (i+1)*wid+j, 1}); // edges
                    // edges.push_back({(i+1)*wid+j, i*wid+j, 1}); // edges
                }
            }
        }
    }

    void euler(int x) {
        if (used[x])
            return;
        used[x] = 1;
        rep(i, g[x].size()) {
            if (used[g[x][i].to])
                continue;
            euler_e.push_back({g[x][i].to, x, g[x][i].co});
            euler(g[x][i].to);
            euler_e.push_back({x, g[x][i].to, g[x][i].co});
        }
    }
};

int main() {
    int n;
    ll ans = lmax;
    cin >> n;

    Graph graph;
    graph.init(n, n - 1, true);
    graph.euler(graph.fir);
    vector<s_edge> vs = graph.euler_e;

    set<int> st;
    vector<int> seen(n);
    seen[graph.fir] = 1;
    st.insert(graph.fir);
    ll cost = 0;
    int pos = 0;
    while (1) {
        // cout << vs[pos].from SP << vs[pos].to SP << vs[pos].co << endl;
        seen[vs[pos].to]++;
        cost += vs[pos].co;
        st.insert(vs[pos].to);
        if (st.size() == n) {
            break;
        }
        pos++;
    }
    ans = cost;
    // cout << cost << endl;
    rep(i, vs.size()) {
        seen[vs[i].from]--;
        cost -= vs[i].co;
        if (seen[vs[i].from] == 0) {
            st.erase(vs[i].from);
        }
        while (st.size() < n) {
            seen[vs[pos % (vs.size())].to]++;
            cost += vs[pos % (vs.size())].co;
            st.insert(vs[pos % (vs.size())].to);
            pos++;
        }
        ans = min(ans, cost);
        // cout << cost << endl;
    }
    cout << ans << endl;

    return 0;
}
