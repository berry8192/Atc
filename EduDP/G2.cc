#include <bits/stdc++.h>
using namespace std;

//N 頂点
//M 辺
//S 始点
//AとBの間のコストがC
//dist 視点からの距離リスト

long long llimax=9223372036854775807;
int N, M;
long long S, A[200009], B[200009], C[200009];
long long dist[200009], distr[200009];
vector<pair<long long, long long>> G[200009], Gr[200009];
priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> Q;
//N M ABC S

struct ed{
	long long u;
	long long v;
	long long w;

	bool operator<(const ed &in) const{
		return u!=in.u ? u<in.u : v!=in.v ? v<in.v : w>in.w;
	};
};

// 木の直径
int main() {
    // グラフを入力する
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= M; i++) {
		cin>> A[i] >> B[i];
        G[A[i]].push_back(make_pair(B[i], 1));
        Gr[B[i]].push_back(make_pair(A[i], 1));
    }
    S=1;

    // 距離を初期化する
    for (int i = 1; i <= N; i++) dist[i] = llimax;

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

	long long mad=0, mai;
	for(int i=1;i<=N;i++){
		if(dist[i]>mad){
			mai=i;
			mad=dist[i];
		}
	}

    S=mai;

    // 距離を初期化する
    for (int i = 1; i <= N; i++) distr[i] = llimax;

    // 優先度付きキューには (距離, 頂点番号) の組を入れる
    Q.push(make_pair(0, S));
    distr[S] = 0;
    while (!Q.empty()) {
        int pos = Q.top().second; Q.pop();
        for (int i = 0; i < Gr[pos].size(); i++) {
            int to = Gr[pos][i].first, cost = Gr[pos][i].second;
            if (distr[to] > distr[pos] + cost) {
                distr[to] = distr[pos] + cost;
                Q.push(make_pair(distr[to], to));
            }
        }
    }

    // 距離を出力する
    for (int i = 1; i <= N; i++){
		mad=max(mad, distr[i]);
    }

	cout<< mad <<endl;

    return 0;
}