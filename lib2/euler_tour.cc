// オイラーツアー euler_tour 部分木クエリ O(V)

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

// ========== ライブラリ本体 ==========

// オイラーツアー
// 木をDFSで巡回し、各頂点の入り時刻と出時刻を記録
struct EulerTour {
    int n;
    vector<int> euler;       // オイラーツアーの頂点列
    vector<int> in_time;     // 各頂点の入り時刻
    vector<int> out_time;    // 各頂点の出時刻
    vector<int> depth;       // 各頂点の深さ
    int timer;

    EulerTour(Graph& g, int root = 0) : n(g.n), in_time(n), out_time(n), depth(n), timer(0) {
        dfs(g, root, -1, 0);
    }

    void dfs(Graph& g, int v, int parent, int d) {
        in_time[v] = timer++;
        euler.push_back(v);
        depth[v] = d;

        for (int next : g.adj_unweighted[v]) {
            if (next == parent) continue;
            dfs(g, next, v, d + 1);
            euler.push_back(v);  // 戻ってきたときも記録
            timer++;
        }

        out_time[v] = timer - 1;
    }

    // vの部分木に含まれるか判定
    bool is_in_subtree(int v, int u) {
        return in_time[v] <= in_time[u] && in_time[u] <= out_time[v];
    }

    // vを根とする部分木のサイズ
    int subtree_size(int v) {
        return (out_time[v] - in_time[v] + 2) / 2;
    }
};

// LCAのためのオイラーツアー
struct EulerTourLCA {
    int n;
    vector<int> euler;           // オイラーツアーの頂点列
    vector<int> first_appear;    // 各頂点が最初に現れる位置
    vector<int> depth;           // オイラーツアー上の各位置での深さ

    EulerTourLCA(Graph& g, int root = 0) : n(g.n), first_appear(n, -1) {
        dfs(g, root, -1, 0);
    }

    void dfs(Graph& g, int v, int parent, int d) {
        if (first_appear[v] == -1) {
            first_appear[v] = euler.size();
        }
        euler.push_back(v);
        depth.push_back(d);

        for (int next : g.adj_unweighted[v]) {
            if (next == parent) continue;
            dfs(g, next, v, d + 1);
            euler.push_back(v);
            depth.push_back(d);
        }
    }

    // u, vのLCAを求める（RMQが必要）
    // ここでは簡易版として全探索で実装
    int lca(int u, int v) {
        int l = min(first_appear[u], first_appear[v]);
        int r = max(first_appear[u], first_appear[v]);

        int min_depth = depth[l];
        int lca_node = euler[l];

        for (int i = l + 1; i <= r; i++) {
            if (depth[i] < min_depth) {
                min_depth = depth[i];
                lca_node = euler[i];
            }
        }

        return lca_node;
    }
};

// HLD用のオイラーツアー（Heavy-Light Decomposition）
struct EulerTourHLD {
    int n;
    vector<int> in_time;      // 入り時刻
    vector<int> out_time;     // 出時刻
    vector<int> euler_order;  // DFS順の頂点列
    vector<int> parent;       // 親
    vector<int> depth;        // 深さ
    vector<int> subtree_size; // 部分木サイズ
    int timer;

    EulerTourHLD(Graph& g, int root = 0) : n(g.n), in_time(n), out_time(n),
                                           parent(n, -1), depth(n), subtree_size(n), timer(0) {
        calc_size(g, root, -1);
        dfs(g, root, -1);
    }

    int calc_size(Graph& g, int v, int p) {
        subtree_size[v] = 1;
        parent[v] = p;
        for (int& next : g.adj_unweighted[v]) {
            if (next == p) continue;
            subtree_size[v] += calc_size(g, next, v);
        }
        return subtree_size[v];
    }

    void dfs(Graph& g, int v, int p) {
        in_time[v] = timer++;
        euler_order.push_back(v);

        // Heavy edgeを優先してDFS
        for (int& next : g.adj_unweighted[v]) {
            if (next == p) continue;
            depth[next] = depth[v] + 1;
            dfs(g, next, v);
        }

        out_time[v] = timer - 1;
    }
};

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的なオイラーツアー
    cout << "例1: 基本的なオイラーツアー" << endl;
    Graph g1(7);
    g1.add_unweighted_undirected_edge(0, 1);
    g1.add_unweighted_undirected_edge(0, 2);
    g1.add_unweighted_undirected_edge(1, 3);
    g1.add_unweighted_undirected_edge(1, 4);
    g1.add_unweighted_undirected_edge(2, 5);
    g1.add_unweighted_undirected_edge(2, 6);

    EulerTour et(g1, 0);

    cout << "オイラーツアー: ";
    for (int v : et.euler) cout << v << " ";
    cout << endl;

    cout << "各頂点の時刻:" << endl;
    for (int i = 0; i < g1.n; i++) {
        cout << "  頂点" << i << ": in=" << et.in_time[i] << ", out=" << et.out_time[i] << endl;
    }

    cout << "頂点1の部分木サイズ: " << et.subtree_size(1) << endl;
    cout << "頂点3は頂点1の部分木に含まれる: " << (et.is_in_subtree(1, 3) ? "Yes" : "No") << endl;
    cout << "頂点5は頂点1の部分木に含まれる: " << (et.is_in_subtree(1, 5) ? "Yes" : "No") << endl;
    cout << endl;

    // 例2: LCA用オイラーツアー
    cout << "例2: LCA用オイラーツアー" << endl;
    EulerTourLCA et_lca(g1, 0);

    cout << "LCA(3, 4) = " << et_lca.lca(3, 4) << endl;
    cout << "LCA(3, 5) = " << et_lca.lca(3, 5) << endl;
    cout << "LCA(4, 6) = " << et_lca.lca(4, 6) << endl;

    return 0;
}