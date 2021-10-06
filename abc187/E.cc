#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

//N 頂点
//M 辺
//S 始点
//AとBの間のコストがC
//dist 視点からの距離リスト

LLi imax=2147483647;
LLi N, M, S, A[500009], B[500009], C[500009];
LLi dist[100009];
vector<pair<LLi, LLi>> G[100009];
priority_queue<pair<LLi, LLi>, vector<pair<LLi, LLi>>, greater<pair<LLi, LLi>>> Q;
//N M ABC S
	vector< vector<int> > g;
	g.resize(N+1);

void dfs(int x){
	//if(seen[x]) return;
	//seen[x]=1;

	for(int i=0;i<g[x].size();i++){
		dfs(g[x][i]);
	}
}

int main() {
    // グラフを入力する
    scanf("%d", &N);
	M=N-1;
    for (int i = 1; i <= M; i++) {
        scanf("%d%d%d", &A[i], &B[i], &C[i]);
		g[a].push_back(b);
		g[b].push_back(a);
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
            LLi to = G[pos][i].first, cost = G[pos][i].second;
            if (dist[to] > dist[pos] + cost) {
                dist[to] = dist[pos] + cost;
                Q.push(make_pair(dist[to], to));
            }
        }
    }

    // 距離を出力する
    for (int i = 1; i <= N; i++){
		if(dist[i]==imax) cout<< "-1" <<endl;
		else cout<< dist[i] <<endl;
    }

	int q, t, e, x, s, g;
	LLi hv=0;
	vector<int> sc;
	sc.resize(N+1);
  	stack<int> st;
	cin>> q;

	for(int i=0;i<q;i++){
		cin>> t >> e >> x;
		if(t==1){
			s=A[e];
			g=B[e];
		}else{
			s=B[e];
			g=A[e];
		}
		if(dist[s]<dist[g]) hv+=x;

	}

	st.push(1);
	while (!st.empty()) {
        int pos = st.top();
		Q.pop();
        for (int i = 0; i < G[pos].size(); i++) {
            int to = G[pos][i].first, cost = G[pos][i].second;
            if (dist[to] > dist[pos] + cost) {
                dist[to] = dist[pos] + cost;
                Q.push(make_pair(dist[to], to));
            }
        }
    }


    return 0;
}