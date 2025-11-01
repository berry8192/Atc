// 橋・関節点 bridge_articulation 連結成分 tarjan

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

// ========== 橋・関節点ライブラリ ==========

struct BridgeArticulation {
    Graph& g;
    int n, timer;
    vector<int> disc, low, parent;
    vector<bool> visited, is_articulation;
    vector<pair<int, int>> bridges;
    vector<int> articulation_points;
    bool is_built;

    BridgeArticulation(Graph& graph) : g(graph), n(graph.n), timer(0), is_built(false) {
        disc.assign(n, -1);
        low.assign(n, -1);
        parent.assign(n, -1);
        visited.assign(n, false);
        is_articulation.assign(n, false);
    }

    // Tarjanのアルゴリズムで橋と関節点を見つける
    void tarjan_dfs(int u) {
        int children = 0;
        visited[u] = true;
        disc[u] = low[u] = timer++;

        for (int v : g.adj_unweighted[u]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                tarjan_dfs(v);

                // uからvへの辺が橋かチェック
                if (low[v] > disc[u]) {
                    bridges.push_back({min(u, v), max(u, v)});
                }

                // uが関節点かチェック
                if ((parent[u] == -1 && children > 1) ||
                    (parent[u] != -1 && low[v] >= disc[u])) {
                    is_articulation[u] = true;
                }

                low[u] = min(low[u], low[v]);
            }
            else if (v != parent[u]) {
                // Back edge
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    // 橋と関節点を構築
    void build() {
        bridges.clear();
        articulation_points.clear();
        timer = 0;
        fill(disc.begin(), disc.end(), -1);
        fill(low.begin(), low.end(), -1);
        fill(parent.begin(), parent.end(), -1);
        fill(visited.begin(), visited.end(), false);
        fill(is_articulation.begin(), is_articulation.end(), false);

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                tarjan_dfs(i);
            }
        }

        // 関節点のリストを作成
        for (int i = 0; i < n; i++) {
            if (is_articulation[i]) {
                articulation_points.push_back(i);
            }
        }

        // 橋をソート
        sort(bridges.begin(), bridges.end());

        is_built = true;
    }

    // 橋のリストを取得
    vector<pair<int, int>> get_bridges() {
        if (!is_built) build();
        return bridges;
    }

    // 関節点のリストを取得
    vector<int> get_articulation_points() {
        if (!is_built) build();
        return articulation_points;
    }

    // 指定した辺が橋かどうかチェック
    bool is_bridge(int u, int v) {
        if (!is_built) build();
        pair<int, int> edge = {min(u, v), max(u, v)};
        return binary_search(bridges.begin(), bridges.end(), edge);
    }

    // 指定した頂点が関節点かどうかチェック
    bool is_articulation_point(int v) {
        if (!is_built) build();
        return is_articulation[v];
    }

    // 橋を除いたグラフの連結成分数
    int connected_components_without_bridges() {
        if (!is_built) build();

        vector<bool> visited_comp(n, false);
        int components = 0;

        // 橋の集合を作成
        set<pair<int, int>> bridge_set;
        for (auto& bridge : bridges) {
            bridge_set.insert(bridge);
        }

        function<void(int)> dfs = [&](int v) {
            visited_comp[v] = true;
            for (int u : g.adj_unweighted[v]) {
                if (!visited_comp[u]) {
                    pair<int, int> edge = {min(v, u), max(v, u)};
                    if (bridge_set.find(edge) == bridge_set.end()) {
                        dfs(u);
                    }
                }
            }
        };

        for (int i = 0; i < n; i++) {
            if (!visited_comp[i]) {
                dfs(i);
                components++;
            }
        }

        return components;
    }

    // 関節点を除いたグラフの連結成分数
    int connected_components_without_articulation(int removed_vertex) {
        if (!is_built) build();

        vector<bool> visited_comp(n, false);
        visited_comp[removed_vertex] = true;  // 指定した頂点を除去
        int components = 0;

        function<void(int)> dfs = [&](int v) {
            visited_comp[v] = true;
            for (int u : g.adj_unweighted[v]) {
                if (!visited_comp[u]) {
                    dfs(u);
                }
            }
        };

        for (int i = 0; i < n; i++) {
            if (!visited_comp[i]) {
                dfs(i);
                components++;
            }
        }

        return components;
    }

