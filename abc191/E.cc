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
    scanf("%d%d", &N, &M);
	
	vector< vector<int> > v;
	vector<int> a, b, c, ow;
	v.resize(N+1);
	ow.resize(N+1, imax);
	for(int i=0;i<N+1;i++) v[i].resize(N+1, imax);

    for (int i = 0; i < M; i++) {
        scanf("%d%d%d", &A[i], &B[i], &C[i]);
		if(A[i]!=B[i]) v[A[i]][B[i]]=min(v[A[i]][B[i]], C[i]);
		else ow[A[i]]=min(ow[A[i]], C[i]);
	}

	for(int i=1;i<N+1;i++){
		for(int j=1;j<N+1;j++){
			if(v[i][j]!=imax){
				a.push_back(i);
				b.push_back(j);
				c.push_back(v[i][j]);
				//cout<< i << " " << j << " " << v[i][j] <<endl;
			}
		}
	}

    for (int i = 0; i < a.size(); i++) {
        //scanf("%d%d%d", &A[i], &B[i], &C[i]);
        G[a[i]].push_back(make_pair(b[i], c[i]));
        //G[B[i]].push_back(make_pair(A[i], C[i]));
    }
    scanf("%d", &S);

    // 距離を初期化する
	for(int j=0;j<N;j++){
		for (int i = 1; i <= N; i++) dist[i] = imax;
		S=j+1;
		// 優先度付きキューには (距離, 頂点番号) の組を入れる
		Q.push(make_pair(0, S));
		dist[S] = 0;
		while (!Q.empty()) {
			int pos = Q.top().second; Q.pop();
			for (int i = 0; i < G[pos].size(); i++) {
				int to = G[pos][i].first, cost = G[pos][i].second;
				if (dist[to] > dist[pos] + cost || dist[pos]==0 || dist[to]==0) {
					dist[to] = dist[pos] + cost;
					Q.push(make_pair(dist[to], to));
				}
			}
		}

		// 距離を出力する
		/*for (int i = 1; i <= N; i++){
			if(dist[i]==imax) cout<< "-1" <<endl;
			else cout<< dist[i] <<endl;
		}*/
		if(dist[S]==0) dist[S]=imax;
		if(dist[S]==imax && ow[S]==imax) cout<< -1 <<endl;
		else cout<< min(ow[S], dist[S]) <<endl;
	}
    return 0;
}