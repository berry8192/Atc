// グラフテンプレート graph_template 隣接リスト

#include <iostream>
#include <vector>
#include <queue>
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

// ========== サンプルコード ==========

int main() {
    // 例1: 重み付きグラフの構築
    cout << "例1: 重み付きグラフ" << endl;
    Graph g1(5);
    g1.add_undirected_edge(0, 1, 10);
    g1.add_undirected_edge(0, 2, 5);
    g1.add_undirected_edge(1, 2, 2);
    g1.add_undirected_edge(1, 3, 1);
    g1.add_undirected_edge(2, 3, 9);
    g1.add_undirected_edge(2, 4, 2);
    g1.add_undirected_edge(3, 4, 4);

    cout << "頂点0からの辺:" << endl;
    for (auto& e : g1.adj[0]) {
        cout << "  -> 頂点" << e.to << " (コスト: " << e.cost << ")" << endl;
    }
    cout << endl;

    // 例2: 重みなしグラフの構築
    cout << "例2: 重みなしグラフ" << endl;
    Graph g2(4);
    g2.add_unweighted_undirected_edge(0, 1);
    g2.add_unweighted_undirected_edge(0, 2);
    g2.add_unweighted_undirected_edge(1, 2);
    g2.add_unweighted_undirected_edge(2, 3);

    cout << "各頂点の次数:" << endl;
    for (int i = 0; i < g2.n; i++) {
        cout << "  頂点" << i << ": " << g2.adj_unweighted[i].size() << endl;
    }
    cout << endl;

    // 例3: 有向グラフ
    cout << "例3: 有向グラフ（トポロジカルソート用）" << endl;
    Graph g3(5);
    g3.add_edge(0, 1);
    g3.add_edge(0, 2);
    g3.add_edge(1, 3);
    g3.add_edge(2, 3);
    g3.add_edge(3, 4);

    vector<int> in_degree(g3.n, 0);
    for (int i = 0; i < g3.n; i++) {
        for (auto& e : g3.adj[i]) {
            in_degree[e.to]++;
        }
    }

    cout << "入次数:" << endl;
    for (int i = 0; i < g3.n; i++) {
        cout << "  頂点" << i << ": " << in_degree[i] << endl;
    }

    return 0;
}