// ベルマンフォード bellman_ford 負辺 負閉路 O(VE)

#include <iostream>
#include <vector>
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

// ベルマンフォード法
// 負辺があっても最短経路を求められる
// 返り値: {最短距離配列, 負閉路が存在するか}
pair<vector<long long>, bool> bellman_ford(Graph& g, int start) {
    const long long INF = 1e18;
    vector<long long> dist(g.n, INF);
    dist[start] = 0;

    // V-1回の緩和
    for (int i = 0; i < g.n - 1; i++) {
        for (auto& e : g.edges) {
            if (dist[e.from] != INF && dist[e.from] + e.cost < dist[e.to]) {
                dist[e.to] = dist[e.from] + e.cost;
            }
        }
    }

    // 負閉路検出
    bool has_negative_cycle = false;
    for (auto& e : g.edges) {
        if (dist[e.from] != INF && dist[e.from] + e.cost < dist[e.to]) {
            has_negative_cycle = true;
            dist[e.to] = dist[e.from] + e.cost;
        }
    }

    return {dist, has_negative_cycle};
}

// 負閉路の影響を受ける頂点を検出
// 返り値: {最短距離配列, 負閉路の影響を受ける頂点}
pair<vector<long long>, vector<bool>> bellman_ford_extended(Graph& g, int start) {
    const long long INF = 1e18;
    vector<long long> dist(g.n, INF);
    vector<bool> negative(g.n, false);
    dist[start] = 0;

    // V-1回の緩和
    for (int i = 0; i < g.n - 1; i++) {
        for (auto& e : g.edges) {
            if (dist[e.from] != INF && dist[e.from] + e.cost < dist[e.to]) {
                dist[e.to] = dist[e.from] + e.cost;
            }
        }
    }

    // 負閉路の影響を受ける頂点を検出
    for (int i = 0; i < g.n; i++) {
        for (auto& e : g.edges) {
            if (dist[e.from] != INF && dist[e.from] + e.cost < dist[e.to]) {
                dist[e.to] = dist[e.from] + e.cost;
                negative[e.to] = true;
            }
            if (negative[e.from]) {
                negative[e.to] = true;
            }
        }
    }

    return {dist, negative};
}

// SPFA (Shortest Path Faster Algorithm)
// ベルマンフォードの高速化版
vector<long long> spfa(Graph& g, int start) {
    const long long INF = 1e18;
    vector<long long> dist(g.n, INF);
    vector<bool> in_queue(g.n, false);
    vector<int> cnt(g.n, 0);
    queue<int> q;

    dist[start] = 0;
    q.push(start);
    in_queue[start] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        in_queue[v] = false;

        for (auto& e : g.adj[v]) {
            if (dist[v] + e.cost < dist[e.to]) {
                dist[e.to] = dist[v] + e.cost;

                if (!in_queue[e.to]) {
                    q.push(e.to);
                    in_queue[e.to] = true;
                    cnt[e.to]++;

                    // 負閉路検出
                    if (cnt[e.to] > g.n) {
                        return vector<long long>();  // 負閉路あり
                    }
                }
            }
        }
    }

    return dist;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的なベルマンフォード
    cout << "例1: 基本的なベルマンフォード" << endl;
    Graph g1(5);
    g1.add_edge(0, 1, 4);
    g1.add_edge(0, 2, 3);
    g1.add_edge(1, 2, -2);
    g1.add_edge(1, 3, 1);
    g1.add_edge(1, 4, 2);
    g1.add_edge(2, 3, 3);
    g1.add_edge(3, 4, -1);

    auto [dist, has_negative] = bellman_ford(g1, 0);

    if (!has_negative) {
        cout << "頂点0からの最短距離:" << endl;
        for (int i = 0; i < g1.n; i++) {
            if (dist[i] == 1e18) {
                cout << "  頂点" << i << ": INF" << endl;
            } else {
                cout << "  頂点" << i << ": " << dist[i] << endl;
            }
        }
    } else {
        cout << "負閉路が存在します" << endl;
    }
    cout << endl;

    // 例2: 負閉路がある場合
    cout << "例2: 負閉路検出" << endl;
    Graph g2(4);
    g2.add_edge(0, 1, 1);
    g2.add_edge(1, 2, -3);
    g2.add_edge(2, 3, 1);
    g2.add_edge(3, 1, 1);

    auto [dist2, negative] = bellman_ford_extended(g2, 0);

    cout << "頂点0からの最短距離:" << endl;
    for (int i = 0; i < g2.n; i++) {
        if (negative[i]) {
            cout << "  頂点" << i << ": -INF (負閉路の影響)" << endl;
        } else if (dist2[i] == 1e18) {
            cout << "  頂点" << i << ": INF" << endl;
        } else {
            cout << "  頂点" << i << ": " << dist2[i] << endl;
        }
    }

    return 0;
}