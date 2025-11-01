// 強連結成分 scc strongly_connected_components コサラジュ法

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

// ========== 強連結成分ライブラリ ==========

struct SCC {
    Graph& g;
    vector<vector<int>> components;  // 各強連結成分の頂点リスト
    vector<int> comp_id;  // 各頂点の属する強連結成分ID
    vector<vector<int>> reverse_graph;  // 逆グラフ
    vector<bool> visited;
    vector<int> finish_order;  // DFS完了順序
    bool is_built;

    SCC(Graph& graph) : g(graph), comp_id(graph.n), reverse_graph(graph.n), visited(graph.n), is_built(false) {}

    // 逆グラフを構築
    void build_reverse_graph() {
        for (int v = 0; v < g.n; v++) {
            for (int u : g.adj_unweighted[v]) {
                reverse_graph[u].push_back(v);
            }
        }
    }

    // 最初のDFS（完了時刻順序を記録）
    void dfs1(int v) {
        visited[v] = true;
        for (int u : g.adj_unweighted[v]) {
            if (!visited[u]) {
                dfs1(u);
            }
        }
        finish_order.push_back(v);
    }

    // 二回目のDFS（逆グラフで強連結成分を見つける）
    void dfs2(int v, vector<int>& component) {
        visited[v] = true;
        component.push_back(v);
        for (int u : reverse_graph[v]) {
            if (!visited[u]) {
                dfs2(u, component);
            }
        }
    }

    // 強連結成分を構築
    void build() {
        components.clear();
        finish_order.clear();
        fill(visited.begin(), visited.end(), false);
        fill(comp_id.begin(), comp_id.end(), -1);

        build_reverse_graph();

        // 最初のDFS：完了時刻順序を記録
        for (int v = 0; v < g.n; v++) {
            if (!visited[v]) {
                dfs1(v);
            }
        }

        // 二回目のDFS：逆グラフで強連結成分を見つける
        fill(visited.begin(), visited.end(), false);
        reverse(finish_order.begin(), finish_order.end());

        for (int v : finish_order) {
            if (!visited[v]) {
                vector<int> component;
                dfs2(v, component);

                // 強連結成分IDを設定
                int comp_idx = components.size();
                for (int u : component) {
                    comp_id[u] = comp_idx;
                }

                components.push_back(component);
            }
        }

        is_built = true;
    }

    // 強連結成分数を取得
    int get_component_count() {
        if (!is_built) build();
        return components.size();
    }

    // 指定した頂点の強連結成分IDを取得
    int get_component_id(int v) {
        if (!is_built) build();
        return comp_id[v];
    }

    // 強連結成分のリストを取得
    vector<vector<int>> get_components() {
        if (!is_built) build();
        return components;
    }

    // 二つの頂点が同じ強連結成分に属するかチェック
    bool same_component(int u, int v) {
        if (!is_built) build();
        return comp_id[u] == comp_id[v];
    }

    // 縮約グラフ（DAG）を構築
    vector<vector<int>> build_condensation_graph() {
        if (!is_built) build();

        int comp_count = components.size();
        vector<vector<int>> condensed(comp_count);
        vector<vector<bool>> added(comp_count, vector<bool>(comp_count, false));

        for (int v = 0; v < g.n; v++) {
            for (int u : g.adj_unweighted[v]) {
                int comp_v = comp_id[v];
                int comp_u = comp_id[u];
                if (comp_v != comp_u && !added[comp_v][comp_u]) {
                    condensed[comp_v].push_back(comp_u);
                    added[comp_v][comp_u] = true;
                }
            }
        }

        return condensed;
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: 基本的な強連結成分" << endl;
    Graph g1(7);
    g1.add_unweighted_edge(0, 1);
    g1.add_unweighted_edge(1, 2);
    g1.add_unweighted_edge(2, 0);
    g1.add_unweighted_edge(1, 3);
    g1.add_unweighted_edge(3, 4);
    g1.add_unweighted_edge(4, 5);
    g1.add_unweighted_edge(5, 3);
    g1.add_unweighted_edge(4, 6);

    SCC scc1(g1);
    scc1.build();

    cout << "強連結成分数: " << scc1.get_component_count() << endl;
    auto components = scc1.get_components();
    for (int i = 0; i < components.size(); i++) {
        cout << "成分 " << i << ": ";
        for (int v : components[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "例2: 各頂点の所属成分" << endl;
    for (int v = 0; v < g1.n; v++) {
        cout << "頂点 " << v << " -> 成分 " << scc1.get_component_id(v) << endl;
    }
    cout << endl;

    cout << "例3: 縮約グラフ（DAG）" << endl;
    auto condensed = scc1.build_condensation_graph();
    for (int i = 0; i < condensed.size(); i++) {
        cout << "成分 " << i << " -> ";
        for (int j : condensed[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "例4: 単純な循環グラフ" << endl;
    Graph g2(4);
    g2.add_unweighted_edge(0, 1);
    g2.add_unweighted_edge(1, 2);
    g2.add_unweighted_edge(2, 3);
    g2.add_unweighted_edge(3, 0);

    SCC scc2(g2);
    cout << "強連結成分数: " << scc2.get_component_count() << endl;
    cout << "頂点0と頂点2は同じ成分か: " << (scc2.same_component(0, 2) ? "はい" : "いいえ") << endl;

    return 0;
}