// グラフ彩色 graph_coloring 二部グラフ判定 k彩色 greedy

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
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

// ========== グラフ彩色ライブラリ ==========

struct GraphColoring {
    Graph& g;
    int n;
    vector<int> color;
    int num_colors;

    GraphColoring(Graph& graph) : g(graph), n(graph.n), color(graph.n, -1), num_colors(0) {}

    // 二部グラフ判定とBFS彩色
    bool is_bipartite() {
        fill(color.begin(), color.end(), -1);

        for (int start = 0; start < n; start++) {
            if (color[start] != -1) continue;

            queue<int> q;
            q.push(start);
            color[start] = 0;

            while (!q.empty()) {
                int v = q.front();
                q.pop();

                for (int u : g.adj_unweighted[v]) {
                    if (color[u] == -1) {
                        color[u] = 1 - color[v];
                        q.push(u);
                    } else if (color[u] == color[v]) {
                        return false;  // 隣接する頂点が同じ色
                    }
                }
            }
        }

        num_colors = 2;
        return true;
    }

    // Greedy彩色アルゴリズム
    int greedy_coloring() {
        fill(color.begin(), color.end(), -1);
        num_colors = 0;

        for (int v = 0; v < n; v++) {
            // 隣接頂点で使われている色を調べる
            vector<bool> used_colors(n, false);
            for (int u : g.adj_unweighted[v]) {
                if (color[u] != -1) {
                    used_colors[color[u]] = true;
                }
            }

            // 最小の未使用色を割り当て
            for (int c = 0; c < n; c++) {
                if (!used_colors[c]) {
                    color[v] = c;
                    num_colors = max(num_colors, c + 1);
                    break;
                }
            }
        }

        return num_colors;
    }

    // Welsh-Powell アルゴリズム（次数順ソート後のGreedy）
    int welsh_powell_coloring() {
        fill(color.begin(), color.end(), -1);
        num_colors = 0;

        // 次数の高い順でソート
        vector<pair<int, int>> degree_vertex;
        for (int i = 0; i < n; i++) {
            degree_vertex.push_back({g.adj_unweighted[i].size(), i});
        }
        sort(degree_vertex.rbegin(), degree_vertex.rend());

        for (auto [degree, v] : degree_vertex) {
            vector<bool> used_colors(n, false);
            for (int u : g.adj_unweighted[v]) {
                if (color[u] != -1) {
                    used_colors[color[u]] = true;
                }
            }

            for (int c = 0; c < n; c++) {
                if (!used_colors[c]) {
                    color[v] = c;
                    num_colors = max(num_colors, c + 1);
                    break;
                }
            }
        }

        return num_colors;
    }

    // k彩色が可能かチェック（バックトラッキング）
    bool can_k_color(int k) {
        fill(color.begin(), color.end(), -1);

        function<bool(int)> backtrack = [&](int v) -> bool {
            if (v == n) return true;

            for (int c = 0; c < k; c++) {
                bool valid = true;
                for (int u : g.adj_unweighted[v]) {
                    if (color[u] == c) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    color[v] = c;
                    if (backtrack(v + 1)) return true;
                    color[v] = -1;
                }
            }

            return false;
        };

        return backtrack(0);
    }

    // 彩色数の下界（最大クリークサイズ）
    int chromatic_lower_bound() {
        int max_clique_size = 1;

        // 全ての頂点について、その頂点を含む最大クリークのサイズを推定
        for (int start = 0; start < n; start++) {
            vector<bool> candidates(n, false);
            candidates[start] = true;

            for (int v : g.adj_unweighted[start]) {
                candidates[v] = true;
            }

            vector<int> clique = {start};

            function<void(int)> find_clique = [&](int pos) {
                if (pos == n) return;

                if (candidates[pos]) {
                    bool can_add = true;
                    for (int u : clique) {
                        bool connected = false;
                        for (int neighbor : g.adj_unweighted[pos]) {
                            if (neighbor == u) {
                                connected = true;
                                break;
                            }
                        }
                        if (!connected) {
                            can_add = false;
                            break;
                        }
                    }

                    if (can_add) {
                        clique.push_back(pos);
                        max_clique_size = max(max_clique_size, (int)clique.size());
                        find_clique(pos + 1);
                        clique.pop_back();
                    }
                }

                find_clique(pos + 1);
            };

            find_clique(start + 1);
        }

        return max_clique_size;
    }

    // 現在の彩色が有効かチェック
    bool is_valid_coloring() {
        for (int v = 0; v < n; v++) {
            if (color[v] == -1) return false;

            for (int u : g.adj_unweighted[v]) {
                if (color[v] == color[u]) return false;
            }
        }
        return true;
    }

    // 彩色結果を取得
    vector<int> get_coloring() {
        return color;
    }

    // 使用色数を取得
    int get_num_colors() {
        return num_colors;
    }

    // 各色の頂点集合を取得
    vector<vector<int>> get_color_classes() {
        vector<vector<int>> classes(num_colors);
        for (int i = 0; i < n; i++) {
            if (color[i] != -1) {
                classes[color[i]].push_back(i);
            }
        }
        return classes;
    }

