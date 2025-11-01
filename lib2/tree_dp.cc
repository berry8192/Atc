// 木DP tree_dp 動的計画法 rerooting 全方位木

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
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

// ========== 木DPライブラリ ==========

struct TreeDP {
    Graph& g;
    int n;

    TreeDP(Graph& graph) : g(graph), n(graph.n) {}

    // 基本的な木DP：部分木のサイズを計算
    vector<int> subtree_size() {
        vector<int> size(n, 1);

        function<void(int, int)> dfs = [&](int v, int parent) {
            for (int u : g.adj_unweighted[v]) {
                if (u != parent) {
                    dfs(u, v);
                    size[v] += size[u];
                }
            }
        };

        dfs(0, -1);
        return size;
    }

    // 各頂点を根とした場合の木の高さ（直径計算に使用）
    vector<int> tree_height_from_each_root() {
        vector<int> heights(n);

        for (int root = 0; root < n; root++) {
            function<int(int, int)> dfs = [&](int v, int parent) -> int {
                int max_depth = 0;
                for (int u : g.adj_unweighted[v]) {
                    if (u != parent) {
                        max_depth = max(max_depth, dfs(u, v) + 1);
                    }
                }
                return max_depth;
            };

            heights[root] = dfs(root, -1);
        }

        return heights;
    }

    // 各頂点から最も遠い頂点までの距離（全方位木DP）
    vector<int> max_distance_from_each_vertex() {
        vector<int> max_dist(n, 0);

        // 最初に任意の頂点（0）から最も遠い頂点を見つける
        auto [farthest1, dist1] = find_farthest_vertex(0);

        // その頂点から最も遠い頂点を見つける（これが直径の端点）
        auto [farthest2, diameter] = find_farthest_vertex(farthest1);

        // 直径の両端点から各頂点への距離を計算
        vector<int> dist_from_end1 = distances_from_vertex(farthest1);
        vector<int> dist_from_end2 = distances_from_vertex(farthest2);

        for (int i = 0; i < n; i++) {
            max_dist[i] = max(dist_from_end1[i], dist_from_end2[i]);
        }

        return max_dist;
    }

    // 指定した頂点から最も遠い頂点とその距離を取得
    pair<int, int> find_farthest_vertex(int start) {
        vector<int> dist(n, -1);
        int farthest = start;
        int max_dist = 0;

        function<void(int, int)> dfs = [&](int v, int d) {
            dist[v] = d;
            if (d > max_dist) {
                max_dist = d;
                farthest = v;
            }

            for (int u : g.adj_unweighted[v]) {
                if (dist[u] == -1) {
                    dfs(u, d + 1);
                }
            }
        };

        dfs(start, 0);
        return {farthest, max_dist};
    }

    // 指定した頂点から全頂点への距離
    vector<int> distances_from_vertex(int start) {
        vector<int> dist(n, -1);

        function<void(int, int)> dfs = [&](int v, int d) {
            dist[v] = d;
            for (int u : g.adj_unweighted[v]) {
                if (dist[u] == -1) {
                    dfs(u, d + 1);
                }
            }
        };

        dfs(start, 0);
        return dist;
    }

    // 全方位木DP：各頂点を根とした場合の部分木の最大値
    template<typename T>
    vector<T> rerooting_dp(
        T identity,
        function<T(T, T)> merge,
        function<T(T, int, int)> add_root
    ) {
        vector<T> dp_down(n, identity);  // 下向きDP
        vector<T> dp_up(n, identity);    // 上向きDP
        vector<T> result(n);

        // 下向きDP
        function<void(int, int)> dfs1 = [&](int v, int parent) {
            for (int u : g.adj_unweighted[v]) {
                if (u != parent) {
                    dfs1(u, v);
                    dp_down[v] = merge(dp_down[v], add_root(dp_down[u], u, v));
                }
            }
        };

        // 上向きDP
        function<void(int, int)> dfs2 = [&](int v, int parent) {
            vector<T> child_values;
            vector<int> children;

            for (int u : g.adj_unweighted[v]) {
                if (u != parent) {
                    children.push_back(u);
                    child_values.push_back(add_root(dp_down[u], u, v));
                }
            }

            // 各子に対して、その子を除いた値を計算
            for (int i = 0; i < children.size(); i++) {
                T value = dp_up[v];
                for (int j = 0; j < child_values.size(); j++) {
                    if (i != j) {
                        value = merge(value, child_values[j]);
                    }
                }
                dp_up[children[i]] = add_root(value, v, children[i]);
                dfs2(children[i], v);
            }
        };

        dfs1(0, -1);
        dfs2(0, -1);

        // 結果を計算
        for (int v = 0; v < n; v++) {
            result[v] = merge(dp_down[v], dp_up[v]);
        }

        return result;
    }

