// オイラー路・オイラー回路 euler_path hierholzer 一筆書き

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
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

// ========== オイラー路ライブラリ ==========

struct EulerPath {
    Graph& g;
    int n;
    vector<vector<int>> adj_list;  // 作業用隣接リスト
    vector<int> in_degree, out_degree;
    vector<int> euler_path;
    bool is_directed;

    EulerPath(Graph& graph, bool directed = false) : g(graph), n(graph.n), is_directed(directed) {
        adj_list.assign(n, vector<int>());
        in_degree.assign(n, 0);
        out_degree.assign(n, 0);
    }

    // 隣接リストを初期化
    void initialize_adj_list() {
        for (int i = 0; i < n; i++) {
            adj_list[i] = g.adj_unweighted[i];
        }

        // 次数を計算
        fill(in_degree.begin(), in_degree.end(), 0);
        fill(out_degree.begin(), out_degree.end(), 0);

        if (is_directed) {
            for (int v = 0; v < n; v++) {
                for (int u : g.adj_unweighted[v]) {
                    out_degree[v]++;
                    in_degree[u]++;
                }
            }
        } else {
            for (int v = 0; v < n; v++) {
                out_degree[v] = in_degree[v] = g.adj_unweighted[v].size();
            }
        }
    }

    // グラフが連結かチェック（オイラー路/回路が存在するために必要）
    bool is_connected() {
        vector<bool> visited(n, false);

        // 次数が0でない頂点から開始
        int start = -1;
        for (int i = 0; i < n; i++) {
            if (out_degree[i] > 0 || in_degree[i] > 0) {
                start = i;
                break;
            }
        }

        if (start == -1) return true;  // 辺がない場合は連結

        function<void(int)> dfs = [&](int v) {
            visited[v] = true;
            for (int u : g.adj_unweighted[v]) {
                if (!visited[u]) {
                    dfs(u);
                }
            }
        };

        dfs(start);

        // 次数が0でないすべての頂点が訪問されているかチェック
        for (int i = 0; i < n; i++) {
            if ((out_degree[i] > 0 || in_degree[i] > 0) && !visited[i]) {
                return false;
            }
        }

        return true;
    }

    // 有向グラフでオイラー路/回路が存在するかチェック
    pair<bool, int> check_directed_euler() {
        initialize_adj_list();

        if (!is_connected()) return {false, -1};

        int start_vertices = 0;  // 出次数 - 入次数 = 1
        int end_vertices = 0;    // 入次数 - 出次数 = 1
        int start_node = 0;

        for (int i = 0; i < n; i++) {
            int diff = out_degree[i] - in_degree[i];
            if (diff == 1) {
                start_vertices++;
                start_node = i;
            } else if (diff == -1) {
                end_vertices++;
            } else if (diff != 0) {
                return {false, -1};
            }
        }

        // オイラー回路: すべての頂点で入次数=出次数
        if (start_vertices == 0 && end_vertices == 0) {
            // 任意の頂点から開始可能
            for (int i = 0; i < n; i++) {
                if (out_degree[i] > 0) {
                    start_node = i;
                    break;
                }
            }
            return {true, start_node};
        }

        // オイラー路: 開始頂点1つ、終了頂点1つ
        if (start_vertices == 1 && end_vertices == 1) {
            return {true, start_node};
        }

        return {false, -1};
    }

    // 無向グラフでオイラー路/回路が存在するかチェック
    pair<bool, int> check_undirected_euler() {
        initialize_adj_list();

        if (!is_connected()) return {false, -1};

        int odd_vertices = 0;
        int start_node = 0;

        for (int i = 0; i < n; i++) {
            if (out_degree[i] % 2 == 1) {
                odd_vertices++;
                start_node = i;
            }
        }

        // オイラー回路: すべての頂点の次数が偶数
        if (odd_vertices == 0) {
            // 任意の頂点から開始可能
            for (int i = 0; i < n; i++) {
                if (out_degree[i] > 0) {
                    start_node = i;
                    break;
                }
            }
            return {true, start_node};
        }

        // オイラー路: 奇数次数の頂点がちょうど2つ
        if (odd_vertices == 2) {
            return {true, start_node};
        }

        return {false, -1};
    }

    // Hierholzerのアルゴリズムでオイラー路を構築
    bool find_euler_path() {
        euler_path.clear();

        auto [exists, start] = is_directed ? check_directed_euler() : check_undirected_euler();
        if (!exists) return false;

        stack<int> curr_path;
        vector<int> circuit;
        curr_path.push(start);

        while (!curr_path.empty()) {
            int curr = curr_path.top();

            if (!adj_list[curr].empty()) {
                int next = adj_list[curr].back();
                adj_list[curr].pop_back();

                // 無向グラフの場合、逆方向の辺も削除
                if (!is_directed) {
                    auto it = find(adj_list[next].begin(), adj_list[next].end(), curr);
                    if (it != adj_list[next].end()) {
                        adj_list[next].erase(it);
                    }
                }

                curr_path.push(next);
            } else {
                circuit.push_back(curr);
                curr_path.pop();
            }
        }

        euler_path = circuit;
        reverse(euler_path.begin(), euler_path.end());
        return true;
    }

    // オイラー路を取得
    vector<int> get_euler_path() {
        if (euler_path.empty()) {
            find_euler_path();
        }
        return euler_path;
    }

    // オイラー回路かオイラー路かを判定
    string get_euler_type() {
        auto [exists, start] = is_directed ? check_directed_euler() : check_undirected_euler();
        if (!exists) return "None";

        if (is_directed) {
            bool all_equal = true;
            for (int i = 0; i < n; i++) {
                if (in_degree[i] != out_degree[i]) {
                    all_equal = false;
                    break;
                }
            }
            return all_equal ? "Euler Circuit" : "Euler Path";
        } else {
            int odd_count = 0;
            for (int i = 0; i < n; i++) {
                if (out_degree[i] % 2 == 1) odd_count++;
            }
            return (odd_count == 0) ? "Euler Circuit" : "Euler Path";
        }
    }

