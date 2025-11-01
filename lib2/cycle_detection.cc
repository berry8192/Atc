// サイクル検出 cycle_detection DFS 閉路 有向グラフ 無向グラフ

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

// ========== サイクル検出ライブラリ ==========

struct CycleDetection {
    Graph& g;
    int n;
    vector<int> state;  // 0: 未訪問, 1: 訪問中, 2: 完了
    vector<int> parent;
    vector<int> cycle_path;
    bool has_cycle;

    CycleDetection(Graph& graph) : g(graph), n(graph.n), state(graph.n), parent(graph.n), has_cycle(false) {}

    // 有向グラフのサイクル検出（DFS）
    bool detect_directed_cycle() {
        fill(state.begin(), state.end(), 0);
        fill(parent.begin(), parent.end(), -1);
        cycle_path.clear();
        has_cycle = false;

        function<bool(int)> dfs = [&](int v) -> bool {
            state[v] = 1;  // 訪問中

            for (int u : g.adj_unweighted[v]) {
                if (state[u] == 1) {
                    // Back edge: サイクル発見
                    cycle_path.clear();
                    int curr = v;
                    while (curr != u) {
                        cycle_path.push_back(curr);
                        curr = parent[curr];
                    }
                    cycle_path.push_back(u);
                    reverse(cycle_path.begin(), cycle_path.end());
                    return true;
                }
                if (state[u] == 0) {
                    parent[u] = v;
                    if (dfs(u)) return true;
                }
            }

            state[v] = 2;  // 完了
            return false;
        };

        for (int i = 0; i < n; i++) {
            if (state[i] == 0) {
                if (dfs(i)) {
                    has_cycle = true;
                    return true;
                }
            }
        }

        return false;
    }

