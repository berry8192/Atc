// 重心分解 centroid_decomposition 木分解 分割統治

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

// ========== 重心分解ライブラリ ==========

struct CentroidDecomposition {
    Graph& g;
    int n;
    vector<bool> removed;
    vector<int> subtree_size;
    vector<int> centroid_parent;
    vector<vector<int>> centroid_children;
    vector<int> centroid_depth;
    bool is_built;

    CentroidDecomposition(Graph& graph) : g(graph), n(graph.n), is_built(false) {
        removed.assign(n, false);
        subtree_size.assign(n, 0);
        centroid_parent.assign(n, -1);
        centroid_children.assign(n);
        centroid_depth.assign(n, 0);
    }

    // 部分木のサイズを計算
    int calculate_size(int v, int parent) {
        subtree_size[v] = 1;
        for (int u : g.adj_unweighted[v]) {
            if (u != parent && !removed[u]) {
                subtree_size[v] += calculate_size(u, v);
            }
        }
        return subtree_size[v];
    }

    // 重心を見つける
    int find_centroid(int v, int parent, int tree_size) {
        for (int u : g.adj_unweighted[v]) {
            if (u != parent && !removed[u] && subtree_size[u] > tree_size / 2) {
                return find_centroid(u, v, tree_size);
            }
        }
        return v;
    }

    // 重心分解を実行
    int decompose(int v, int parent_centroid, int depth) {
        int tree_size = calculate_size(v, -1);
        int centroid = find_centroid(v, -1, tree_size);

        removed[centroid] = true;
        centroid_parent[centroid] = parent_centroid;
        centroid_depth[centroid] = depth;

        if (parent_centroid != -1) {
            centroid_children[parent_centroid].push_back(centroid);
        }

        for (int u : g.adj_unweighted[centroid]) {
            if (!removed[u]) {
                decompose(u, centroid, depth + 1);
            }
        }

        return centroid;
    }

    // 重心分解を構築
    int build() {
        fill(removed.begin(), removed.end(), false);
        int root = decompose(0, -1, 0);
        is_built = true;
        return root;
    }

    // 各頂点から指定した距離以下の頂点を取得
    void get_vertices_at_distance(int v, int max_dist, int current_dist, int parent, vector<pair<int, int>>& result) {
        if (current_dist > max_dist) return;
        result.push_back({v, current_dist});

        for (int u : g.adj_unweighted[v]) {
            if (u != parent && !removed[u]) {
                get_vertices_at_distance(u, max_dist, current_dist + 1, v, result);
            }
        }
    }

    // 指定した頂点から距離k以下の頂点の個数を数える
    int count_vertices_within_distance(int start, int k) {
        if (!is_built) build();

        int count = 0;
        function<void(int)> dfs = [&](int centroid) {
            // 現在の重心を中心とした距離計算
            vector<pair<int, int>> vertices_with_dist;
            get_vertices_at_distance(centroid, k, 0, -1, vertices_with_dist);

            for (auto [v, dist] : vertices_with_dist) {
                if (dist <= k) count++;
            }

            // 除外される部分（子の重心木）を処理
            for (int child : centroid_children[centroid]) {
                removed[child] = false;  // 一時的に復元
                vector<pair<int, int>> child_vertices;
                get_vertices_at_distance(child, k - 1, 0, -1, child_vertices);

                for (auto [v, dist] : child_vertices) {
                    if (dist + 1 <= k) count--;  // 重複を除去
                }

                removed[child] = true;  // 再び削除
                dfs(child);
            }
        };

        // 一時的にすべて復元
        fill(removed.begin(), removed.end(), false);
        dfs(0);  // root centroid から開始

        return count;
    }

    // 重心分解の深さを取得
    int get_centroid_depth(int v) {
        if (!is_built) build();
        return centroid_depth[v];
    }

    // 重心分解の親を取得
    int get_centroid_parent(int v) {
        if (!is_built) build();
        return centroid_parent[v];
    }

    // 重心分解の子を取得
    vector<int> get_centroid_children(int v) {
        if (!is_built) build();
        return centroid_children[v];
    }