    // 各頂点の次数を取得
    vector<pair<int, int>> get_degrees() {
        initialize_adj_list();
        vector<pair<int, int>> degrees;
        for (int i = 0; i < n; i++) {
            degrees.push_back({in_degree[i], out_degree[i]});
        }
        return degrees;
    }

    // オイラー路の辺数を取得
    int get_edge_count() {
        return is_directed ? g.edges.size() : g.edges.size();
    }

    // オイラー路の検証
    bool verify_euler_path(const vector<int>& path) {
        if (path.empty()) return false;

        // 辺の使用回数をカウント
        map<pair<int, int>, int> edge_count;

        for (const auto& edge : g.edges) {
            if (is_directed) {
                edge_count[{edge.from, edge.to}]++;
            } else {
                edge_count[{min(edge.from, edge.to), max(edge.from, edge.to)}]++;
            }
        }

        // パスの辺をカウント
        map<pair<int, int>, int> path_edge_count;
        for (int i = 0; i < path.size() - 1; i++) {
            int u = path[i], v = path[i + 1];
            if (is_directed) {
                path_edge_count[{u, v}]++;
            } else {
                path_edge_count[{min(u, v), max(u, v)}]++;
            }
        }

        return edge_count == path_edge_count;
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: 無向グラフのオイラー回路" << endl;
    Graph undirected_circuit(4);
    undirected_circuit.add_unweighted_undirected_edge(0, 1);
    undirected_circuit.add_unweighted_undirected_edge(1, 2);
    undirected_circuit.add_unweighted_undirected_edge(2, 3);
    undirected_circuit.add_unweighted_undirected_edge(3, 0);

    EulerPath ep1(undirected_circuit, false);
    cout << "オイラータイプ: " << ep1.get_euler_type() << endl;

    if (ep1.find_euler_path()) {
        auto path = ep1.get_euler_path();
        cout << "オイラー回路: ";
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
        cout << "検証: " << (ep1.verify_euler_path(path) ? "正しい" : "間違い") << endl;
    }
    cout << endl;

    cout << "例2: 無向グラフのオイラー路" << endl;
    Graph undirected_path(5);
    undirected_path.add_unweighted_undirected_edge(0, 1);
    undirected_path.add_unweighted_undirected_edge(1, 2);
    undirected_path.add_unweighted_undirected_edge(2, 3);
    undirected_path.add_unweighted_undirected_edge(3, 4);
    undirected_path.add_unweighted_undirected_edge(1, 3);

    EulerPath ep2(undirected_path, false);
    cout << "オイラータイプ: " << ep2.get_euler_type() << endl;

    auto degrees = ep2.get_degrees();
    cout << "各頂点の次数:" << endl;
    for (int i = 0; i < undirected_path.n; i++) {
        cout << "頂点" << i << ": " << degrees[i].first << endl;
    }

    if (ep2.find_euler_path()) {
        auto path = ep2.get_euler_path();
        cout << "オイラー路: ";
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "例3: 有向グラフのオイラー回路" << endl;
    Graph directed_circuit(3);
    directed_circuit.add_unweighted_edge(0, 1);
    directed_circuit.add_unweighted_edge(1, 2);
    directed_circuit.add_unweighted_edge(2, 0);

    EulerPath ep3(directed_circuit, true);
    cout << "オイラータイプ: " << ep3.get_euler_type() << endl;

    auto dir_degrees = ep3.get_degrees();
    cout << "各頂点の次数（入次数, 出次数）:" << endl;
    for (int i = 0; i < directed_circuit.n; i++) {
        cout << "頂点" << i << ": (" << dir_degrees[i].first << ", " << dir_degrees[i].second << ")" << endl;
    }

    if (ep3.find_euler_path()) {
        auto path = ep3.get_euler_path();
        cout << "オイラー回路: ";
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "例4: 有向グラフのオイラー路" << endl;
    Graph directed_path(4);
    directed_path.add_unweighted_edge(0, 1);
    directed_path.add_unweighted_edge(1, 2);
    directed_path.add_unweighted_edge(2, 3);
    directed_path.add_unweighted_edge(1, 3);

    EulerPath ep4(directed_path, true);
    cout << "オイラータイプ: " << ep4.get_euler_type() << endl;

    if (ep4.find_euler_path()) {
        auto path = ep4.get_euler_path();
        cout << "オイラー路: ";
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "例5: オイラー路が存在しないグラフ" << endl;
    Graph no_euler(4);
    no_euler.add_unweighted_undirected_edge(0, 1);
    no_euler.add_unweighted_undirected_edge(1, 2);
    no_euler.add_unweighted_undirected_edge(2, 3);
    no_euler.add_unweighted_undirected_edge(0, 2);  // 奇数次数の頂点が4つ

    EulerPath ep5(no_euler, false);
    cout << "オイラータイプ: " << ep5.get_euler_type() << endl;

    auto no_euler_degrees = ep5.get_degrees();
    cout << "各頂点の次数:" << endl;
    int odd_count = 0;
    for (int i = 0; i < no_euler.n; i++) {
        cout << "頂点" << i << ": " << no_euler_degrees[i].first;
        if (no_euler_degrees[i].first % 2 == 1) {
            cout << " (奇数)";
            odd_count++;
        }
        cout << endl;
    }
    cout << "奇数次数の頂点数: " << odd_count << " (オイラー路には2つまで必要)" << endl;

    return 0;
}