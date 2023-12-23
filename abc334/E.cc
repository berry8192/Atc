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
// ll mod=998244353;
// ll mod=1000000007;

template <class T> ll gcdv(vector<T> gv) {
    assert(gv.size() > 0);
    ll tmp = gv[0];
    for (int i = 1; i < (int)gv.size(); i++)
        tmp = gcdi(tmp, gv[i]);
    return tmp;
}

template <class T> ll lcmv(vector<T> gv) {
    assert(gv.size() > 0);
    ll tmp = gv[0];
    for (ll i = 1; i < (int)gv.size(); i++)
        tmp = lcmi(tmp, gv[i]);
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

    void init(int nn, int mm, bool weight = false, bool directed = false) {
        n = nn;
        m = mm;
        // n頂点、m辺、重み有無、有向無向
        int uu, vv, ww;
        g.resize(nn);

        for (int i = 0; i < mm; i++) {
            cin >> uu >> vv;
            uu--;
            vv--;
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

    vector<int> bfs(int x) {
        vector<int> rtn(n, imax);
        rtn[x] = 0;
        queue<int> que;
        que.push(x);
        while (!que.empty()) {
            int y = que.front();
            int d = rtn[x];
            que.pop();
            for (int i = 0; i < g[y].size(); i++) {
                int to_x = g[y][i].to;
                if (d + g[y][i].co < rtn[to_x]) {
                    rtn[to_x] = d + g[y][i].co;
                    que.push(to_x);
                }
            }
        }
        return rtn;
    }
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

// 配列中の総和
template <class T> ll SM(vector<T> smv) {
    ll tmp = 0;
    rep(i, (int)smv.size()) tmp += smv[i];

    return tmp;
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

int main() {
    int h, w, red = 0;
    cin >> h >> w;
    vector<string> s(h);

    rep(i, h) cin >> s[i];
    dsu d(h * w);
    rep(i, h) {
        rep(j, w) {
            if (s[i][j] == '.')
                red++;
            if (i < h - 1 && s[i][j] == '#' && s[i + 1][j] == '#')
                d.merge(i * w + j, (i + 1) * w + j);
            if (j < w - 1 && s[i][j] == '#' && s[i][j + 1] == '#')
                d.merge(i * w + j, i * w + j + 1);
        }
    }

    int defo;
    set<int> st;
    rep(i, h) {
        rep(j, w) {
            if (s[i][j] == '.')
                continue;
            st.insert(d.leader(i * w + j));
            // cout << "l" << d.leader(i * w + j) << endl;
        }
    }
    defo = st.size();

    mint ans = 0;
    rep(i, h) {
        rep(j, w) {
            if (s[i][j] == '#')
                continue;
            set<int> dir4;
            int cnt = 0;
            if (i != 0 && s[i - 1][j] == '#') {
                dir4.insert(d.leader((i - 1) * w + j));
                cnt++;
            }
            if (i != h - 1 && s[i + 1][j] == '#') {
                dir4.insert(d.leader((i + 1) * w + j));
                cnt++;
            }
            if (j != 0 && s[i][j - 1] == '#') {
                dir4.insert(d.leader(i * w + j - 1));
                cnt++;
            }
            if (j != w - 1 && s[i][j + 1] == '#') {
                dir4.insert(d.leader(i * w + j + 1));
                cnt++;
            }
            ans += defo - (dir4.size() - 1);
            // cout << defo - (dir4.size() - 1) << endl;
        }
    }
    ans /= red;

    cout << ans.val() << endl;

    return 0;
}