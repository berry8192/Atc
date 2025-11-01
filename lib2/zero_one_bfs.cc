// 0-1 BFS deque 最短経路 O(V+E)

#include <iostream>
#include <vector>
#include <deque>
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

// 0-1 BFS
// エッジのコストが0または1の場合の最短経路
vector<int> zero_one_bfs(Graph& g, int start) {
    const int INF = 1e9;
    vector<int> dist(g.n, INF);
    deque<int> dq;

    dist[start] = 0;
    dq.push_back(start);

    while (!dq.empty()) {
        int v = dq.front();
        dq.pop_front();

        for (auto& e : g.adj[v]) {
            if (dist[v] + e.cost < dist[e.to]) {
                dist[e.to] = dist[v] + e.cost;

                if (e.cost == 0) {
                    dq.push_front(e.to);  // コスト0なら前に追加
                } else {
                    dq.push_back(e.to);   // コスト1なら後ろに追加
                }
            }
        }
    }

    return dist;
}

// 0-1 BFS（経路復元付き）
pair<vector<int>, vector<int>> zero_one_bfs_with_path(Graph& g, int start) {
    const int INF = 1e9;
    vector<int> dist(g.n, INF);
    vector<int> prev(g.n, -1);
    deque<int> dq;

    dist[start] = 0;
    dq.push_back(start);

    while (!dq.empty()) {
        int v = dq.front();
        dq.pop_front();

        for (auto& e : g.adj[v]) {
            if (dist[v] + e.cost < dist[e.to]) {
                dist[e.to] = dist[v] + e.cost;
                prev[e.to] = v;

                if (e.cost == 0) {
                    dq.push_front(e.to);
                } else {
                    dq.push_back(e.to);
                }
            }
        }
    }

    return {dist, prev};
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な0-1 BFS
    cout << "例1: 0-1 BFS" << endl;
    Graph g1(6);
    g1.add_edge(0, 1, 0);
    g1.add_edge(0, 2, 1);
    g1.add_edge(1, 2, 1);
    g1.add_edge(1, 3, 0);
    g1.add_edge(2, 3, 1);
    g1.add_edge(2, 4, 0);
    g1.add_edge(3, 4, 1);
    g1.add_edge(3, 5, 1);
    g1.add_edge(4, 5, 0);

    vector<int> dist = zero_one_bfs(g1, 0);

    cout << "頂点0からの最短距離:" << endl;
    for (int i = 0; i < g1.n; i++) {
        cout << "  頂点" << i << ": " << dist[i] << endl;
    }
    cout << endl;

    // 例2: グリッドグラフでの応用
    cout << "例2: グリッドグラフ（壁を壊せる）" << endl;
    // 3x3グリッド、壁を壊すコスト1、移動コスト0
    Graph g2(9);  // 0-8の9マス

    // グリッドの隣接関係を構築
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int idx = i * 3 + j;

            // 右
            if (j < 2) {
                int right = i * 3 + (j + 1);
                // 壁がある場合はコスト1、ない場合は0
                int cost = (i == 1 && j == 0) ? 1 : 0;  // (1,0)-(1,1)間に壁
                g2.add_edge(idx, right, cost);
                g2.add_edge(right, idx, cost);
            }

            // 下
            if (i < 2) {
                int down = (i + 1) * 3 + j;
                int cost = (i == 0 && j == 1) ? 1 : 0;  // (0,1)-(1,1)間に壁
                g2.add_edge(idx, down, cost);
                g2.add_edge(down, idx, cost);
            }
        }
    }

    vector<int> dist2 = zero_one_bfs(g2, 0);
    cout << "左上(0)から各マスへの最小コスト:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << dist2[i * 3 + j] << " ";
        }
        cout << endl;
    }

    return 0;
}