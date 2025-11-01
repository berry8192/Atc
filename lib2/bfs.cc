// BFS 幅優先探索 shortest_path O(V+E)

#include <iostream>
#include <vector>
#include <queue>
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

// BFSによる単一始点最短距離
// 重みなしグラフ（全エッジのコスト1）での最短距離
vector<int> bfs(Graph& g, int start) {
    vector<int> dist(g.n, -1);
    queue<int> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int next : g.adj_unweighted[v]) {
            if (dist[next] == -1) {
                dist[next] = dist[v] + 1;
                q.push(next);
            }
        }
    }

    return dist;
}

// BFSによる経路復元付き最短距離
pair<vector<int>, vector<int>> bfs_with_path(Graph& g, int start) {
    vector<int> dist(g.n, -1);
    vector<int> prev(g.n, -1);
    queue<int> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int next : g.adj_unweighted[v]) {
            if (dist[next] == -1) {
                dist[next] = dist[v] + 1;
                prev[next] = v;
                q.push(next);
            }
        }
    }

    return {dist, prev};
}

// 2頂点間の最短経路を復元
vector<int> get_path(const vector<int>& prev, int goal) {
    vector<int> path;
    for (int v = goal; v != -1; v = prev[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

// 多始点BFS（複数の始点から同時にBFS）
vector<int> multi_source_bfs(Graph& g, const vector<int>& starts) {
    vector<int> dist(g.n, -1);
    queue<int> q;

    for (int s : starts) {
        dist[s] = 0;
        q.push(s);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int next : g.adj_unweighted[v]) {
            if (dist[next] == -1) {
                dist[next] = dist[v] + 1;
                q.push(next);
            }
        }
    }

    return dist;
}

// 二部グラフ判定
// 返り値: {二部グラフか, 色分け配列}
pair<bool, vector<int>> is_bipartite(Graph& g) {
    vector<int> color(g.n, -1);

    for (int start = 0; start < g.n; start++) {
        if (color[start] != -1) continue;

        queue<int> q;
        color[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int next : g.adj_unweighted[v]) {
                if (color[next] == -1) {
                    color[next] = 1 - color[v];
                    q.push(next);
                } else if (color[next] == color[v]) {
                    return {false, vector<int>()};
                }
            }
        }
    }

    return {true, color};
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的なBFS
    cout << "例1: 基本的なBFS" << endl;
    Graph g1(6);
    g1.add_unweighted_undirected_edge(0, 1);
    g1.add_unweighted_undirected_edge(0, 2);
    g1.add_unweighted_undirected_edge(1, 3);
    g1.add_unweighted_undirected_edge(2, 3);
    g1.add_unweighted_undirected_edge(2, 4);
    g1.add_unweighted_undirected_edge(3, 5);
    g1.add_unweighted_undirected_edge(4, 5);

    vector<int> dist = bfs(g1, 0);
    cout << "頂点0からの距離:" << endl;
    for (int i = 0; i < g1.n; i++) {
        cout << "  頂点" << i << ": " << dist[i] << endl;
    }
    cout << endl;

    // 例2: 経路復元
    cout << "例2: 経路復元" << endl;
    auto [dist2, prev] = bfs_with_path(g1, 0);
    vector<int> path = get_path(prev, 5);
    cout << "頂点0から頂点5への最短経路: ";
    for (int i = 0; i < path.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << path[i];
    }
    cout << endl;
    cout << "距離: " << dist2[5] << endl << endl;

    // 例3: 二部グラフ判定
    cout << "例3: 二部グラフ判定" << endl;
    Graph g2(4);
    g2.add_unweighted_undirected_edge(0, 1);
    g2.add_unweighted_undirected_edge(1, 2);
    g2.add_unweighted_undirected_edge(2, 3);
    g2.add_unweighted_undirected_edge(3, 0);

    auto [is_bip, color] = is_bipartite(g2);
    if (is_bip) {
        cout << "二部グラフです" << endl;
        cout << "色分け: ";
        for (int c : color) cout << c << " ";
        cout << endl;
    } else {
        cout << "二部グラフではありません" << endl;
    }

    return 0;
}