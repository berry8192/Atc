#include <bits/stdc++.h>
using namespace std;

//N 頂点
//M 辺
//S 始点
//AとBの間のコストがC
//dist 視点からの距離リスト

int imax=2147483647;
int N, M, S, A[500009], B[500009], C[500009];
int dist[100009];
vector<pair<int, int>> G[100009];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
//N M ABC S

int main() {
    // グラフを入力する
    scanf("%d", &N);
	M=N-1;
    for (int i = 1; i <= M; i++) {
        scanf("%d%d", &A[i], &B[i]);
        G[A[i]].push_back(make_pair(B[i], 1));
        G[B[i]].push_back(make_pair(A[i], 1));
    }
    //scanf("%d", &S);
	S=1;

    // 距離を初期化する
    for (int i = 1; i <= N; i++) dist[i] = imax;

    // 優先度付きキューには (距離, 頂点番号) の組を入れる
    Q.push(make_pair(0, S));
    dist[S] = 0;
    while (!Q.empty()) {
        int pos = Q.top().second; Q.pop();
        for (int i = 0; i < G[pos].size(); i++) {
            int to = G[pos][i].first, cost = G[pos][i].second;
            if (dist[to] > dist[pos] + cost) {
                dist[to] = dist[pos] + cost;
                Q.push(make_pair(dist[to], to));
            }
        }
    }

	vector<int> a, b;

    // 距離を出力する
    for (int i = 1; i <= N; i++){
		if(dist[i]%2) a.push_back(i);
		else b.push_back(i);
    }

	if(a.size()<b.size()) swap(a, b);
	for(int i=0;i<N/2;i++) cout<< a[i] << " ";
	cout<< endl;

    return 0;
}