    // パスの重心を通る経路数を計算（例：長さk以下のパス数）
    long long count_paths_through_centroid(int centroid, int k) {
        vector<vector<int>> subtree_counts(centroid_children[centroid].size());

        // 各子部分木での距離別頂点数を計算
        for (int i = 0; i < centroid_children[centroid].size(); i++) {
            int child = centroid_children[centroid][i];
            subtree_counts[i].resize(k + 1, 0);

            function<void(int, int, int)> count_in_subtree = [&](int v, int parent, int dist) {
                if (dist <= k) {
                    subtree_counts[i][dist]++;
                }
                for (int u : g.adj_unweighted[v]) {
                    if (u != parent && !removed[u] && dist + 1 <= k) {
                        count_in_subtree(u, v, dist + 1);
                    }
                }
            };

            removed[child] = false;
            count_in_subtree(child, centroid, 1);
            removed[child] = true;
        }

        long long result = 0;

        // 重心を通るパスの数を計算
        for (int len = 0; len <= k; len++) {
            // 長さlenのパス
            for (int i = 0; i < subtree_counts.size(); i++) {
                for (int j = i + 1; j < subtree_counts.size(); j++) {
                    for (int d1 = 0; d1 <= len; d1++) {
                        int d2 = len - d1;
                        if (d2 >= 0 && d2 < subtree_counts[j].size()) {
                            result += (long long)subtree_counts[i][d1] * subtree_counts[j][d2];
                        }
                    }
                }
            }
        }

        return result;
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: 基本的な重心分解" << endl;
    Graph tree1(8);

    //     0
    //    /|\
    //   1 2 3
    //  /| |  \
    // 4 5 6   7

    tree1.add_unweighted_undirected_edge(0, 1);
    tree1.add_unweighted_undirected_edge(0, 2);
    tree1.add_unweighted_undirected_edge(0, 3);
    tree1.add_unweighted_undirected_edge(1, 4);
    tree1.add_unweighted_undirected_edge(1, 5);
    tree1.add_unweighted_undirected_edge(2, 6);
    tree1.add_unweighted_undirected_edge(3, 7);

    CentroidDecomposition cd1(tree1);
    int root_centroid = cd1.build();

    cout << "根重心: " << root_centroid << endl;
    cout << "各頂点の重心分解での深さ:" << endl;
    for (int i = 0; i < tree1.n; i++) {
        cout << "頂点" << i << ": 深さ" << cd1.get_centroid_depth(i);
        int parent = cd1.get_centroid_parent(i);
        if (parent != -1) {
            cout << " (親: " << parent << ")";
        }
        cout << endl;
    }
    cout << endl;

    cout << "例2: 重心分解の構造" << endl;
    function<void(int, int)> print_centroid_tree = [&](int v, int depth) {
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << "重心" << v << endl;

        for (int child : cd1.get_centroid_children(v)) {
            print_centroid_tree(child, depth + 1);
        }
    };

    cout << "重心分解木の構造:" << endl;
    print_centroid_tree(root_centroid, 0);
    cout << endl;

    cout << "例3: 線形の木での重心分解" << endl;
    Graph tree2(7);
    // 0-1-2-3-4-5-6 の一直線
    for (int i = 0; i < 6; i++) {
        tree2.add_unweighted_undirected_edge(i, i + 1);
    }

    CentroidDecomposition cd2(tree2);
    int root2 = cd2.build();

    cout << "線形木の根重心: " << root2 << endl;
    cout << "各頂点の重心分解での深さ:" << endl;
    for (int i = 0; i < tree2.n; i++) {
        cout << "頂点" << i << ": 深さ" << cd2.get_centroid_depth(i) << endl;
    }
    cout << endl;

    cout << "例4: 完全二分木での重心分解" << endl;
    Graph tree3(7);
    //       0
    //      / \
    //     1   2
    //    /|   |\
    //   3 4   5 6

    tree3.add_unweighted_undirected_edge(0, 1);
    tree3.add_unweighted_undirected_edge(0, 2);
    tree3.add_unweighted_undirected_edge(1, 3);
    tree3.add_unweighted_undirected_edge(1, 4);
    tree3.add_unweighted_undirected_edge(2, 5);
    tree3.add_unweighted_undirected_edge(2, 6);

    CentroidDecomposition cd3(tree3);
    int root3 = cd3.build();

    cout << "完全二分木の根重心: " << root3 << endl;
    cout << "重心分解の最大深さ: " << *max_element(cd3.centroid_depth.begin(), cd3.centroid_depth.end()) << endl;

    return 0;
}