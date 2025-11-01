// 二部マッチング bipartite_matching 最大マッチング hungarian

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

// ========== 二部マッチングライブラリ ==========

struct BipartiteMatching {
    int n, m;  // 左側n個、右側m個
    vector<vector<int>> graph;  // 左側から右側への辺
    vector<int> match_left, match_right;  // マッチング結果
    vector<bool> visited;

    BipartiteMatching(int n, int m) : n(n), m(m), graph(n), match_left(n, -1), match_right(m, -1), visited(n) {}

    // 左側の頂点leftから右側の頂点rightへの辺を追加
    void add_edge(int left, int right) {
        graph[left].push_back(right);
    }

    // DFSで増加路を探す
    bool dfs(int v) {
        for (int to : graph[v]) {
            if (visited[to]) continue;
            visited[to] = true;

            if (match_right[to] == -1 || dfs(match_right[to])) {
                match_left[v] = to;
                match_right[to] = v;
                return true;
            }
        }
        return false;
    }

    // 最大マッチングを計算
    int max_matching() {
        int result = 0;
        for (int v = 0; v < n; v++) {
            fill(visited.begin(), visited.end(), false);
            if (dfs(v)) {
                result++;
            }
        }
        return result;
    }

    // マッチング結果を取得
    vector<pair<int, int>> get_matching() {
        vector<pair<int, int>> matching;
        for (int i = 0; i < n; i++) {
            if (match_left[i] != -1) {
                matching.push_back({i, match_left[i]});
            }
        }
        return matching;
    }

    // 左側の頂点iにマッチしている右側の頂点を取得（-1なら未マッチ）
    int get_match_right(int left) {
        return match_left[left];
    }

    // 右側の頂点jにマッチしている左側の頂点を取得（-1なら未マッチ）
    int get_match_left(int right) {
        return match_right[right];
    }

    // 最大独立集合を取得（König's theorem）
    pair<vector<int>, vector<int>> max_independent_set() {
        max_matching();  // まずマッチングを計算

        // 未マッチの左側頂点から到達可能な頂点を探す
        vector<bool> reachable_left(n, false);
        vector<bool> reachable_right(m, false);

        function<void(int)> dfs_reachable = [&](int v) {
            reachable_left[v] = true;
            for (int to : graph[v]) {
                if (!reachable_right[to]) {
                    reachable_right[to] = true;
                    if (match_right[to] != -1 && !reachable_left[match_right[to]]) {
                        dfs_reachable(match_right[to]);
                    }
                }
            }
        };

        for (int i = 0; i < n; i++) {
            if (match_left[i] == -1 && !reachable_left[i]) {
                dfs_reachable(i);
            }
        }

        // 最大独立集合は到達不可能な左側頂点 + 到達可能な右側頂点
        vector<int> independent_left, independent_right;
        for (int i = 0; i < n; i++) {
            if (!reachable_left[i]) {
                independent_left.push_back(i);
            }
        }
        for (int i = 0; i < m; i++) {
            if (reachable_right[i]) {
                independent_right.push_back(i);
            }
        }

        return {independent_left, independent_right};
    }

    // 最小頂点被覆を取得（König's theorem）
    pair<vector<int>, vector<int>> min_vertex_cover() {
        max_matching();

        vector<bool> reachable_left(n, false);
        vector<bool> reachable_right(m, false);

        function<void(int)> dfs_reachable = [&](int v) {
            reachable_left[v] = true;
            for (int to : graph[v]) {
                if (!reachable_right[to]) {
                    reachable_right[to] = true;
                    if (match_right[to] != -1 && !reachable_left[match_right[to]]) {
                        dfs_reachable(match_right[to]);
                    }
                }
            }
        };

        for (int i = 0; i < n; i++) {
            if (match_left[i] == -1 && !reachable_left[i]) {
                dfs_reachable(i);
            }
        }

        // 最小頂点被覆は到達可能な左側頂点 + 到達不可能な右側頂点
        vector<int> cover_left, cover_right;
        for (int i = 0; i < n; i++) {
            if (reachable_left[i]) {
                cover_left.push_back(i);
            }
        }
        for (int i = 0; i < m; i++) {
            if (!reachable_right[i]) {
                cover_right.push_back(i);
            }
        }

        return {cover_left, cover_right};
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: 基本的な二部マッチング" << endl;
    BipartiteMatching bm1(4, 4);

    // 左側の人と右側の仕事のマッチング
    bm1.add_edge(0, 0);  // 人0 -> 仕事0
    bm1.add_edge(0, 1);  // 人0 -> 仕事1
    bm1.add_edge(1, 1);  // 人1 -> 仕事1
    bm1.add_edge(1, 2);  // 人1 -> 仕事2
    bm1.add_edge(2, 2);  // 人2 -> 仕事2
    bm1.add_edge(3, 3);  // 人3 -> 仕事3

    int max_match = bm1.max_matching();
    cout << "最大マッチング数: " << max_match << endl;

    auto matching = bm1.get_matching();
    cout << "マッチング結果:" << endl;
    for (auto [left, right] : matching) {
        cout << "  人" << left << " -> 仕事" << right << endl;
    }
    cout << endl;

    cout << "例2: 完全マッチングが存在しない場合" << endl;
    BipartiteMatching bm2(3, 2);

    bm2.add_edge(0, 0);
    bm2.add_edge(1, 0);
    bm2.add_edge(2, 1);

    int max_match2 = bm2.max_matching();
    cout << "最大マッチング数: " << max_match2 << endl;
    cout << "完全マッチング: " << (max_match2 == min(3, 2) ? "存在" : "不存在") << endl;
    cout << endl;

    cout << "例3: König's定理の応用" << endl;
    BipartiteMatching bm3(4, 3);

    bm3.add_edge(0, 0);
    bm3.add_edge(0, 1);
    bm3.add_edge(1, 1);
    bm3.add_edge(2, 1);
    bm3.add_edge(2, 2);
    bm3.add_edge(3, 2);

    int matching_size = bm3.max_matching();
    cout << "最大マッチング数: " << matching_size << endl;

    auto [cover_left, cover_right] = bm3.min_vertex_cover();
    cout << "最小頂点被覆サイズ: " << cover_left.size() + cover_right.size() << endl;
    cout << "左側被覆頂点: ";
    for (int v : cover_left) cout << v << " ";
    cout << endl;
    cout << "右側被覆頂点: ";
    for (int v : cover_right) cout << v << " ";
    cout << endl;

    auto [indep_left, indep_right] = bm3.max_independent_set();
    cout << "最大独立集合サイズ: " << indep_left.size() + indep_right.size() << endl;
    cout << "左側独立集合: ";
    for (int v : indep_left) cout << v << " ";
    cout << endl;
    cout << "右側独立集合: ";
    for (int v : indep_right) cout << v << " ";
    cout << endl;

    cout << "König's定理検証: 最大マッチング(" << matching_size << ") = 最小頂点被覆(" << cover_left.size() + cover_right.size() << ")" << endl;

    return 0;
}