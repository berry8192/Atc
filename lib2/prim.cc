// プリム法 prim 最小全域木 minimum_spanning_tree 優先度付きキュー

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
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

// ========== プリム法ライブラリ ==========

struct PrimMST {
    Graph& g;
    vector<EdgeList> mst_edges;
    long long total_cost;
    bool is_built;

    PrimMST(Graph& graph) : g(graph), total_cost(0), is_built(false) {}

    // 最小全域木を構築（指定した頂点から開始）
    bool build(int start = 0) {
        mst_edges.clear();
        total_cost = 0;
        is_built = false;

        if (start >= g.n) return false;

        vector<bool> in_mst(g.n, false);
        priority_queue<pair<long long, pair<int, int>>,
                      vector<pair<long long, pair<int, int>>>,
                      greater<pair<long long, pair<int, int>>>> pq;

        in_mst[start] = true;

        // 開始頂点から出る辺を優先度付きキューに追加
        for (const auto& edge : g.adj[start]) {
            pq.push({edge.cost, {start, edge.to}});
        }

        while (!pq.empty() && mst_edges.size() < g.n - 1) {
            auto [cost, edge_pair] = pq.top();
            pq.pop();
            int from = edge_pair.first;
            int to = edge_pair.second;

            if (in_mst[to]) continue;

            // 辺を最小全域木に追加
            in_mst[to] = true;
            mst_edges.push_back(EdgeList(from, to, cost));
            total_cost += cost;

            // 新しい頂点から出る辺を追加
            for (const auto& edge : g.adj[to]) {
                if (!in_mst[edge.to]) {
                    pq.push({edge.cost, {to, edge.to}});
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

    // 指定した頂点から到達可能な最大頂点数を取得
    int get_reachable_count(int start = 0) {
        vector<bool> visited(g.n, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        int count = 1;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (const auto& edge : g.adj[v]) {
                if (!visited[edge.to]) {
                    visited[edge.to] = true;
                    q.push(edge.to);
                    count++;
                }
            }
        }

        return count;
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

    PrimMST mst1(g1);
    if (mst1.build(0)) {
        cout << "最小全域木のコスト: " << mst1.get_total_cost() << endl;
        cout << "使用する辺:" << endl;
        for (const auto& edge : mst1.get_mst_edges()) {
            cout << "  " << edge.from << " - " << edge.to << " (コスト: " << edge.cost << ")" << endl;
        }
    } else {
        cout << "グラフが非連結です" << endl;
    }
    cout << endl;

    cout << "例2: 異なる開始点での構築" << endl;
    PrimMST mst2(g1);
    if (mst2.build(3)) {
        cout << "頂点3から開始した最小全域木のコスト: " << mst2.get_total_cost() << endl;
        cout << "使用する辺:" << endl;
        for (const auto& edge : mst2.get_mst_edges()) {
            cout << "  " << edge.from << " - " << edge.to << " (コスト: " << edge.cost << ")" << endl;
        }
    }
    cout << endl;

    cout << "例3: 非連結グラフ" << endl;
    Graph g3(5);
    g3.add_undirected_edge(0, 1, 1);
    g3.add_undirected_edge(1, 2, 2);
    g3.add_undirected_edge(3, 4, 3);

    PrimMST mst3(g3);
    cout << "頂点0から到達可能な頂点数: " << mst3.get_reachable_count(0) << endl;
    if (mst3.build(0)) {
        cout << "最小全域木のコスト: " << mst3.get_total_cost() << endl;
    } else {
        cout << "グラフが非連結のため、最小全域木は存在しません" << endl;
        cout << "部分的に選択された辺数: " << mst3.get_mst_edges().size() << endl;
    }

    return 0;
}