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
    int n, m, h, w;
    vector<vector<Edge>> g;
    vector<Edge> edges;
    vector<vector<ll>> dist;
    vector<Edge> euler_e;
    vector<int> euler_used;

    Graph() {};

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

            g[uu].push_back({uu, vv, ww});
            edges.push_back({uu, vv, ww}); // edges
            if (!directed) {
                g[vv].push_back({vv, uu, ww});
                edges.push_back({vv, uu, ww}); // edges
            }
        }
    }
    void board_init(int hh, int ww, int &sh, int &sw, int &gh, int &gw) {
        // void board_init(int h, int w) {
        h = hh;
        w = ww;
        g.resize(h * w);

        vector<string> s(h);
        rep(i, h) { cin >> s[i]; }

        // for (int i = 0; i < h; i++) {
        //     for (int j = 0; j < w; j++) {
        //         if (s[i][j] == 'S') {
        //             sh = i;
        //             sw = j;
        //         }
        //         if (s[i][j] == 'G') {
        //             gh = i;
        //             gw = j;
        //         }
        //     }
        // }
        for (int i = 0; i < h - 1; i++) {
            for (int j = 0; j < w; j++) {
                if (s[i][j] != '#' && s[i + 1][j] != '#') {
                    int wei = 1;
                    g[i * w + j].push_back({i * w + j, (i + 1) * w + j, wei});
                    g[(i + 1) * w + j].push_back(
                        {(i + 1) * w + j, i * w + j, wei});
                    // edges.push_back({i*wid+j, (i+1)*wid+j, 1}); // edges
                    // edges.push_back({(i+1)*wid+j, i*wid+j, 1}); // edges
                }
            }
        }
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w - 1; j++) {
                if (s[i][j] != '#' && s[i][j + 1] != '#') {
                    int wei = 1;
                    g[i * w + j].push_back({i * w + j, i * w + j + 1, wei});
                    g[i * w + j + 1].push_back({i * w + j + 1, i * w + j, wei});
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
            int d = rtn[y];
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
    void euler_tour(int x) {
        if (euler_used[x])
            return;
        euler_used[x] = 1;
        rep(i, g[x].size()) {
            if (euler_used[g[x][i].to])
                continue;
            euler_e.push_back({g[x][i].to, x, g[x][i].cost});
            euler_tour(g[x][i].to);
            euler_e.push_back({x, g[x][i].to, g[x][i].cost});
        }
    }
    ll calc_diameter() {
        djikstra(0);
        ll ma = 0;
        int mai;
        rep(i, n) {
            ma = max(ma, dist[0][i]);
            mai = i;
        }
        djikstra(mai);
        rep(i, n) { ma = max(ma, dist[0][i]); }
        return ma;
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
    int q;
    cin >> q;

    vector<ll> rui = {0};
    ll rem = 0;
    rep(i, q) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll l;
            cin >> l;
            rui.push_back(rui[rui.size() - 1] + l);
        } else if (t == 2) {
            rem++;
        } else {
            ll k;
            cin >> k;
            ll tmp = rui[k - 1 + rem] - rui[rem];
            // cout << rui[k - 1 + rem] SP << rui[rem] << endl;
            cout << tmp << endl;
        }
    }
    return 0;
}