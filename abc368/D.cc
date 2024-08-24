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
set<int> st, bad;
struct Graph {
    int n, m;
    vector<set<int>> g;

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

            g[uu].insert(vv);
            if (!directed) {
                g[vv].insert(uu);
            }
        }
    }
    // 葉を削除するDFS
    int prune_leaves(vector<int> &v) {
        vector<int> degree(n, 0);
        queue<int> leaves;

        // 初期の各頂点の次数を計算し、葉を探す
        for (int i = 0; i < n; i++) {
            degree[i] = g[i].size();
            if (degree[i] == 1) {
                leaves.push(i);
            }
        }

        // 削除フラグ
        vector<bool> removed(n, false);
        set<int> v_set(v.begin(), v.end());

        // 葉の削除
        while (!leaves.empty()) {
            int leaf = leaves.front();
            leaves.pop();

            // vに含まれる頂点は削除しない
            if (v_set.count(leaf))
                continue;

            removed[leaf] = true;
            for (int neighbor : g[leaf]) {
                g[neighbor].erase(leaf);
                degree[neighbor]--;

                // 新たに葉になった頂点を追加
                if (degree[neighbor] == 1) {
                    leaves.push(neighbor);
                }
            }
        }

        // 残った頂点数を数える
        int remaining = 0;
        for (int i = 0; i < n; i++) {
            if (!removed[i])
                remaining++;
        }
        return remaining;
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
    int n, k;
    vector<int> v;
    cin >> n >> k;
    Graph graph;
    graph.init(n, n - 1);
    v.resize(k);

    rep(i, k) {
        cin >> v[i];
        v[i]--;
    }

    // vector<int> sta(n);
    // rep(i, graph.euler_e.size()) {
    //     // cout << graph.euler_e[i].from << " " << graph.euler_e[i].to << " "
    //     //      << graph.euler_e[i].cost << endl;
    //     sta[graph.euler_e[i].from] = i;
    //     if(sta[graph.euler_e[i].to]=i;
    //     if (st.find(graph.euler_e[i].to) != st.end()) {
    //         stack.push(graph.euler_e[i].to);
    //     }
    //     if (stack.top() == graph.euler_e[i].from){
    //         stack.pop();

    //     }
    // }

    int result = graph.prune_leaves(v);
    cout << result << endl;

    return 0;
}