    // 無向グラフのサイクル検出（DFS）
    bool detect_undirected_cycle() {
        vector<bool> visited(n, false);
        fill(parent.begin(), parent.end(), -1);
        cycle_path.clear();
        has_cycle = false;

        function<bool(int, int)> dfs = [&](int v, int p) -> bool {
            visited[v] = true;
            parent[v] = p;

            for (int u : g.adj_unweighted[v]) {
                if (u == p) continue;  // 親への辺は無視

                if (visited[u]) {
                    // サイクル発見
                    cycle_path.clear();
                    int curr = v;
                    while (curr != u) {
                        cycle_path.push_back(curr);
                        curr = parent[curr];
                    }
                    cycle_path.push_back(u);
                    reverse(cycle_path.begin(), cycle_path.end());
                    return true;
                }

                if (dfs(u, v)) return true;
            }

            return false;
        };

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (dfs(i, -1)) {
                    has_cycle = true;
                    return true;
                }
            }
        }

        return false;
    }

    // Union-Findを使った無向グラフのサイクル検出
    bool detect_undirected_cycle_union_find() {
        vector<int> parent(n);
        vector<int> rank(n, 0);

        // Union-Find初期化
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }

        function<int(int)> find = [&](int x) -> int {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };

        auto unite = [&](int x, int y) -> bool {
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
        };

        // エッジを処理
        for (const auto& edge : g.edges) {
            if (!unite(edge.from, edge.to)) {
                has_cycle = true;
                return true;
            }
        }

        return false;
    }

    // 最短サイクルを検出（重み付きグラフ）
    pair<bool, long long> shortest_cycle() {
        long long min_cycle = LLONG_MAX;
        bool found = false;

        // 各辺を削除して最短経路を計算
        for (const auto& removed_edge : g.edges) {
            vector<long long> dist(n, LLONG_MAX);
            dist[removed_edge.from] = 0;

            // Bellman-Ford法で最短経路を計算（削除した辺以外）
            for (int i = 0; i < n - 1; i++) {
                for (const auto& edge : g.edges) {
                    if (edge.from == removed_edge.from && edge.to == removed_edge.to) continue;
                    if (dist[edge.from] != LLONG_MAX && dist[edge.from] + edge.cost < dist[edge.to]) {
                        dist[edge.to] = dist[edge.from] + edge.cost;
                    }
                }
            }

            // 削除した辺を使ってサイクルができるかチェック
            if (dist[removed_edge.to] != LLONG_MAX) {
                long long cycle_length = dist[removed_edge.to] + removed_edge.cost;
                min_cycle = min(min_cycle, cycle_length);
                found = true;
            }
        }

        return {found, found ? min_cycle : -1};
    }

    // サイクルが存在するかチェック
    bool has_cycle_directed() {
        return detect_directed_cycle();
    }

    bool has_cycle_undirected() {
        return detect_undirected_cycle();
    }

    // 見つかったサイクルのパスを取得
    vector<int> get_cycle_path() {
        return cycle_path;
    }

    // すべてのサイクルを検出（小さなグラフ用）
    vector<vector<int>> find_all_simple_cycles() {
        vector<vector<int>> all_cycles;

        function<void(int, vector<int>&, vector<bool>&)> dfs = [&](int v, vector<int>& path, vector<bool>& in_path) {
            if (path.size() > n) return;  // 長すぎる場合は打ち切り

            for (int u : g.adj_unweighted[v]) {
                if (in_path[u]) {
                    // サイクル発見
                    auto it = find(path.begin(), path.end(), u);
                    if (it != path.end()) {
                        vector<int> cycle(it, path.end());
                        cycle.push_back(u);
                        all_cycles.push_back(cycle);
                    }
                } else {
                    path.push_back(u);
                    in_path[u] = true;
                    dfs(u, path, in_path);
                    path.pop_back();
                    in_path[u] = false;
                }
            }
        };

        for (int start = 0; start < n; start++) {
            vector<int> path = {start};
            vector<bool> in_path(n, false);
            in_path[start] = true;
            dfs(start, path, in_path);
        }

        // 重複を除去
        sort(all_cycles.begin(), all_cycles.end());
        all_cycles.erase(unique(all_cycles.begin(), all_cycles.end()), all_cycles.end());

        return all_cycles;
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: 有向グラフのサイクル検出" << endl;
    Graph directed_g(4);
    directed_g.add_unweighted_edge(0, 1);
    directed_g.add_unweighted_edge(1, 2);
    directed_g.add_unweighted_edge(2, 3);
    directed_g.add_unweighted_edge(3, 1);  // サイクル: 1->2->3->1

    CycleDetection cd1(directed_g);
    if (cd1.detect_directed_cycle()) {
        cout << "有向サイクル発見: ";
        for (int v : cd1.get_cycle_path()) {
            cout << v << " ";
        }
        cout << endl;
    } else {
        cout << "有向サイクルなし" << endl;
    }
    cout << endl;

    cout << "例2: 無向グラフのサイクル検出" << endl;
    Graph undirected_g(5);
    undirected_g.add_unweighted_undirected_edge(0, 1);
    undirected_g.add_unweighted_undirected_edge(1, 2);
    undirected_g.add_unweighted_undirected_edge(2, 3);
    undirected_g.add_unweighted_undirected_edge(3, 0);  // サイクル
    undirected_g.add_unweighted_undirected_edge(3, 4);

    CycleDetection cd2(undirected_g);
    if (cd2.detect_undirected_cycle()) {
        cout << "無向サイクル発見: ";
        for (int v : cd2.get_cycle_path()) {
            cout << v << " ";
        }
        cout << endl;
    }

    cout << "Union-Findでの検出: " << (cd2.detect_undirected_cycle_union_find() ? "サイクルあり" : "サイクルなし") << endl;
    cout << endl;

    cout << "例3: DAG（非循環有向グラフ）" << endl;
    Graph dag(4);
    dag.add_unweighted_edge(0, 1);
    dag.add_unweighted_edge(0, 2);
    dag.add_unweighted_edge(1, 3);
    dag.add_unweighted_edge(2, 3);

    CycleDetection cd3(dag);
    cout << "DAGにサイクル: " << (cd3.detect_directed_cycle() ? "あり" : "なし") << endl;
    cout << endl;

    cout << "例4: 重み付きグラフの最短サイクル" << endl;
    Graph weighted_g(4);
    weighted_g.add_edge(0, 1, 2);
    weighted_g.add_edge(1, 2, 3);
    weighted_g.add_edge(2, 3, 1);
    weighted_g.add_edge(3, 0, 4);  // サイクル 0->1->2->3->0, 重み10
    weighted_g.add_edge(0, 2, 5);  // 別経路

    CycleDetection cd4(weighted_g);
    auto [has_cycle, min_length] = cd4.shortest_cycle();
    if (has_cycle) {
        cout << "最短サイクル長: " << min_length << endl;
    } else {
        cout << "サイクルなし" << endl;
    }
    cout << endl;

    cout << "例5: 木構造（サイクルなし）" << endl;
    Graph tree(4);
    tree.add_unweighted_undirected_edge(0, 1);
    tree.add_unweighted_undirected_edge(1, 2);
    tree.add_unweighted_undirected_edge(1, 3);

    CycleDetection cd5(tree);
    cout << "木構造にサイクル: " << (cd5.detect_undirected_cycle() ? "あり" : "なし") << endl;

    return 0;
}