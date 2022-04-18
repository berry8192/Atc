#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;
//using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

// 今回はトポロジカルソートが必要ない
vector<int> topological_sort(vector<vector<int>> &G, vector<int> &indegree, int V) {
    // トポロジカルソートを記録する配列
    vector<int> sorted_vertices;

    // 入次数が0の頂点を発見したら、処理待ち頂点としてキューに追加する
    queue<int> que;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            que.push(i);
        }
    }

    // キューが空になるまで、操作1~3を繰り返す
    while (que.empty() == false) {
        // キューの先頭の頂点を取り出す
        int v = que.front();
        que.pop();

        // その頂点と隣接している頂点の入次数を減らし、0になればキューに追加
        for (int i = 0; i < G[v].size(); i++) {
            int u = G[v][i];
            indegree[u] -= 1;
            if (indegree[u] == 0) que.push(u);
        }
        // 頂点vを配列の末尾に追加する 
        sorted_vertices.push_back(v);
    }

    // トポロジカルソートを返す
    return sorted_vertices;
}

int main(){
    // 頂点数と辺の本数
    int V, E;
    cin >> V >> E;

    // 隣接リストにより表現されるグラフ
    vector<vector<int>> G(V);
    // 頂点の入次数を記録する配列
    vector<int> indegree(V);
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
		u--;
		v--;
        G[u].push_back(v);
        indegree[v] += 1;
    }

    // トポロジカルソートする
    vector<int> sorted_vertices = topological_sort(G, indegree, V);

    // トポロジカルソートを出力
    for (int i = 0; i < sorted_vertices.size(); i++) {
        cout << sorted_vertices[i] << endl;
    }
 
	return 0;
}