// Heavy Light Decomposition hld 重軽分解 パス クエリ

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

// ========== HLDライブラリ ==========

struct HLD {
    Graph& g;
    int n, root;
    vector<int> parent, depth, subtree_size;
    vector<int> heavy_child;
    vector<int> head, position;
    int pos_counter;
    bool is_built;

    HLD(Graph& graph, int root = 0) : g(graph), n(graph.n), root(root), is_built(false) {
        parent.assign(n, -1);
        depth.assign(n, 0);
        subtree_size.assign(n, 0);
        heavy_child.assign(n, -1);
        head.assign(n, -1);
        position.assign(n, -1);
        pos_counter = 0;
    }

    // DFS1: 部分木のサイズとheavy childを計算
    void dfs1(int v, int p) {
        parent[v] = p;
        subtree_size[v] = 1;
        int max_subtree = 0;

        for (int u : g.adj_unweighted[v]) {
            if (u == p) continue;
            depth[u] = depth[v] + 1;
            dfs1(u, v);
            subtree_size[v] += subtree_size[u];

            if (subtree_size[u] > max_subtree) {
                max_subtree = subtree_size[u];
                heavy_child[v] = u;
            }
        }
    }

    // DFS2: Heavy pathの先頭を決定し、位置を割り当て
    void dfs2(int v, int h) {
        head[v] = h;
        position[v] = pos_counter++;

        // Heavy childを最初に処理
        if (heavy_child[v] != -1) {
            dfs2(heavy_child[v], h);
        }

        // Light childrenを処理
        for (int u : g.adj_unweighted[v]) {
            if (u == parent[v] || u == heavy_child[v]) continue;
            dfs2(u, u);  // 新しいchainの開始
        }
    }

    // HLDを構築
    void build() {
        dfs1(root, -1);
        dfs2(root, root);
        is_built = true;
    }

