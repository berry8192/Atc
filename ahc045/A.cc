#include <algorithm>
#include <atcoder/dsu>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
using namespace atcoder;

struct Point {
    int lx, rx, ly, ry, id;
};

struct Edge {
    int u, v, weight;
};

int euclidean_distance(const Point &a, const Point &b) {
    int dx = max(0, max(a.lx - b.rx, b.lx - a.rx));
    int dy = max(0, max(a.ly - b.ry, b.ly - a.ry));
    return dx * dx + dy * dy;
}

vector<Edge> build_edges(const vector<Point> &points) {
    vector<Edge> edges;
    int n = points.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int weight = euclidean_distance(points[i], points[j]);
            edges.push_back({points[i].id, points[j].id, weight});
        }
    }
    return edges;
}

bool compare_edges(const Edge &a, const Edge &b) { return a.weight < b.weight; }

vector<Edge> kruskal(int n, vector<Edge> &edges) {
    vector<Edge> mst;
    dsu d(n);
    sort(edges.begin(), edges.end(), compare_edges);

    for (const Edge &e : edges) {
        if (!d.same(e.u, e.v)) {
            d.merge(e.u, e.v);
            mst.push_back(e);
        }
    }
    return mst;
}

void output(const vector<vector<int>> &groups,
            const vector<vector<Edge>> &mst_edges) {
    cout << "!" << endl;
    for (size_t i = 0; i < groups.size(); ++i) {
        for (int id : groups[i])
            cout << id << " ";
        cout << "-1" << endl;

        for (const auto &e : mst_edges[i]) {
            cout << e.u << " " << e.v << endl;
        }
        cout << "-1 -1" << endl;
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

    dsu global_dsu(N);
    for (auto &e : mst) {
        global_dsu.merge(e.u, e.v);
    }

    int queries_used = 0;
    while (queries_used < Q) {
        int u, v;
        cin >> u >> v;
        if (global_dsu.same(u, v)) {
            cout << "0" << endl;
        } else {
            int min_distance = INT_MAX;
            for (auto &e : edges) {
                if (!global_dsu.same(e.u, e.v)) {
                    min_distance = min(min_distance, e.weight);
                }
            }
            cout << min_distance << endl;
            global_dsu.merge(u, v);
        }
        queries_used++;
    }

    return 0;
}
