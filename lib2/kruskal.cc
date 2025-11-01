// クラスカル法 kruskal 最小全域木 minimum_spanning_tree union_find

#include <iostream>
#include <vector>
#include <algorithm>
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

// ========== Union-Find構造体 ==========

struct UnionFind {
    vector<int> parent, rank;

    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;

        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

// ========== クラスカル法ライブラリ ==========

struct KruskalMST {
    Graph& g;
    vector<EdgeList> mst_edges;
    long long total_cost;
    bool is_built;

    KruskalMST(Graph& graph) : g(graph), total_cost(0), is_built(false) {}

    // 最小全域木を構築
    bool build() {
        mst_edges.clear();
        total_cost = 0;
        is_built = false;

        if (g.edges.empty()) return false;

        vector<EdgeList> sorted_edges = g.edges;
        sort(sorted_edges.begin(), sorted_edges.end());

        UnionFind uf(g.n);

        for (const auto& edge : sorted_edges) {
            if (uf.unite(edge.from, edge.to)) {
                mst_edges.push_back(edge);
                total_cost += edge.cost;

                if (mst_edges.size() == g.n - 1) {
                    break;
                }
            }
        }

        is_built = (mst_edges.size() == g.n - 1);
        return is_built;
    }

    // 最小全域木のコストを取得
    long long get_total_cost() {
        if (!is_built) build();
        return total_cost;
    }

    // 最小全域木の辺を取得
    vector<EdgeList> get_mst_edges() {
        if (!is_built) build();
        return mst_edges;
    }

    // グラフが連結かどうか判定
    bool is_connected() {
        if (!is_built) build();
        return is_built;
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: 基本的な最小全域木" << endl;
    Graph g1(6);
    g1.add_undirected_edge(0, 1, 2);
    g1.add_undirected_edge(0, 2, 3);
    g1.add_undirected_edge(1, 2, 1);
    g1.add_undirected_edge(1, 3, 1);
    g1.add_undirected_edge(2, 3, 4);
    g1.add_undirected_edge(3, 4, 2);
    g1.add_undirected_edge(3, 5, 3);
    g1.add_undirected_edge(4, 5, 6);

    KruskalMST mst1(g1);
    if (mst1.build()) {
        cout << "最小全域木のコスト: " << mst1.get_total_cost() << endl;
        cout << "使用する辺:" << endl;
        for (const auto& edge : mst1.get_mst_edges()) {
            cout << "  " << edge.from << " - " << edge.to << " (コスト: " << edge.cost << ")" << endl;
        }
    } else {
        cout << "グラフが非連結です" << endl;
    }
    cout << endl;

    cout << "例2: 非連結グラフ" << endl;
    Graph g2(4);
    g2.add_undirected_edge(0, 1, 1);
    g2.add_undirected_edge(2, 3, 2);

    KruskalMST mst2(g2);
    if (mst2.build()) {
        cout << "最小全域木のコスト: " << mst2.get_total_cost() << endl;
    } else {
        cout << "グラフが非連結のため、最小全域木は存在しません" << endl;
        cout << "部分的に選択された辺数: " << mst2.get_mst_edges().size() << endl;
    }
    cout << endl;

    cout << "例3: 大きなコストの辺を含むグラフ" << endl;
    Graph g3(4);
    g3.add_undirected_edge(0, 1, 1);
    g3.add_undirected_edge(1, 2, 100);
    g3.add_undirected_edge(2, 3, 1);
    g3.add_undirected_edge(0, 3, 2);

    KruskalMST mst3(g3);
    if (mst3.build()) {
        cout << "最小全域木のコスト: " << mst3.get_total_cost() << endl;
        cout << "使用する辺:" << endl;
        for (const auto& edge : mst3.get_mst_edges()) {
            cout << "  " << edge.from << " - " << edge.to << " (コスト: " << edge.cost << ")" << endl;
        }
    }

    return 0;
}