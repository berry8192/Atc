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
// using namespace atcoder;

int imax = 2147483647;
ll lmax = 9223372036854775807;
// using mint = modint1000000007;
// using mint = modint998244353;
//  ll mod=998244353;
//  ll mod=1000000007;

struct Edge {
    long long to, cost;
};
struct S_rmq {
    long long value;
    long long index;
};
S_rmq op_rmq(S_rmq a, S_rmq b) {
    if (a.value < b.value)
        return a;
    else
        return b;
}
S_rmq E_rmq() { return {(1LL << 60), -1LL}; }
struct S_rsq {
    long long value;
};
S_rsq op_rsq(S_rsq a, S_rsq b) { return {a.value + b.value}; }
S_rsq E_rsq() { return {0}; }

struct weighted_euler_tour {
    vector<long long> depth, visit, cost1, cost2;
    vector<long long> discover, finishing;
    vector<vector<Edge>> g;
    long long n;
    map<pair<long long, long long>, long long> edge_index1;
    map<pair<long long, long long>, long long> edge_index2;

    atcoder::segtree<S_rmq, op_rmq, E_rmq> rmq;
    atcoder::segtree<S_rsq, op_rsq, E_rsq> rsq1;
    atcoder::segtree<S_rsq, op_rsq, E_rsq> rsq2;

    weighted_euler_tour(long long n = 1,
                        vector<vector<Edge>> g = vector<vector<Edge>>()) {
        init(n, g);
    }

    void init(long long n, vector<vector<Edge>> g) {
        this->n = n;
        depth.clear();
        visit.clear();
        discover.assign(n, (1 << 30));
        finishing.assign(n, -1);
        this->g = g;
        this->g.resize(n);
    }

    void add_edge(long long u, long long v, long long cost) {
        g[u].push_back({v, cost});
        g[v].push_back({u, cost});
    }

    void dfs(long long root) {
        cost1.push_back(0);
        cost2.push_back(0);
        Dfs(root, -1, 0);
        for (long long i = 0; i < int(visit.size()); i++) {
            discover[visit[i]] = min(discover[visit[i]], i);
            finishing[visit[i]] = max(finishing[visit[i]], i + 1);
        }
        vector<S_rmq> depth_v(int(depth.size()));
        for (long long i = 0; i < int(depth.size()); i++) {
            depth_v[i] = {depth[i], visit[i]};
        }
        vector<S_rsq> cost1_v(int(cost1.size()));
        for (long long i = 0; i < int(cost1.size()); i++) {
            cost1_v[i] = {cost1[i]};
        }
        vector<S_rsq> cost2_v(int(cost2.size()));
        for (long long i = 0; i < int(cost2.size()); i++) {
            cost2_v[i] = {cost2[i]};
        }

        rmq = atcoder::segtree<S_rmq, op_rmq, E_rmq>(depth_v);
        rsq1 = atcoder::segtree<S_rsq, op_rsq, E_rsq>(cost1_v);
        rsq2 = atcoder::segtree<S_rsq, op_rsq, E_rsq>(cost2_v);
    }

    void Dfs(long long v, long long p, long long d) {
        visit.push_back(v);
        depth.push_back(d);
        for (Edge u : g[v]) {
            if (u.to == p)
                continue;
            cost1.push_back(u.cost);
            cost2.push_back(u.cost);
            edge_index1[{min(v, u.to), max(v, u.to)}] = cost1.size() - 1;
            edge_index2[{v, u.to}] = cost2.size() - 1;

            Dfs(u.to, v, d + 1);
            visit.push_back(v);
            depth.push_back(d);
            cost1.push_back(0);
            cost2.push_back(-u.cost);
            edge_index2[{u.to, v}] = cost2.size() - 1;
        }
    }

    long long lca(long long u, long long v) {
        return rmq
            .prod(min(discover[u], discover[v]), max(discover[u], discover[v]))
            .index;
    }

    long long pe(long long u) { return rsq2.prod(0, discover[u] + 1).value; }

    long long dist(long long u, long long v) {
        if (u == v)
            return 0;
        return pe(u) + pe(v) - 2 * pe(lca(u, v));
    }

    long long sum(long long x) {
        return rsq1.prod(discover[x], finishing[x]).value;
    }

    void update(long long u, long long v, long long x) {
        if (u > v)
            swap(u, v);
        if (edge_index1.find({u, v}) == edge_index1.end()) {
            // cout << "edge not found" << endl;
            return;
        }
        rsq1.set(edge_index1[{u, v}], {x});

        if (depth[discover[u]] > depth[discover[v]])
            swap(u, v);
        rsq2.set(edge_index2[{u, v}], {x});
        rsq2.set(edge_index2[{v, u}], {-x});
    }

    void add(long long u, long long v, long long x) {
        if (u > v)
            swap(u, v);
        if (edge_index1.find({u, v}) == edge_index1.end()) {
            // cout << "edge not found" << endl;
            return;
        }
        rsq1.set(
            edge_index1[{u, v}],
            {rsq1.prod(edge_index1[{u, v}], edge_index1[{u, v}] + 1).value +
             x});

        if (depth[u] > depth[v])
            swap(u, v);
        rsq2.set(
            edge_index2[{u, v}],
            {rsq2.prod(edge_index2[{u, v}], edge_index2[{u, v}] + 1).value +
             x});
        rsq2.set(
            edge_index2[{v, u}],
            {rsq2.prod(edge_index2[{v, u}], edge_index2[{v, u}] + 1).value -
             x});
    }
};

int main() {
    int n;
    cin >> n;

    weighted_euler_tour et(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--; // 0indexedにしてください
        et.add_edge(u, v, w);
    }
    /*
        こちらの書き方もできます
        vector<vector<Edge>> g(n);
        for(int i=0;i<n-1;i++){
            int u,v,w; cin >> u >> v >> w;
            u--; v--;
            g[u].push_back({v,w});
            g[v].push_back({u,w});
        }
        weighted_euler_tour et(n,g);
    */
    et.dfs(0); // これを忘れないで下さい(セグフォります)

    cout << et.lca(2, 3) << endl; // 頂点2と頂点3のLCAを出力します。
    cout << et.dist(2, 3) << endl; // 頂点2と頂点3の距離を出力します。
    cout << et.sum(3)
         << endl; // 頂点0を含まない方の部分木の辺の重みの合計を求めます。
    et.update(1, 3, 2); // 頂点1,3間の辺の重みを2に変更します。
    et.add(
        1, 3,
        1); // 頂点1,3間の辺の辺の重みに1を加えます。つまり、重みは現在3です。
}