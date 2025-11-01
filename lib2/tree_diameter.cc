// 木の直径 tree_diameter 最遠頂点対 O(V)

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

// ========== ライブラリ本体 ==========

// BFSで最遠点を求める（重みなし木）
pair<int, int> bfs_farthest(Graph& g, int start) {
    vector<int> dist(g.n, -1);
    queue<int> q;

    dist[start] = 0;
    q.push(start);

    int max_dist = 0;
    int farthest = start;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int next : g.adj_unweighted[v]) {
            if (dist[next] == -1) {
                dist[next] = dist[v] + 1;
                q.push(next);
                if (dist[next] > max_dist) {
                    max_dist = dist[next];
                    farthest = next;
                }
            }
        }
    }

    return {farthest, max_dist};
}

// DFSで最遠点を求める（重み付き木）
pair<int, long long> dfs_farthest(Graph& g, int start) {
    vector<long long> dist(g.n, -1);
    dist[start] = 0;

    function<void(int, int)> dfs = [&](int v, int parent) {
        for (auto& e : g.adj[v]) {
            if (e.to == parent) continue;
            dist[e.to] = dist[v] + e.cost;
            dfs(e.to, v);
        }
    };

    dfs(start, -1);

    long long max_dist = 0;
    int farthest = start;
    for (int i = 0; i < g.n; i++) {
        if (dist[i] > max_dist) {
            max_dist = dist[i];
            farthest = i;
        }
    }

    return {farthest, max_dist};
}

// 木の直径（重みなし）
// 返り値: {直径の長さ, 端点1, 端点2}
tuple<int, int, int> tree_diameter_unweighted(Graph& g) {
    // 適当な点から最遠点を求める
    auto [v1, d1] = bfs_farthest(g, 0);
    // その点から最遠点を求める
    auto [v2, diameter] = bfs_farthest(g, v1);

    return {diameter, v1, v2};
}

// 木の直径（重み付き）
// 返り値: {直径の長さ, 端点1, 端点2}
tuple<long long, int, int> tree_diameter_weighted(Graph& g) {
    // 適当な点から最遠点を求める
    auto [v1, d1] = dfs_farthest(g, 0);
    // その点から最遠点を求める
    auto [v2, diameter] = dfs_farthest(g, v1);

    return {diameter, v1, v2};
}

// 木の直径上のパスを取得
vector<int> get_diameter_path(Graph& g, int start, int goal) {
    vector<int> path;
    vector<int> parent(g.n, -1);

    function<bool(int, int)> dfs = [&](int v, int p) {
        parent[v] = p;
        if (v == goal) {
            for (int cur = goal; cur != -1; cur = parent[cur]) {
                path.push_back(cur);
            }
            reverse(path.begin(), path.end());
            return true;
        }
        for (int next : g.adj_unweighted[v]) {
            if (next == p) continue;
            if (dfs(next, v)) return true;
        }
        return false;
    };

    dfs(start, -1);
    return path;
}

// 全点対最短距離の最大値（木の直径の別解法）
int tree_diameter_all_pairs(Graph& g) {
    int diameter = 0;

    for (int i = 0; i < g.n; i++) {
        vector<int> dist(g.n, -1);
        queue<int> q;
        dist[i] = 0;
        q.push(i);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int next : g.adj_unweighted[v]) {
                if (dist[next] == -1) {
                    dist[next] = dist[v] + 1;
                    q.push(next);
                    diameter = max(diameter, dist[next]);
                }
            }
        }
    }

    return diameter;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 重みなし木の直径
    cout << "例1: 重みなし木の直径" << endl;
    Graph g1(7);
    g1.add_unweighted_undirected_edge(0, 1);
    g1.add_unweighted_undirected_edge(1, 2);
    g1.add_unweighted_undirected_edge(1, 3);
    g1.add_unweighted_undirected_edge(3, 4);
    g1.add_unweighted_undirected_edge(3, 5);
    g1.add_unweighted_undirected_edge(5, 6);

    auto [diameter, v1, v2] = tree_diameter_unweighted(g1);
    cout << "直径: " << diameter << endl;
    cout << "端点: " << v1 << " - " << v2 << endl;

    vector<int> path = get_diameter_path(g1, v1, v2);
    cout << "直径上のパス: ";
    for (int i = 0; i < path.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << path[i];
    }
    cout << endl << endl;

    // 例2: 重み付き木の直径
    cout << "例2: 重み付き木の直径" << endl;
    Graph g2(5);
    g2.add_undirected_edge(0, 1, 3);
    g2.add_undirected_edge(1, 2, 4);
    g2.add_undirected_edge(1, 3, 2);
    g2.add_undirected_edge(3, 4, 5);

    auto [diameter2, u1, u2] = tree_diameter_weighted(g2);
    cout << "直径（重み付き）: " << diameter2 << endl;
    cout << "端点: " << u1 << " - " << u2 << endl;

    return 0;
}