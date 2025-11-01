// ダイクストラ dijkstra 最短経路 O((E+V)logV)

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

// ========== 共通グラフ構造体 ==========

// エッジ（隣接リスト用）
struct Edge {
    int to;
    long long cost;
    Edge(int to, long long cost) : to(to), cost(cost) {}
};

// エッジ（エッジリスト用：クラスカル法など）
struct EdgeList {
    int from, to;
    long long cost;
    EdgeList(int from, int to, long long cost) : from(from), to(to), cost(cost) {}
    bool operator<(const EdgeList& other) const {
        return cost < other.cost;
    }
};

// グラフクラス（隣接リスト表現 + エッジリスト）
struct Graph {
    int n;  // 頂点数
    vector<vector<Edge>> adj;  // 隣接リスト
    vector<vector<int>> adj_unweighted;  // 重みなし用
    vector<EdgeList> edges;  // エッジリスト（クラスカル法など用）

    Graph(int n) : n(n), adj(n), adj_unweighted(n) {}

    // 重み付き有向辺を追加
    void add_edge(int from, int to, long long cost = 1) {
        adj[from].push_back(Edge(to, cost));
        adj_unweighted[from].push_back(to);
        edges.push_back(EdgeList(from, to, cost));
    }

    // 重み付き無向辺を追加
    void add_undirected_edge(int from, int to, long long cost = 1) {
        adj[from].push_back(Edge(to, cost));
        adj[to].push_back(Edge(from, cost));
        adj_unweighted[from].push_back(to);
        adj_unweighted[to].push_back(from);
        edges.push_back(EdgeList(from, to, cost));
    }

    // 重みなし有向辺を追加
    void add_unweighted_edge(int from, int to) {
        adj_unweighted[from].push_back(to);
        adj[from].push_back(Edge(to, 1));
        edges.push_back(EdgeList(from, to, 1));
    }

    // 重みなし無向辺を追加
    void add_unweighted_undirected_edge(int from, int to) {
        adj_unweighted[from].push_back(to);
        adj_unweighted[to].push_back(from);
        adj[from].push_back(Edge(to, 1));
        adj[to].push_back(Edge(from, 1));
        edges.push_back(EdgeList(from, to, 1));
    }
};

// ========== ライブラリ本体 ==========

// ダイクストラ法による単一始点最短経路
// start: 始点
// 返り値: 各頂点への最短距離（到達不可能な場合はINF）
vector<long long> dijkstra(Graph& g, int start) {
    const long long INF = 1e18;
    vector<long long> dist(g.n, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();

        if (dist[v] < d) continue;

        for (auto& e : g.adj[v]) {
            if (dist[v] + e.cost < dist[e.to]) {
                dist[e.to] = dist[v] + e.cost;
                pq.push({dist[e.to], e.to});
            }
        }
    }

    return dist;
}

// 経路復元付きダイクストラ
// 返り値: {距離配列, 経路復元用の前頂点配列}
pair<vector<long long>, vector<int>> dijkstra_with_path(Graph& g, int start) {
    const long long INF = 1e18;
    vector<long long> dist(g.n, INF);
    vector<int> prev(g.n, -1);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();

        if (dist[v] < d) continue;

        for (auto& e : g.adj[v]) {
            if (dist[v] + e.cost < dist[e.to]) {
                dist[e.to] = dist[v] + e.cost;
                prev[e.to] = v;
                pq.push({dist[e.to], e.to});
            }
        }
    }

    return {dist, prev};
}

// 経路復元
vector<int> restore_path(const vector<int>& prev, int goal) {
    vector<int> path;
    for (int v = goal; v != -1; v = prev[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

// ========== サンプルコード ==========

int main() {
    // 例: 5頂点のグラフ
    Graph g(5);
    g.add_undirected_edge(0, 1, 10);
    g.add_undirected_edge(0, 2, 5);
    g.add_undirected_edge(1, 2, 2);
    g.add_undirected_edge(1, 3, 1);
    g.add_undirected_edge(2, 3, 9);
    g.add_undirected_edge(2, 4, 2);
    g.add_undirected_edge(3, 4, 4);

    // 通常のダイクストラ
    vector<long long> dist = dijkstra(g, 0);

    cout << "頂点0からの最短距離:" << endl;
    for (int i = 0; i < g.n; i++) {
        cout << "  頂点" << i << ": " << dist[i] << endl;
    }
    cout << endl;

    // 経路復元付きダイクストラ
    auto [dist2, prev] = dijkstra_with_path(g, 0);

    cout << "頂点0から頂点4への最短経路:" << endl;
    vector<int> path = restore_path(prev, 4);
    cout << "  経路: ";
    for (int i = 0; i < path.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << path[i];
    }
    cout << endl;
    cout << "  距離: " << dist2[4] << endl;

    return 0;
}