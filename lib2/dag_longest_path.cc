// DAG最長経路 dag_longest_path 有向非循環グラフ トポロジカルソート 動的計画法

#include <iostream>
#include <vector>
#include <algorithm>
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

// ========== DAG最長経路ライブラリ ==========

struct DAGLongestPath {
    Graph& g;
    int n;
    vector<long long> dist;
    vector<int> parent;
    vector<int> topo_order;
    bool is_dag;

    DAGLongestPath(Graph& graph) : g(graph), n(graph.n), dist(graph.n), parent(graph.n), is_dag(true) {}

    // トポロジカルソートを実行してDAGかチェック
    bool topological_sort() {
        topo_order.clear();
        vector<int> in_degree(n, 0);

        // 入次数を計算
        for (int v = 0; v < n; v++) {
            for (int u : g.adj_unweighted[v]) {
                in_degree[u]++;
            }
        }

        queue<int> q;
        for (int v = 0; v < n; v++) {
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            topo_order.push_back(v);

            for (int u : g.adj_unweighted[v]) {
                in_degree[u]--;
                if (in_degree[u] == 0) {
                    q.push(u);
                }
            }
        }

        is_dag = (topo_order.size() == n);
        return is_dag;
    }

    // 単一始点からの最長経路（DPベース）
    bool longest_path_from_source(int start) {
        if (!topological_sort()) return false;

        fill(dist.begin(), dist.end(), LLONG_MIN);
        fill(parent.begin(), parent.end(), -1);
        dist[start] = 0;

        for (int v : topo_order) {
            if (dist[v] == LLONG_MIN) continue;

            for (const auto& edge : g.adj[v]) {
                if (dist[edge.to] < dist[v] + edge.cost) {
                    dist[edge.to] = dist[v] + edge.cost;
                    parent[edge.to] = v;
                }
            }
        }

        return true;
    }

    // 全ペア間最長経路を計算
    vector<vector<long long>> all_pairs_longest_path() {
        if (!topological_sort()) return {};

        vector<vector<long long>> all_dist(n, vector<long long>(n, LLONG_MIN));

        // 各頂点を始点として最長経路を計算
        for (int start = 0; start < n; start++) {
            all_dist[start][start] = 0;

            for (int v : topo_order) {
                if (all_dist[start][v] == LLONG_MIN) continue;

                for (const auto& edge : g.adj[v]) {
                    if (all_dist[start][edge.to] < all_dist[start][v] + edge.cost) {
                        all_dist[start][edge.to] = all_dist[start][v] + edge.cost;
                    }
                }
            }
        }

        return all_dist;
    }

