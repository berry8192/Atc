#include <bits/stdc++.h>
using namespace std;

int n, m, ans=0; //n頂点　m辺
vector< vector<int> > g;
vector<int> seen;

void dfs(int x){
	if(seen[x]) return;
	seen[x]=1;

	for(int i=0;i<g[x].size();i++){
		dfs(g[x][i]);
	}
}

int main(){

	cin>> n >> m;

	g.resize(n+1);
	seen.resize(n+1, 0);

	for(int i=0;i<m;i++){
		int a, b;
		cin>> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);//有向グラフの場合はコメントアウト
	}

	dfs(1);
	
	for(int i=1;i<=n;i++){
		if(seen[i]) ans++;
	}

	cout<< ans <<endl;

	return 0;
}