    // 2-edge-connected componentsを取得
    vector<vector<int>> get_2edge_connected_components() {
        if (!is_built) build();

        vector<bool> visited_comp(n, false);
        vector<vector<int>> components;

        // 橋の集合を作成
        set<pair<int, int>> bridge_set;
        for (auto& bridge : bridges) {
            bridge_set.insert(bridge);
        }

        function<void(int, vector<int>&)> dfs = [&](int v, vector<int>& component) {
            visited_comp[v] = true;
            component.push_back(v);
            for (int u : g.adj_unweighted[v]) {
                if (!visited_comp[u]) {
                    pair<int, int> edge = {min(v, u), max(v, u)};
                    if (bridge_set.find(edge) == bridge_set.end()) {
                        dfs(u, component);
                    }
                }
            }
        };

        for (int i = 0; i < n; i++) {
            if (!visited_comp[i]) {
                vector<int> component;
                dfs(i, component);
                components.push_back(component);
            }
        }

        return components;
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: 基本的な橋と関節点" << endl;
    Graph g1(7);

    // グラフ構築
    //   0---1---2
    //   |   |   |
    //   3---4   5
    //       |
    //       6

    g1.add_unweighted_undirected_edge(0, 1);
    g1.add_unweighted_undirected_edge(1, 2);
    g1.add_unweighted_undirected_edge(0, 3);
    g1.add_unweighted_undirected_edge(1, 4);
    g1.add_unweighted_undirected_edge(3, 4);
    g1.add_unweighted_undirected_edge(2, 5);
    g1.add_unweighted_undirected_edge(4, 6);

    BridgeArticulation ba1(g1);

    auto bridges = ba1.get_bridges();
    cout << "橋: ";
    for (auto [u, v] : bridges) {
        cout << "(" << u << "-" << v << ") ";
    }
    cout << endl;

    auto articulation_points = ba1.get_articulation_points();
    cout << "関節点: ";
    for (int v : articulation_points) {
        cout << v << " ";
    }
    cout << endl << endl;

    cout << "例2: 橋・関節点の判定" << endl;
    cout << "辺(1-2)は橋か: " << (ba1.is_bridge(1, 2) ? "はい" : "いいえ") << endl;
    cout << "辺(0-1)は橋か: " << (ba1.is_bridge(0, 1) ? "はい" : "いいえ") << endl;
    cout << "頂点1は関節点か: " << (ba1.is_articulation_point(1) ? "はい" : "いいえ") << endl;
    cout << "頂点3は関節点か: " << (ba1.is_articulation_point(3) ? "はい" : "いいえ") << endl;
    cout << endl;

    cout << "例3: 2-edge-connected components" << endl;
    auto components = ba1.get_2edge_connected_components();
    cout << "2-edge-connected成分数: " << components.size() << endl;
    for (int i = 0; i < components.size(); i++) {
        cout << "成分" << i << ": ";
        for (int v : components[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "例4: 単純な環" << endl;
    Graph g2(4);
    g2.add_unweighted_undirected_edge(0, 1);
    g2.add_unweighted_undirected_edge(1, 2);
    g2.add_unweighted_undirected_edge(2, 3);
    g2.add_unweighted_undirected_edge(3, 0);

    BridgeArticulation ba2(g2);
    cout << "環グラフの橋数: " << ba2.get_bridges().size() << endl;
    cout << "環グラフの関節点数: " << ba2.get_articulation_points().size() << endl;
    cout << endl;

    cout << "例5: 木構造" << endl;
    Graph g3(5);
    g3.add_unweighted_undirected_edge(0, 1);
    g3.add_unweighted_undirected_edge(1, 2);
    g3.add_unweighted_undirected_edge(1, 3);
    g3.add_unweighted_undirected_edge(3, 4);

    BridgeArticulation ba3(g3);
    cout << "木の橋数: " << ba3.get_bridges().size() << " (辺数と同じ)" << endl;
    cout << "木の関節点: ";
    for (int v : ba3.get_articulation_points()) {
        cout << v << " ";
    }
    cout << endl;

    cout << "関節点1を除去した場合の連結成分数: " << ba3.connected_components_without_articulation(1) << endl;

    return 0;
}