// 最小費用流 min_cost_flow 最小費用最大流 spfa

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

// ========== 最小費用流ライブラリ ==========

struct CostFlowEdge {
    int to, rev;
    long long cap, cost;
    CostFlowEdge(int to, long long cap, long long cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {}
};

struct MinCostFlow {
    vector<vector<CostFlowEdge>> graph;
    vector<long long> dist, h;
    vector<int> prev_v, prev_e;
    int n;

    MinCostFlow(int n) : n(n), graph(n), dist(n), h(n), prev_v(n), prev_e(n) {}

    // 容量cap、コストcostの辺を追加
    void add_edge(int from, int to, long long cap, long long cost) {
        graph[from].push_back(CostFlowEdge(to, cap, cost, graph[to].size()));
        graph[to].push_back(CostFlowEdge(from, 0, -cost, graph[from].size() - 1));
    }

    // 最小費用流を計算（流量flow_limitまで）
    pair<long long, long long> min_cost_flow(int s, int t, long long flow_limit) {
        long long total_cost = 0;
        long long total_flow = 0;
        fill(h.begin(), h.end(), 0);

        while (total_flow < flow_limit) {
            // Dijkstra法でポテンシャルを更新
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
            fill(dist.begin(), dist.end(), LLONG_MAX);
            dist[s] = 0;
            pq.push({0, s});

            while (!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if (dist[v] < d) continue;

                for (int i = 0; i < graph[v].size(); i++) {
                    CostFlowEdge& e = graph[v][i];
                    if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                        dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                        prev_v[e.to] = v;
                        prev_e[e.to] = i;
                        pq.push({dist[e.to], e.to});
                    }
                }
            }

            if (dist[t] == LLONG_MAX) break;

            // ポテンシャルを更新
            for (int v = 0; v < n; v++) {
                if (dist[v] < LLONG_MAX) {
                    h[v] += dist[v];
                }
            }

            // s-t間の最短経路で流せる最大流量を計算
            long long augment = flow_limit - total_flow;
            for (int v = t; v != s; v = prev_v[v]) {
                augment = min(augment, graph[prev_v[v]][prev_e[v]].cap);
            }

            // 流量を流す
            for (int v = t; v != s; v = prev_v[v]) {
                CostFlowEdge& e = graph[prev_v[v]][prev_e[v]];
                e.cap -= augment;
                graph[v][e.rev].cap += augment;
            }

            total_flow += augment;
            total_cost += augment * h[t];
        }

        return {total_flow, total_cost};
    }

    // 最小費用最大流を計算
    pair<long long, long long> min_cost_max_flow(int s, int t) {
        return min_cost_flow(s, t, LLONG_MAX);
    }

    // 指定した流量での最小費用を計算
    long long min_cost_for_flow(int s, int t, long long required_flow) {
        auto [flow, cost] = min_cost_flow(s, t, required_flow);
        if (flow < required_flow) return -1;  // 不可能
        return cost;
    }

    // 単位流量あたりの費用を取得
    vector<long long> get_marginal_costs(int s, int t, long long max_flow) {
        vector<long long> costs;
        long long current_flow = 0;
        long long current_cost = 0;
        fill(h.begin(), h.end(), 0);

        while (current_flow < max_flow) {
            // 現在の最短経路を見つける
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
            fill(dist.begin(), dist.end(), LLONG_MAX);
            dist[s] = 0;
            pq.push({0, s});

            while (!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if (dist[v] < d) continue;

                for (int i = 0; i < graph[v].size(); i++) {
                    CostFlowEdge& e = graph[v][i];
                    if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                        dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                        prev_v[e.to] = v;
                        prev_e[e.to] = i;
                        pq.push({dist[e.to], e.to});
                    }
                }
            }

            if (dist[t] == LLONG_MAX) break;

            // ポテンシャルを更新
            for (int v = 0; v < n; v++) {
                if (dist[v] < LLONG_MAX) {
                    h[v] += dist[v];
                }
            }

            long long marginal_cost = h[t];
            costs.push_back(marginal_cost);

            // 1単位の流量を流す
            long long augment = min(1LL, max_flow - current_flow);
            for (int v = t; v != s; v = prev_v[v]) {
                augment = min(augment, graph[prev_v[v]][prev_e[v]].cap);
            }

            for (int v = t; v != s; v = prev_v[v]) {
                CostFlowEdge& e = graph[prev_v[v]][prev_e[v]];
                e.cap -= augment;
                graph[v][e.rev].cap += augment;
            }

            current_flow += augment;
            current_cost += augment * marginal_cost;
        }

        return costs;
    }
};

// ========== サンプルコード ==========

int main() {
    cout << "例1: 基本的な最小費用流" << endl;
    MinCostFlow mcf1(4);

    // 各辺の容量とコストを設定
    mcf1.add_edge(0, 1, 2, 1);  // 0->1: 容量2, コスト1
    mcf1.add_edge(0, 2, 1, 2);  // 0->2: 容量1, コスト2
    mcf1.add_edge(1, 2, 1, 1);  // 1->2: 容量1, コスト1
    mcf1.add_edge(1, 3, 1, 3);  // 1->3: 容量1, コスト3
    mcf1.add_edge(2, 3, 2, 1);  // 2->3: 容量2, コスト1

    auto [max_flow, min_cost] = mcf1.min_cost_max_flow(0, 3);
    cout << "最大流量: " << max_flow << endl;
    cout << "最小費用: " << min_cost << endl;
    cout << endl;

    cout << "例2: 指定流量での最小費用" << endl;
    MinCostFlow mcf2(4);

    mcf2.add_edge(0, 1, 3, 2);
    mcf2.add_edge(0, 2, 2, 1);
    mcf2.add_edge(1, 3, 2, 1);
    mcf2.add_edge(2, 3, 3, 3);

    for (int flow = 1; flow <= 3; flow++) {
        long long cost = mcf2.min_cost_for_flow(0, 3, flow);
        if (cost >= 0) {
            cout << "流量" << flow << "での最小費用: " << cost << endl;
        } else {
            cout << "流量" << flow << "は実現不可能" << endl;
        }
    }
    cout << endl;

    cout << "例3: 輸送問題（供給と需要）" << endl;
    // 供給地2つ（容量3, 2）、需要地2つ（需要2, 3）
    MinCostFlow mcf3(6);  // ソース0、供給地1,2、需要地3,4、シンク5

    // ソースから供給地への容量
    mcf3.add_edge(0, 1, 3, 0);  // 供給地1の容量3
    mcf3.add_edge(0, 2, 2, 0);  // 供給地2の容量2

    // 供給地から需要地への輸送コスト
    mcf3.add_edge(1, 3, 5, 2);  // 供給地1->需要地3: コスト2
    mcf3.add_edge(1, 4, 5, 3);  // 供給地1->需要地4: コスト3
    mcf3.add_edge(2, 3, 5, 1);  // 供給地2->需要地3: コスト1
    mcf3.add_edge(2, 4, 5, 4);  // 供給地2->需要地4: コスト4

    // 需要地からシンクへの需要
    mcf3.add_edge(3, 5, 2, 0);  // 需要地3の需要2
    mcf3.add_edge(4, 5, 3, 0);  // 需要地4の需要3

    auto [transport_flow, transport_cost] = mcf3.min_cost_max_flow(0, 5);
    cout << "輸送量: " << transport_flow << endl;
    cout << "総輸送費用: " << transport_cost << endl;

    return 0;
}