    // DAG内の最長経路を取得
    pair<long long, vector<int>> get_longest_path() {
        if (!topological_sort()) return {-1, {}};

        vector<vector<long long>> all_dist = all_pairs_longest_path();
        long long max_dist = LLONG_MIN;
        int best_start = -1, best_end = -1;

        // 全ペアの中で最長経路を見つける
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (all_dist[i][j] > max_dist) {
                    max_dist = all_dist[i][j];
                    best_start = i;
                    best_end = j;
                }
            }
        }

        if (best_start == -1) return {0, {}};

        // 最長経路を復元
        longest_path_from_source(best_start);
        vector<int> path;
        int curr = best_end;
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());

        return {max_dist, path};
    }

    // 指定した始点から到達可能な最遠点までの距離と経路
    pair<long long, vector<int>> farthest_from_source(int start) {
        if (!longest_path_from_source(start)) return {-1, {}};

        long long max_dist = LLONG_MIN;
        int farthest_node = -1;

        for (int i = 0; i < n; i++) {
            if (dist[i] > max_dist) {
                max_dist = dist[i];
                farthest_node = i;
            }
        }

        if (farthest_node == -1) return {0, {start}};

        // 経路を復元
        vector<int> path;
        int curr = farthest_node;
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());

        return {max_dist, path};
    }

    // 最長パスの頂点数（重みなしの場合）
    int longest_path_length() {
        if (!topological_sort()) return -1;

        vector<int> path_length(n, 0);

        for (int v : topo_order) {
            for (int u : g.adj_unweighted[v]) {
                path_length[u] = max(path_length[u], path_length[v] + 1);
            }
        }

        return *max_element(path_length.begin(), path_length.end());
    }

    // 特定の始点と終点間の最長経路
    pair<long long, vector<int>> longest_path_between(int start, int end) {
        if (!longest_path_from_source(start)) return {-1, {}};

        if (dist[end] == LLONG_MIN) return {-1, {}};  // 到達不可能

        // 経路を復元
        vector<int> path;
        int curr = end;
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());

        return {dist[end], path};
    }

    // DAGかどうかを判定
    bool is_dag_valid() {
        return topological_sort();
    }

    // トポロジカル順序を取得
    vector<int> get_topological_order() {
        if (!is_dag) topological_sort();
        return topo_order;
    }

    // 各頂点への距離を取得
    vector<long long> get_distances() {
        return dist;
    }

    // クリティカルパス分析（プロジェクトスケジューリング）
    struct TaskInfo {
        long long earliest_start;
        long long latest_start;
        long long slack;
        bool is_critical;
    };

    vector<TaskInfo> critical_path_analysis() {
        if (!topological_sort()) return {};

        vector<TaskInfo> tasks(n);

        // Forward pass: earliest start time
        vector<long long> earliest(n, 0);
        for (int v : topo_order) {
            tasks[v].earliest_start = earliest[v];
            for (const auto& edge : g.adj[v]) {
                earliest[edge.to] = max(earliest[edge.to], earliest[v] + edge.cost);
            }
        }

        // Backward pass: latest start time
        long long project_duration = *max_element(earliest.begin(), earliest.end());
        vector<long long> latest(n, project_duration);

        reverse(topo_order.begin(), topo_order.end());
        for (int v : topo_order) {
            tasks[v].latest_start = latest[v];
            for (const auto& edge : g.adj[v]) {
                latest[v] = min(latest[v], latest[edge.to] - edge.cost);
            }
        }

        // Calculate slack and identify critical tasks
        for (int i = 0; i < n; i++) {
            tasks[i].slack = tasks[i].latest_start - tasks[i].earliest_start;
            tasks[i].is_critical = (tasks[i].slack == 0);
        }

        return tasks;
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: 基本的なDAG最長経路" << endl;
    Graph dag1(6);

    // DAGを構築
    dag1.add_edge(0, 1, 3);
    dag1.add_edge(0, 2, 2);
    dag1.add_edge(1, 3, 4);
    dag1.add_edge(2, 3, 1);
    dag1.add_edge(2, 4, 5);
    dag1.add_edge(3, 4, 2);
    dag1.add_edge(3, 5, 6);
    dag1.add_edge(4, 5, 1);

    DAGLongestPath dlp1(dag1);

    if (dlp1.is_dag_valid()) {
        cout << "DAGです" << endl;

        auto [max_dist, longest_path] = dlp1.get_longest_path();
        cout << "最長経路の距離: " << max_dist << endl;
        cout << "最長経路: ";
        for (int v : longest_path) {
            cout << v << " ";
        }
        cout << endl;
    } else {
        cout << "DAGではありません（サイクルが存在）" << endl;
    }
    cout << endl;

    cout << "例2: 特定の始点からの最遠点" << endl;
    auto [farthest_dist, farthest_path] = dlp1.farthest_from_source(0);
    cout << "頂点0からの最遠距離: " << farthest_dist << endl;
    cout << "頂点0からの最遠経路: ";
    for (int v : farthest_path) {
        cout << v << " ";
    }
    cout << endl << endl;

    cout << "例3: 重みなしDAGの最長パス" << endl;
    Graph unweighted_dag(5);
    unweighted_dag.add_unweighted_edge(0, 1);
    unweighted_dag.add_unweighted_edge(0, 2);
    unweighted_dag.add_unweighted_edge(1, 3);
    unweighted_dag.add_unweighted_edge(2, 3);
    unweighted_dag.add_unweighted_edge(3, 4);

    DAGLongestPath dlp2(unweighted_dag);
    int longest_length = dlp2.longest_path_length();
    cout << "最長パスの頂点数: " << longest_length + 1 << " (辺数: " << longest_length << ")" << endl;
    cout << endl;

    cout << "例4: 特定の始点・終点間の最長経路" << endl;
    auto [path_dist, path] = dlp1.longest_path_between(0, 5);
    if (path_dist != -1) {
        cout << "頂点0から頂点5への最長経路距離: " << path_dist << endl;
        cout << "経路: ";
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
    } else {
        cout << "頂点0から頂点5への経路が存在しません" << endl;
    }
    cout << endl;

    cout << "例5: クリティカルパス分析（プロジェクトスケジューリング）" << endl;
    auto tasks = dlp1.critical_path_analysis();
    cout << "タスク分析:" << endl;
    cout << "Task | ES | LS | Slack | Critical" << endl;
    cout << "-----|----|----|-------|----------" << endl;
    for (int i = 0; i < tasks.size(); i++) {
        cout << "  " << i << "  | "
             << tasks[i].earliest_start << "  | "
             << tasks[i].latest_start << "  |   "
             << tasks[i].slack << "   | "
             << (tasks[i].is_critical ? "Yes" : "No") << endl;
    }
    cout << endl;

    cout << "例6: サイクルを含むグラフでの検証" << endl;
    Graph cyclic_g(3);
    cyclic_g.add_edge(0, 1, 1);
    cyclic_g.add_edge(1, 2, 1);
    cyclic_g.add_edge(2, 0, 1);  // サイクル

    DAGLongestPath dlp3(cyclic_g);
    if (dlp3.is_dag_valid()) {
        cout << "DAGです" << endl;
    } else {
        cout << "DAGではありません（サイクルが存在するため最長経路は未定義）" << endl;
    }

    return 0;
}