    // LCAを計算
    int lca(int u, int v) {
        if (!is_built) build();

        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) {
                u = parent[head[u]];
            } else {
                v = parent[head[v]];
            }
        }

        return depth[u] < depth[v] ? u : v;
    }

    // パス u-v 上の範囲をセグメント木用の区間として取得
    vector<pair<int, int>> path_ranges(int u, int v) {
        if (!is_built) build();

        vector<pair<int, int>> ranges;
        int l = lca(u, v);

        // uからlcaまで
        while (head[u] != head[l]) {
            ranges.push_back({position[head[u]], position[u]});
            u = parent[head[u]];
        }
        ranges.push_back({position[l], position[u]});

        // vからlcaまで（逆順で追加）
        vector<pair<int, int>> v_ranges;
        while (head[v] != head[l]) {
            v_ranges.push_back({position[head[v]], position[v]});
            v = parent[head[v]];
        }
        if (v != l) {
            v_ranges.push_back({position[l] + 1, position[v]});
        }

        // v側の範囲を逆順で追加
        for (int i = v_ranges.size() - 1; i >= 0; i--) {
            ranges.push_back(v_ranges[i]);
        }

        return ranges;
    }

    // 部分木 v の範囲を取得
    pair<int, int> subtree_range(int v) {
        if (!is_built) build();
        return {position[v], position[v] + subtree_size[v] - 1};
    }

    // 頂点の位置を取得
    int get_position(int v) {
        if (!is_built) build();
        return position[v];
    }

    // 位置から頂点を取得
    int get_vertex(int pos) {
        if (!is_built) build();
        for (int i = 0; i < n; i++) {
            if (position[i] == pos) return i;
        }
        return -1;
    }

    // 二点間の距離
    int distance(int u, int v) {
        if (!is_built) build();
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    // パス u-v 上のk番目の頂点（0-indexed）
    int kth_node_on_path(int u, int v, int k) {
        if (!is_built) build();

        int l = lca(u, v);
        int dist_u_lca = depth[u] - depth[l];
        int dist_v_lca = depth[v] - depth[l];

        if (k <= dist_u_lca) {
            // uからlca方向
            int cur = u;
            while (k > 0) {
                if (head[cur] == head[l] || depth[head[cur]] < depth[l]) {
                    // 同じchainまたはlcaを含むchain
                    int steps = min(k, depth[cur] - depth[l]);
                    for (int i = 0; i < steps; i++) {
                        cur = parent[cur];
                    }
                    k -= steps;
                } else {
                    // 別のchain
                    int steps = depth[cur] - depth[head[cur]] + 1;
                    if (k >= steps) {
                        cur = parent[head[cur]];
                        k -= steps;
                    } else {
                        for (int i = 0; i < k; i++) {
                            cur = parent[cur];
                        }
                        k = 0;
                    }
                }
            }
            return cur;
        } else {
            // vからlca方向
            k = dist_u_lca + dist_v_lca - k;
            int cur = v;
            while (k > 0) {
                if (head[cur] == head[l] || depth[head[cur]] < depth[l]) {
                    int steps = min(k, depth[cur] - depth[l]);
                    for (int i = 0; i < steps; i++) {
                        cur = parent[cur];
                    }
                    k -= steps;
                } else {
                    int steps = depth[cur] - depth[head[cur]] + 1;
                    if (k >= steps) {
                        cur = parent[head[cur]];
                        k -= steps;
                    } else {
                        for (int i = 0; i < k; i++) {
                            cur = parent[cur];
                        }
                        k = 0;
                    }
                }
            }
            return cur;
        }
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: HLDの基本操作" << endl;
    Graph tree1(10);

    // 木を構築
    //       0
    //      /|\
    //     1 2 3
    //    /| |  \
    //   4 5 6   7
    //       |   |
    //       8   9

    tree1.add_unweighted_undirected_edge(0, 1);
    tree1.add_unweighted_undirected_edge(0, 2);
    tree1.add_unweighted_undirected_edge(0, 3);
    tree1.add_unweighted_undirected_edge(1, 4);
    tree1.add_unweighted_undirected_edge(1, 5);
    tree1.add_unweighted_undirected_edge(2, 6);
    tree1.add_unweighted_undirected_edge(3, 7);
    tree1.add_unweighted_undirected_edge(6, 8);
    tree1.add_unweighted_undirected_edge(7, 9);

    HLD hld1(tree1, 0);

    cout << "各頂点の位置（DFS順序）:" << endl;
    for (int i = 0; i < tree1.n; i++) {
        cout << "頂点" << i << ": 位置" << hld1.get_position(i) << endl;
    }
    cout << endl;

    cout << "例2: LCAとパス" << endl;
    cout << "LCA(8, 9) = " << hld1.lca(8, 9) << endl;
    cout << "LCA(4, 5) = " << hld1.lca(4, 5) << endl;
    cout << "距離(8, 9) = " << hld1.distance(8, 9) << endl;
    cout << "距離(4, 9) = " << hld1.distance(4, 9) << endl;
    cout << endl;

    cout << "例3: パス 4-9 の分解" << endl;
    auto ranges = hld1.path_ranges(4, 9);
    cout << "パス 4-9 の区間数: " << ranges.size() << endl;
    for (int i = 0; i < ranges.size(); i++) {
        cout << "区間" << i << ": [" << ranges[i].first << ", " << ranges[i].second << "]" << endl;
    }
    cout << endl;

    cout << "例4: パス上のk番目の頂点" << endl;
    int u = 4, v = 9;
    int dist = hld1.distance(u, v);
    cout << "パス " << u << " -> " << v << " (距離" << dist << "):" << endl;
    for (int k = 0; k <= dist; k++) {
        int node = hld1.kth_node_on_path(u, v, k);
        cout << "  " << k << "番目: " << node << endl;
    }
    cout << endl;

    cout << "例5: 部分木の範囲" << endl;
    for (int v = 0; v < 4; v++) {
        auto [start, end] = hld1.subtree_range(v);
        cout << "頂点" << v << "の部分木範囲: [" << start << ", " << end << "]" << endl;
    }

    return 0;
}