    // グラフの最大次数を取得（彩色数の上界）
    int max_degree() {
        int max_deg = 0;
        for (int i = 0; i < n; i++) {
            max_deg = max(max_deg, (int)g.adj_unweighted[i].size());
        }
        return max_deg;
    }

    // Brooks' 定理の判定（最大次数Δに対して、クリークでも奇サイクルでもなければΔ彩色可能）
    bool is_brooks_applicable() {
        int delta = max_degree();

        // 完全グラフかチェック
        bool is_complete = true;
        for (int i = 0; i < n && is_complete; i++) {
            if ((int)g.adj_unweighted[i].size() != n - 1) {
                is_complete = false;
            }
        }

        if (is_complete) return false;  // 完全グラフなのでBrooks定理は適用不可

        // 奇サイクルかチェック（n >= 3の場合）
        if (n >= 3) {
            bool is_cycle = true;
            for (int i = 0; i < n; i++) {
                if ((int)g.adj_unweighted[i].size() != 2) {
                    is_cycle = false;
                    break;
                }
            }
            if (is_cycle && n % 2 == 1) return false;  // 奇サイクルなのでBrooks定理は適用不可
        }

        return true;
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: 二部グラフの判定" << endl;
    Graph bipartite_g(6);
    bipartite_g.add_unweighted_undirected_edge(0, 3);
    bipartite_g.add_unweighted_undirected_edge(0, 4);
    bipartite_g.add_unweighted_undirected_edge(1, 3);
    bipartite_g.add_unweighted_undirected_edge(1, 5);
    bipartite_g.add_unweighted_undirected_edge(2, 4);
    bipartite_g.add_unweighted_undirected_edge(2, 5);

    GraphColoring gc1(bipartite_g);
    if (gc1.is_bipartite()) {
        cout << "二部グラフです（2彩色可能）" << endl;
        auto coloring = gc1.get_coloring();
        cout << "彩色: ";
        for (int i = 0; i < bipartite_g.n; i++) {
            cout << "頂点" << i << ":色" << coloring[i] << " ";
        }
        cout << endl;
    } else {
        cout << "二部グラフではありません" << endl;
    }
    cout << endl;

    cout << "例2: Greedy彩色" << endl;
    Graph triangle_g(4);
    triangle_g.add_unweighted_undirected_edge(0, 1);
    triangle_g.add_unweighted_undirected_edge(1, 2);
    triangle_g.add_unweighted_undirected_edge(2, 0);  // 三角形
    triangle_g.add_unweighted_undirected_edge(0, 3);

    GraphColoring gc2(triangle_g);
    int greedy_colors = gc2.greedy_coloring();
    cout << "Greedy彩色の色数: " << greedy_colors << endl;

    int welsh_powell_colors = gc2.welsh_powell_coloring();
    cout << "Welsh-Powell彩色の色数: " << welsh_powell_colors << endl;

    auto coloring2 = gc2.get_coloring();
    cout << "彩色結果: ";
    for (int i = 0; i < triangle_g.n; i++) {
        cout << "頂点" << i << ":色" << coloring2[i] << " ";
    }
    cout << endl;
    cout << endl;

    cout << "例3: k彩色の判定" << endl;
    for (int k = 1; k <= 4; k++) {
        bool can_color = gc2.can_k_color(k);
        cout << k << "彩色: " << (can_color ? "可能" : "不可能") << endl;
    }
    cout << endl;

    cout << "例4: 彩色数の境界" << endl;
    int lower_bound = gc2.chromatic_lower_bound();
    int upper_bound = gc2.max_degree() + 1;
    cout << "彩色数の下界（最大クリーク）: " << lower_bound << endl;
    cout << "彩色数の上界（最大次数+1）: " << upper_bound << endl;
    cout << "Brooks定理適用可能: " << (gc2.is_brooks_applicable() ? "はい" : "いいえ") << endl;
    if (gc2.is_brooks_applicable()) {
        cout << "Brooks定理により最大次数彩色可能: " << gc2.max_degree() << "色" << endl;
    }
    cout << endl;

    cout << "例5: 完全グラフK4" << endl;
    Graph complete_g(4);
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            complete_g.add_unweighted_undirected_edge(i, j);
        }
    }

    GraphColoring gc3(complete_g);
    cout << "K4は二部グラフか: " << (gc3.is_bipartite() ? "はい" : "いいえ") << endl;

    int complete_colors = gc3.greedy_coloring();
    cout << "K4のGreedy彩色数: " << complete_colors << endl;
    cout << "K4のBrooks定理適用可能: " << (gc3.is_brooks_applicable() ? "はい" : "いいえ") << endl;

    auto color_classes = gc3.get_color_classes();
    cout << "各色クラス:" << endl;
    for (int i = 0; i < color_classes.size(); i++) {
        cout << "色" << i << ": ";
        for (int v : color_classes[i]) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}