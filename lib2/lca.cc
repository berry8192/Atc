// 最近共通祖先 lca lowest_common_ancestor binary_lifting

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
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

// ========== LCAライブラリ ==========

struct LCA {
    Graph& g;
    int n, log_n;
    vector<vector<int>> parent;  // parent[k][v] = vの2^k個上の祖先
    vector<int> depth;
    int root;
    bool is_built;

    LCA(Graph& graph, int root = 0) : g(graph), n(graph.n), root(root), is_built(false) {
        log_n = 0;
        while ((1 << log_n) <= n) log_n++;
        parent.assign(log_n, vector<int>(n, -1));
        depth.assign(n, -1);
    }

    // DFSで深さと親を設定
    void dfs(int v, int p, int d) {
        parent[0][v] = p;
        depth[v] = d;
        for (int u : g.adj_unweighted[v]) {
            if (u != p && depth[u] == -1) {
                dfs(u, v, d + 1);
            }
        }
    }

    // 前処理: Binary Liftingの表を構築
    void build() {
        dfs(root, -1, 0);

        // Binary Liftingの表を構築
        for (int k = 0; k + 1 < log_n; k++) {
            for (int v = 0; v < n; v++) {
                if (parent[k][v] != -1) {
                    parent[k + 1][v] = parent[k][parent[k][v]];
                }
            }
        }

        is_built = true;
    }

    // 頂点vからk個上の祖先を取得
    int kth_ancestor(int v, int k) {
        if (!is_built) build();
        if (depth[v] < k) return -1;

        for (int i = 0; i < log_n; i++) {
            if ((k >> i) & 1) {
                v = parent[i][v];
                if (v == -1) return -1;
            }
        }
        return v;
    }

    // LCAを計算
    int lca(int u, int v) {
        if (!is_built) build();

        if (depth[u] > depth[v]) swap(u, v);

        // vをuと同じ深さまで上げる
        v = kth_ancestor(v, depth[v] - depth[u]);

        if (u == v) return u;

        // Binary Searchで最近共通祖先を見つける
        for (int k = log_n - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }

        return parent[0][u];
    }

    // 二点間の距離
    int distance(int u, int v) {
        if (!is_built) build();
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    // 頂点vの深さを取得
    int get_depth(int v) {
        if (!is_built) build();
        return depth[v];
    }

    // u-v パス上でuからk番目の頂点を取得（0-indexed）
    int kth_node_on_path(int u, int v, int k) {
        if (!is_built) build();

        int lca_node = lca(u, v);
        int dist_u_lca = depth[u] - depth[lca_node];
        int dist_v_lca = depth[v] - depth[lca_node];

        if (k <= dist_u_lca) {
            return kth_ancestor(u, k);
        } else {
            return kth_ancestor(v, dist_u_lca + dist_v_lca - k);
        }
    }

    // u-v パスの中点を取得（距離が偶数の場合）
    int midpoint(int u, int v) {
        if (!is_built) build();
        int dist = distance(u, v);
        if (dist % 2 == 1) return -1;  // 中点が存在しない
        return kth_node_on_path(u, v, dist / 2);
    }

    // 頂点vが頂点uの祖先かどうか判定
    bool is_ancestor(int u, int v) {
        if (!is_built) build();
        return lca(u, v) == u;
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: 基本的なLCA" << endl;
    Graph tree1(10);

    // 木を構築（根は0）
    //       0
    //      / \
    //     1   2
    //    /|   |\
    //   3 4   5 6
    //  /      |
    // 7       8
    //         |
    //         9

    tree1.add_unweighted_undirected_edge(0, 1);
    tree1.add_unweighted_undirected_edge(0, 2);
    tree1.add_unweighted_undirected_edge(1, 3);
    tree1.add_unweighted_undirected_edge(1, 4);
    tree1.add_unweighted_undirected_edge(2, 5);
    tree1.add_unweighted_undirected_edge(2, 6);
    tree1.add_unweighted_undirected_edge(3, 7);
    tree1.add_unweighted_undirected_edge(5, 8);
    tree1.add_unweighted_undirected_edge(8, 9);

    LCA lca1(tree1, 0);

    cout << "LCA(7, 9) = " << lca1.lca(7, 9) << endl;
    cout << "LCA(4, 6) = " << lca1.lca(4, 6) << endl;
    cout << "LCA(3, 4) = " << lca1.lca(3, 4) << endl;
    cout << "距離(7, 9) = " << lca1.distance(7, 9) << endl;
    cout << "距離(4, 6) = " << lca1.distance(4, 6) << endl;
    cout << endl;

    cout << "例2: k番目の祖先" << endl;
    for (int k = 1; k <= 3; k++) {
        int ancestor = lca1.kth_ancestor(9, k);
        cout << "頂点9の" << k << "個上の祖先: " << ancestor << endl;
    }
    cout << endl;

    cout << "例3: パス上のk番目の頂点" << endl;
    int u = 7, v = 9;
    int dist = lca1.distance(u, v);
    cout << "パス " << u << " -> " << v << " (距離" << dist << "):" << endl;
    for (int k = 0; k <= dist; k++) {
        int node = lca1.kth_node_on_path(u, v, k);
        cout << "  " << k << "番目: " << node << endl;
    }
    cout << endl;

    cout << "例4: 中点とその他の操作" << endl;
    cout << "パス 4-6 の中点: " << lca1.midpoint(4, 6) << endl;
    cout << "パス 7-8 の中点: " << lca1.midpoint(7, 8) << " (距離が奇数のため-1)" << endl;
    cout << "頂点0は頂点7の祖先か: " << (lca1.is_ancestor(0, 7) ? "はい" : "いいえ") << endl;
    cout << "頂点1は頂点7の祖先か: " << (lca1.is_ancestor(1, 7) ? "はい" : "いいえ") << endl;
    cout << "頂点3は頂点7の祖先か: " << (lca1.is_ancestor(3, 7) ? "はい" : "いいえ") << endl;

    cout << endl;
    cout << "各頂点の深さ:" << endl;
    for (int i = 0; i < tree1.n; i++) {
        cout << "頂点" << i << ": 深さ" << lca1.get_depth(i) << endl;
    }

    return 0;
}