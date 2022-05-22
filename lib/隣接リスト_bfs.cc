#include <bits/stdc++.h>
using namespace std;

int n, m, ans=0; //n頂点　m辺
vector< vector<int> > g;
vector<int> dis;
queue<int> q;
//vector<int> seen;

int main(){

	cin>> n >> m;

	g.resize(n+1);
	dis.resize(n+1, 9999999);
	//seen.resize(n+1, 0);

	for(int i=0;i<m;i++){
		int a, b;
		cin>> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);//有向グラフの場合はコメントアウト
	}

	q.push(1);
	dis[1]=0;
  	while (!q.empty()) {
		int tmpf=q.front();
		q.pop();
		for(int i=0;i<g[tmpf].size();i++){
			if(dis[g[tmpf][i]]<=dis[tmpf]+1) continue;
			q.push(g[tmpf][i]);
			dis[g[tmpf][i]]=dis[tmpf]+1;
		}
  	}

	for(int i=1;i<=n;i++){
		if(dis[i]==9999999) cout<< "x" <<endl;
		else cout<< dis[i] <<endl;
	}

	cout<< ans <<endl;

	return 0;
}