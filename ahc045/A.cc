#include <bits/stdc++.h>
using namespace std;

struct Point {
    int id, lx, rx, ly, ry;
};

struct Edge {
    int u, v;
    int weight;
    bool operator<(const Edge &other) const { return weight < other.weight; }
};

struct UnionFind {
    vector<int> parent, rank;

    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int x, int y) {
        int xr = find(x), yr = find(y);
        if (xr == yr)
            return false;
        if (rank[xr] < rank[yr])
            parent[xr] = yr;
        else if (rank[xr] > rank[yr])
            parent[yr] = xr;
        else {
            parent[yr] = xr;
            rank[xr]++;
        }
        return true;
    }
};

int euclidean_distance(Point &a, Point &b) {
    int dx = max(0, max(a.lx - b.rx, b.lx - a.rx));
    int dy = max(0, max(a.ly - b.ry, b.ly - a.ry));
    return dx * dx + dy * dy;
}

vector<Edge> build_edges(vector<Point> &cities) {
    vector<Edge> edges;
    int n = cities.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int weight = euclidean_distance(cities[i], cities[j]);
            edges.push_back({cities[i].id, cities[j].id, weight});
        }
    }
    return edges;
}

vector<Edge> kruskal(int n, vector<Edge> &edges) {
    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    vector<Edge> mst;
    for (auto &e : edges) {
        if (uf.unite(e.u, e.v)) {
            mst.push_back(e);
            if (mst.size() == n - 1)
                break;
        }
    }
    return mst;
}

void output(vector<vector<int>> &groups, vector<vector<Edge>> &mst_edges) {
    cout << "!" << endl;
    for (int i = 0; i < groups.size(); ++i) {
        for (int j = 0; j < groups[i].size(); ++j) {
            if (j > 0)
                cout << " ";
            cout << groups[i][j];
        }
        cout << endl;
        for (auto &e : mst_edges[i]) {
            cout << e.u << " " << e.v << endl;
        }
    }
}

int main() {
    int N, M, Q, L, W;
    cin >> N >> M >> Q >> L >> W;

    vector<int> G(M);
    for (int i = 0; i < M; ++i)
        cin >> G[i];

    vector<Point> cities(N);
    for (int i = 0; i < N; ++i) {
        cin >> cities[i].lx >> cities[i].rx >> cities[i].ly >> cities[i].ry;
        cities[i].id = i;
    }
    vector<Edge> edges = build_edges(cities);
    vector<Edge> mst = kruskal(N, edges);

    vector<vector<int>> groups(M);
    vector<vector<Edge>> mst_edges(M);

    int idx = 0;
    for (int i = 0; i < M; ++i) {
        vector<Point> group_points;
        for (int j = 0; j < G[i]; ++j) {
            groups[i].push_back(cities[idx].id);
            group_points.push_back(cities[idx]);
            idx++;
        }
        vector<Edge> group_edges = build_edges(group_points);
        mst_edges[i] = kruskal(G[i], group_edges);
    }

    output(groups, mst_edges);

    int queries_used = 0;
    UnionFind global_uf(N);

    for (auto &e : mst) {
        global_uf.unite(e.u, e.v);
    }

    while (queries_used < Q) {
        int u, v;
        cin >> u >> v;
        if (global_uf.find(u) == global_uf.find(v)) {
            cout << "0" << endl;
        } else {
            int min_distance = INT_MAX;
            for (auto &e : edges) {
                if (global_uf.find(e.u) != global_uf.find(e.v)) {
                    min_distance = min(min_distance, e.weight);
                }
            }
            cout << min_distance << endl;
            queries_used++;
        }
    }

    return 0;
}
