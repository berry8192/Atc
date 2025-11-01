// 2-SAT two_sat 充足可能性 satisfiability 強連結成分

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

// ========== 2-SATライブラリ ==========

struct TwoSAT {
    int n;  // 変数の数
    Graph g;  // 含意グラフ
    vector<int> comp_id;  // 強連結成分ID
    vector<bool> assignment;  // 変数の真偽値割り当て
    bool is_satisfiable;

    TwoSAT(int n) : n(n), g(2 * n), comp_id(2 * n), assignment(n), is_satisfiable(false) {}

    // 変数iの正リテラルを取得 (i -> 2*i)
    int pos(int i) { return 2 * i; }

    // 変数iの負リテラル（否定）を取得 (¬i -> 2*i+1)
    int neg(int i) { return 2 * i + 1; }

    // 節 (a or b) を追加 (¬a -> b, ¬b -> a)
    void add_clause(int a, bool va, int b, bool vb) {
        // aの真偽値がvaでない場合、bの真偽値はvbでなければならない
        // bの真偽値がvbでない場合、aの真偽値はvaでなければならない
        g.add_unweighted_edge(va ? neg(a) : pos(a), vb ? pos(b) : neg(b));
        g.add_unweighted_edge(vb ? neg(b) : pos(b), va ? pos(a) : neg(a));
    }

    // at_most_one制約: 変数のうち最大1つだけtrue
    void add_at_most_one(const vector<int>& vars) {
        for (int i = 0; i < vars.size(); i++) {
            for (int j = i + 1; j < vars.size(); j++) {
                // vars[i] and vars[j] が同時にtrueになることはできない
                add_clause(vars[i], false, vars[j], false);  // ¬vars[i] or ¬vars[j]
            }
        }
    }

    // exactly_one制約: 変数のうちちょうど1つだけtrue
    void add_exactly_one(const vector<int>& vars) {
        // 少なくとも1つはtrue
        for (int i = 1; i < vars.size(); i++) {
            add_clause(vars[0], true, vars[i], true);
        }
        // 最大1つだけtrue
        add_at_most_one(vars);
    }

    // 強連結成分を使ってSATを解く
    bool solve() {
        // 強連結成分分解
        vector<vector<int>> scc_components = scc_decomposition();

        // 同じ強連結成分にxと¬xが含まれているかチェック
        for (int i = 0; i < n; i++) {
            if (comp_id[pos(i)] == comp_id[neg(i)]) {
                is_satisfiable = false;
                return false;
            }
        }

        // 変数の割り当てを決定
        for (int i = 0; i < n; i++) {
            // より大きな成分IDを持つ方をfalseにする（トポロジカル順序）
            assignment[i] = comp_id[pos(i)] > comp_id[neg(i)];
        }

        is_satisfiable = true;
        return true;
    }

    // 強連結成分分解（Kosaraju's algorithm）
    vector<vector<int>> scc_decomposition() {
        vector<bool> visited(2 * n, false);
        vector<int> finish_order;
        vector<vector<int>> reverse_graph(2 * n);

        // 逆グラフを構築
        for (int v = 0; v < 2 * n; v++) {
            for (int u : g.adj_unweighted[v]) {
                reverse_graph[u].push_back(v);
            }
        }

        // 最初のDFS
        function<void(int)> dfs1 = [&](int v) {
            visited[v] = true;
            for (int u : g.adj_unweighted[v]) {
                if (!visited[u]) {
                    dfs1(u);
                }
            }
            finish_order.push_back(v);
        };

        for (int v = 0; v < 2 * n; v++) {
            if (!visited[v]) {
                dfs1(v);
            }
        }

        // 二回目のDFS
        fill(visited.begin(), visited.end(), false);
        reverse(finish_order.begin(), finish_order.end());
        vector<vector<int>> components;

        function<void(int, vector<int>&)> dfs2 = [&](int v, vector<int>& component) {
            visited[v] = true;
            component.push_back(v);
            for (int u : reverse_graph[v]) {
                if (!visited[u]) {
                    dfs2(u, component);
                }
            }
        };

        for (int v : finish_order) {
            if (!visited[v]) {
                vector<int> component;
                dfs2(v, component);

                int comp_idx = components.size();
                for (int u : component) {
                    comp_id[u] = comp_idx;
                }

                components.push_back(component);
            }
        }

        return components;
    }

    // 解の取得
    vector<bool> get_assignment() {
        if (!is_satisfiable) solve();
        return assignment;
    }

    // 充足可能かどうか
    bool satisfiable() {
        if (!is_satisfiable) solve();
        return is_satisfiable;
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: 基本的な2-SAT問題" << endl;
    TwoSAT sat1(3);

    // (x0 or x1) and (¬x1 or x2) and (¬x0 or ¬x2)
    sat1.add_clause(0, true, 1, true);    // x0 or x1
    sat1.add_clause(1, false, 2, true);   // ¬x1 or x2
    sat1.add_clause(0, false, 2, false);  // ¬x0 or ¬x2

    if (sat1.solve()) {
        cout << "充足可能です" << endl;
        auto assignment = sat1.get_assignment();
        for (int i = 0; i < 3; i++) {
            cout << "x" << i << " = " << (assignment[i] ? "true" : "false") << endl;
        }
    } else {
        cout << "充足不可能です" << endl;
    }
    cout << endl;

    cout << "例2: 充足不可能な問題" << endl;
    TwoSAT sat2(2);

    // (x0 or x1) and (x0 or ¬x1) and (¬x0 or x1) and (¬x0 or ¬x1)
    sat2.add_clause(0, true, 1, true);    // x0 or x1
    sat2.add_clause(0, true, 1, false);   // x0 or ¬x1
    sat2.add_clause(0, false, 1, true);   // ¬x0 or x1
    sat2.add_clause(0, false, 1, false);  // ¬x0 or ¬x1

    if (sat2.solve()) {
        cout << "充足可能です" << endl;
    } else {
        cout << "充足不可能です（全ての組み合わせで矛盾）" << endl;
    }
    cout << endl;

    cout << "例3: at_most_one制約" << endl;
    TwoSAT sat3(4);

    // 変数0, 1, 2のうち最大1つだけtrue
    vector<int> vars = {0, 1, 2};
    sat3.add_at_most_one(vars);

    // 変数3はtrue
    sat3.add_clause(3, true, 3, true);  // x3 (恒真)

    if (sat3.solve()) {
        cout << "充足可能です" << endl;
        auto assignment = sat3.get_assignment();
        for (int i = 0; i < 4; i++) {
            cout << "x" << i << " = " << (assignment[i] ? "true" : "false") << endl;
        }

        int true_count = 0;
        for (int i = 0; i < 3; i++) {
            if (assignment[i]) true_count++;
        }
        cout << "変数0-2でtrueの数: " << true_count << " (最大1つまで)" << endl;
    }

    return 0;
}