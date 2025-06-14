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
    void vertex_baika(int d) {
        vector<vector<Edge>> ng;
        ng.resize(n * d);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < g[i].size(); j++) {
                Edge edge = g[i][j];
                // cout << "original edge: " << edge.from << "->" << edge.to
                //      << " cost: " << edge.cost << endl;
                for (int k = 0; k < d; k++) {
                    int from = edge.from * d + k;
                    int to = edge.to * d + (k ^ edge.cost);
                    ng[from].push_back({from, to, edge.cost});
                    // cout << "edge: " << from << "->" << to
                    //      << " cost: " << edge.cost << endl;
                }
            }
        }
        g = ng;
        n *= d;
    }
    vector<int> bfs(int x) {
        vector<int> rtn(n, imax);
        rtn[x] = 0;
        queue<int> que;
        que.push(x);
        while (!que.empty()) {
            int y = que.front();
            que.pop();
            for (int i = 0; i < g[y].size(); i++) {
                int to_x = g[y][i].to;
                if (rtn[to_x] == imax) {
                    rtn[to_x] = 0;
                    que.push(to_x);
                }
            }
        }
        return rtn;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    int d = (1 << 10);

    Graph graph;
    graph.init(n, m, true, true);
    graph.vertex_baika(d);
    vector<int> dist = graph.bfs(0);

    rep(i, d) {
        if (dist[d * (n - 1) + i] != imax) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;

    return 0;
}
