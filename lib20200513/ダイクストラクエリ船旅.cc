//https://atcoder.jp/contests/joi2008yo/tasks/joi2008yo_f
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
  	int n, k;
  	cin>> n >> k;
  	N=n;
  
  	for(int j=0;j<k;j++){
    	int d;
    	cin>> d;
    	if(d==0){
      		int a, b;
      		cin>> a >> b;
      
    		S=a;

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
      		if(dist[b]==imax) cout<< "-1" <<endl;
      		else cout<< dist[b] <<endl;
    	}else{
      		int a, b, c;
      		cin>> a >> b >> c;
        	G[a].push_back(make_pair(b, c));
        	G[b].push_back(make_pair(a, c));
    	}
  	}
    return 0;
}
