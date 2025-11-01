// トポロジカルソート topological_sort 有向非循環グラフ dag kahn

#include <iostream>
#include <vector>
#include <queue>
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

// ========== トポロジカルソートライブラリ ==========

struct TopologicalSort {
    Graph& g;
    vector<int> sorted_order;
    vector<int> in_degree;
    bool is_sorted;
    bool has_cycle;

    TopologicalSort(Graph& graph) : g(graph), in_degree(graph.n, 0), is_sorted(false), has_cycle(false) {}

    // 入次数を計算
    void calculate_in_degree() {
        fill(in_degree.begin(), in_degree.end(), 0);
        for (int v = 0; v < g.n; v++) {
            for (int u : g.adj_unweighted[v]) {
                in_degree[u]++;
            }
        }
    }

    // Kahn's algorithmでトポロジカルソート
    bool kahn_sort() {
        sorted_order.clear();
        calculate_in_degree();

        queue<int> q;
        for (int v = 0; v < g.n; v++) {
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            sorted_order.push_back(v);

            for (int u : g.adj_unweighted[v]) {
                in_degree[u]--;
                if (in_degree[u] == 0) {
                    q.push(u);
                }
            }
        }

        has_cycle = (sorted_order.size() != g.n);
        is_sorted = !has_cycle;
        return is_sorted;
    }

    // DFSベースのトポロジカルソート
    bool dfs_sort() {
        sorted_order.clear();
        vector<int> state(g.n, 0);  // 0: 未訪問, 1: 訪問中, 2: 完了
        has_cycle = false;

        function<void(int)> dfs = [&](int v) {
            state[v] = 1;
            for (int u : g.adj_unweighted[v]) {
                if (state[u] == 1) {
                    has_cycle = true;
                    return;
                }
                if (state[u] == 0) {
                    dfs(u);
                }
            }
            state[v] = 2;
            sorted_order.push_back(v);
        };

        for (int v = 0; v < g.n; v++) {
            if (state[v] == 0) {
                dfs(v);
                if (has_cycle) break;
            }
        }

        if (!has_cycle) {
            reverse(sorted_order.begin(), sorted_order.end());
        }

        is_sorted = !has_cycle;
        return is_sorted;
    }

    // トポロジカルソート順序を取得
    vector<int> get_sorted_order() {
        if (!is_sorted) kahn_sort();
        return sorted_order;
    }

    // グラフにサイクルがあるかチェック
    bool check_cycle() {
        if (!is_sorted) kahn_sort();
        return has_cycle;
    }

    // 各頂点のトポロジカル順序での位置を取得
    vector<int> get_topological_position() {
        if (!is_sorted) kahn_sort();
        vector<int> position(g.n);
        for (int i = 0; i < sorted_order.size(); i++) {
            position[sorted_order[i]] = i;
        }
        return position;
    }

    // 字句順最小のトポロジカルソートを取得
    vector<int> get_lexicographically_smallest() {
        sorted_order.clear();
        calculate_in_degree();

        priority_queue<int, vector<int>, greater<int>> pq;  // 昇順
        for (int v = 0; v < g.n; v++) {
            if (in_degree[v] == 0) {
                pq.push(v);
            }
        }

        while (!pq.empty()) {
            int v = pq.top();
            pq.pop();
            sorted_order.push_back(v);

            for (int u : g.adj_unweighted[v]) {
                in_degree[u]--;
                if (in_degree[u] == 0) {
                    pq.push(u);
                }
            }
        }

        has_cycle = (sorted_order.size() != g.n);
        is_sorted = !has_cycle;
        return sorted_order;
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: 基本的なDAG" << endl;
    Graph g1(6);
    g1.add_unweighted_edge(5, 2);
    g1.add_unweighted_edge(5, 0);
    g1.add_unweighted_edge(4, 0);
    g1.add_unweighted_edge(4, 1);
    g1.add_unweighted_edge(2, 3);
    g1.add_unweighted_edge(3, 1);

    TopologicalSort topo1(g1);
    if (topo1.kahn_sort()) {
        cout << "Kahn's algorithmによるトポロジカルソート: ";
        for (int v : topo1.get_sorted_order()) {
            cout << v << " ";
        }
        cout << endl;
    } else {
        cout << "グラフにサイクルが存在します" << endl;
    }

    if (topo1.dfs_sort()) {
        cout << "DFSによるトポロジカルソート: ";
        for (int v : topo1.get_sorted_order()) {
            cout << v << " ";
        }
        cout << endl;
    }

    cout << "字句順最小のトポロジカルソート: ";
    for (int v : topo1.get_lexicographically_smallest()) {
        cout << v << " ";
    }
    cout << endl << endl;

    cout << "例2: サイクルのあるグラフ" << endl;
    Graph g2(3);
    g2.add_unweighted_edge(0, 1);
    g2.add_unweighted_edge(1, 2);
    g2.add_unweighted_edge(2, 0);

    TopologicalSort topo2(g2);
    if (topo2.kahn_sort()) {
        cout << "トポロジカルソート成功" << endl;
    } else {
        cout << "グラフにサイクルが存在するため、トポロジカルソートできません" << endl;
    }
    cout << "サイクル検出結果: " << (topo2.check_cycle() ? "サイクルあり" : "サイクルなし") << endl;
    cout << endl;

    cout << "例3: 依存関係の例（タスクスケジューリング）" << endl;
    Graph g3(7);
    // タスク依存関係: 0->1, 0->2, 1->3, 2->3, 3->4, 4->5, 4->6
    g3.add_unweighted_edge(0, 1);
    g3.add_unweighted_edge(0, 2);
    g3.add_unweighted_edge(1, 3);
    g3.add_unweighted_edge(2, 3);
    g3.add_unweighted_edge(3, 4);
    g3.add_unweighted_edge(4, 5);
    g3.add_unweighted_edge(4, 6);

    TopologicalSort topo3(g3);
    cout << "タスク実行順序: ";
    for (int task : topo3.get_sorted_order()) {
        cout << "T" << task << " ";
    }
    cout << endl;

    auto positions = topo3.get_topological_position();
    cout << "各タスクの実行順位:" << endl;
    for (int i = 0; i < g3.n; i++) {
        cout << "  T" << i << ": " << positions[i] + 1 << "番目" << endl;
    }

    return 0;
}