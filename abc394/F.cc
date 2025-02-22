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
ll oneormore = -1;
struct Graph {
    int n, m, h, w;
    vector<vector<Edge>> g;

    Graph() {};

    void init(int nn, int mm, bool weight = false, bool directed = false) {
        n = nn;
        m = mm;
        // n頂点、m辺、重み有無、有向無向
        vector<int> uu(mm), vv(mm), cnt(nn);
        rep(i, mm) {
            cin >> uu[i] >> vv[i];
            uu[i]--;
            vv[i]--;
            cnt[uu[i]]++;
            cnt[vv[i]]++;
        }
        g.resize(nn);

        for (int i = 0; i < mm; i++) {
            if (cnt[uu[i]] >= 4) {
                oneormore = 1;
                if (cnt[vv[i]] >= 4) {
                    g[uu[i]].push_back({uu[i], vv[i], 1});
                    g[vv[i]].push_back({vv[i], uu[i], 1});
                }
            }
        }
    }
    map<int, int> bfs(int x) {
        map<int, int> rtn;
        rtn[x] = 0;
        queue<int> que;
        que.push(x);
        while (!que.empty()) {
            int y = que.front();
            int d = rtn[y];
            que.pop();
            for (int i = 0; i < g[y].size(); i++) {
                int to_x = g[y][i].to;
                if (rtn.find(to_x) == rtn.end()) {
                    rtn[to_x] = imax;
                }
                if (d + g[y][i].cost < rtn[to_x]) {
                    rtn[to_x] = d + g[y][i].cost;
                    que.push(to_x);
                }
            }
        }
        return rtn;
    }
    ll calc_diameter() {
        int ma = -1;
        vector<int> seen(n);
        rep(i, n) {
            if (!seen[i] && g[i].size() == 1) {
                map<int, int> tmp = bfs(i);
                // cout << i << endl;
                // PV(tmp);
                int maa = -1;
                int mai;
                for (auto m : tmp) {
                    if (m.second != imax) {
                        maa = max(m.second + 1, maa);
                        mai = m.first;
                        seen[m.first] = 1;
                    }
                }
                tmp = bfs(mai);
                for (auto m : tmp) {
                    if (m.second != imax) {
                        ma = max(m.second + 1, maa);
                        seen[m.first] = 1;
                    }
                }
                // PV(seen);
            }
        }
        return ma;
    }
};

int main() {
    int n;
    cin >> n;

    Graph g;
    g.init(n, n - 1);
    // cout << "e" << endl;
    int dia = max(oneormore, g.calc_diameter());
    cout << 3 * dia + 2 << endl;

    return 0;
}