    // 重み付き木での最遠点距離（全方位）
    vector<long long> max_weighted_distance_from_each_vertex() {
        return rerooting_dp<long long>(
            0LL,  // identity
            [](long long a, long long b) { return max(a, b); },  // merge
            [&](long long child_val, int child, int parent) -> long long {
                // 親から子への辺の重みを加算
                for (auto& e : g.adj[parent]) {
                    if (e.to == child) {
                        return child_val + e.cost;
                    }
                }
                return child_val + 1;  // 重みなしの場合
            }
        );
    }

    // 各頂点を根とした場合の部分木内の頂点数（全方位）
    vector<int> subtree_sizes_rerooting() {
        return rerooting_dp<int>(
            1,  // identity (自分自身)
            [](int a, int b) { return a + b; },  // merge
            [](int child_size, int child, int parent) { return child_size; }  // add_root
        );
    }

    // 木の直径とその端点を取得
    tuple<int, int, int> tree_diameter() {
        auto [end1, dist1] = find_farthest_vertex(0);
        auto [end2, diameter] = find_farthest_vertex(end1);
        return {end1, end2, diameter};
    }

    // 木の重心を取得
    vector<int> find_centroids() {
        vector<int> size = subtree_size();
        vector<int> centroids;

        function<void(int, int)> dfs = [&](int v, int parent) {
            bool is_centroid = true;
            for (int u : g.adj_unweighted[v]) {
                if (u != parent) {
                    dfs(u, v);
                    if (size[u] > n / 2) {
                        is_centroid = false;
                    }
                }
            }
            if (n - size[v] > n / 2) {
                is_centroid = false;
            }
            if (is_centroid) {
                centroids.push_back(v);
            }
        };

        dfs(0, -1);
        return centroids;
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: 基本的な木DP" << endl;
    Graph tree1(7);

    tree1.add_unweighted_undirected_edge(0, 1);
    tree1.add_unweighted_undirected_edge(0, 2);
    tree1.add_unweighted_undirected_edge(1, 3);
    tree1.add_unweighted_undirected_edge(1, 4);
    tree1.add_unweighted_undirected_edge(2, 5);
    tree1.add_unweighted_undirected_edge(2, 6);

    TreeDP dp1(tree1);

    auto sizes = dp1.subtree_size();
    cout << "各頂点の部分木のサイズ:" << endl;
    for (int i = 0; i < tree1.n; i++) {
        cout << "頂点" << i << ": " << sizes[i] << endl;
    }
    cout << endl;

    cout << "例2: 木の直径" << endl;
    auto [end1, end2, diameter] = dp1.tree_diameter();
    cout << "直径: " << diameter << " (端点: " << end1 << " - " << end2 << ")" << endl;
    cout << endl;

    cout << "例3: 各頂点からの最大距離" << endl;
    auto max_dists = dp1.max_distance_from_each_vertex();
    for (int i = 0; i < tree1.n; i++) {
        cout << "頂点" << i << "からの最大距離: " << max_dists[i] << endl;
    }
    cout << endl;

    cout << "例4: 木の重心" << endl;
    auto centroids = dp1.find_centroids();
    cout << "重心: ";
    for (int c : centroids) {
        cout << c << " ";
    }
    cout << endl << endl;

    cout << "例5: 重み付き木での最遠点距離" << endl;
    Graph weighted_tree(5);
    weighted_tree.add_undirected_edge(0, 1, 3);
    weighted_tree.add_undirected_edge(1, 2, 2);
    weighted_tree.add_undirected_edge(1, 3, 4);
    weighted_tree.add_undirected_edge(2, 4, 1);

    TreeDP dp2(weighted_tree);
    auto weighted_max_dists = dp2.max_weighted_distance_from_each_vertex();
    cout << "重み付き木での各頂点からの最大距離:" << endl;
    for (int i = 0; i < weighted_tree.n; i++) {
        cout << "頂点" << i << ": " << weighted_max_dists[i] << endl;
    }
    cout << endl;

    cout << "例6: 全方位木DPでの部分木サイズ" << endl;
    auto rerooting_sizes = dp2.subtree_sizes_rerooting();
    cout << "各頂点を根とした場合の部分木サイズ（全体）:" << endl;
    for (int i = 0; i < weighted_tree.n; i++) {
        cout << "頂点" << i << "を根: " << rerooting_sizes[i] << endl;
    }

    return 0;
}