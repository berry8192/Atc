// 最大流 max_flow ford_fulkerson dinic edmonds_karp

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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

// ========== 最大流ライブラリ ==========

struct FlowEdge {
    int to, rev;
    long long cap;
    FlowEdge(int to, long long cap, int rev) : to(to), cap(cap), rev(rev) {}
};

struct MaxFlow {
    vector<vector<FlowEdge>> graph;
    vector<int> level, iter;
    int n;

    MaxFlow(int n) : n(n), graph(n), level(n), iter(n) {}

    // 容量capの辺を追加
    void add_edge(int from, int to, long long cap) {
        graph[from].push_back(FlowEdge(to, cap, graph[to].size()));
        graph[to].push_back(FlowEdge(from, 0, graph[from].size() - 1));
    }

    // Dinic's algorithmのBFS部分
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto& e : graph[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }

        return level[t] >= 0;
    }

    // Dinic's algorithmのDFS部分
    long long dfs(int v, int t, long long f) {
        if (v == t) return f;

        for (int& i = iter[v]; i < graph[v].size(); i++) {
            FlowEdge& e = graph[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                long long d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    // 最大流を計算（Dinic's algorithm）
    long long max_flow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            long long f;
            while ((f = dfs(s, t, LLONG_MAX)) > 0) {
                flow += f;
            }
        }
        return flow;
    }

    // 最小カットを取得
    vector<bool> min_cut(int s) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto& e : graph[v]) {
                if (e.cap > 0 && !visited[e.to]) {
                    visited[e.to] = true;
                    q.push(e.to);
                }
            }
        }

        return visited;
    }

    // エッジの残余容量を取得
    long long get_residual_capacity(int from, int edge_idx) {
        return graph[from][edge_idx].cap;
    }

    // 現在の流量を取得
    long long get_flow(int from, int edge_idx, long long original_cap) {
        return original_cap - graph[from][edge_idx].cap;
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: 基本的な最大流問題" << endl;
    MaxFlow mf1(6);

    // ソース0からシンク5への最大流
    mf1.add_edge(0, 1, 16);
    mf1.add_edge(0, 2, 13);
    mf1.add_edge(1, 2, 10);
    mf1.add_edge(1, 3, 12);
    mf1.add_edge(2, 1, 4);
    mf1.add_edge(2, 4, 14);
    mf1.add_edge(3, 2, 9);
    mf1.add_edge(3, 5, 20);
    mf1.add_edge(4, 3, 7);
    mf1.add_edge(4, 5, 4);

    long long max_flow_value = mf1.max_flow(0, 5);
    cout << "最大流量: " << max_flow_value << endl;

    // 最小カットを表示
    vector<bool> cut = mf1.min_cut(0);
    cout << "最小カット（ソース側の頂点）: ";
    for (int i = 0; i < 6; i++) {
        if (cut[i]) cout << i << " ";
    }
    cout << endl;
    cout << "最小カット（シンク側の頂点）: ";
    for (int i = 0; i < 6; i++) {
        if (!cut[i]) cout << i << " ";
    }
    cout << endl << endl;

    cout << "例2: 二部グラフの最大マッチング" << endl;
    // 左側3頂点、右側3頂点の二部グラフ
    // 頂点0がソース、頂点7がシンク
    // 左側: 1, 2, 3  右側: 4, 5, 6
    MaxFlow mf2(8);

    // ソースから左側への容量1の辺
    mf2.add_edge(0, 1, 1);
    mf2.add_edge(0, 2, 1);
    mf2.add_edge(0, 3, 1);

    // 左側から右側への容量1の辺（マッチング可能な組み合わせ）
    mf2.add_edge(1, 4, 1);  // 左1 - 右4
    mf2.add_edge(1, 5, 1);  // 左1 - 右5
    mf2.add_edge(2, 5, 1);  // 左2 - 右5
    mf2.add_edge(2, 6, 1);  // 左2 - 右6
    mf2.add_edge(3, 6, 1);  // 左3 - 右6

    // 右側からシンクへの容量1の辺
    mf2.add_edge(4, 7, 1);
    mf2.add_edge(5, 7, 1);
    mf2.add_edge(6, 7, 1);

    long long matching = mf2.max_flow(0, 7);
    cout << "最大マッチング数: " << matching << endl;
    cout << endl;

    cout << "例3: 容量制約のあるネットワーク" << endl;
    MaxFlow mf3(4);

    mf3.add_edge(0, 1, 3);
    mf3.add_edge(0, 2, 2);
    mf3.add_edge(1, 2, 2);
    mf3.add_edge(1, 3, 2);
    mf3.add_edge(2, 3, 3);

    cout << "各辺の容量:" << endl;
    cout << "0->1: 3, 0->2: 2, 1->2: 2, 1->3: 2, 2->3: 3" << endl;

    long long max_flow_3 = mf3.max_flow(0, 3);
    cout << "0から3への最大流量: " << max_flow_3 << endl;

    return 0;
}