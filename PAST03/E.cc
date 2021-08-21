#include <bits/stdc++.h>
using namespace std;

int n, m, ans=0; //n頂点　m辺
vector< vector<int> > g;
vector< int > cl;

void dfs(int x){
	for(int i=0;i<g[x].size();i++){
		cl[g[x][i]]=cl[x];
	}
}

int main(){

	int q, tmp;
	int a, b;
	cin>> n >> m >> q;

	g.resize(n+1);
	cl.resize(n+1);

	for(int i=0;i<m;i++){
		int a, b;
		cin>> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);//有向グラフの場合はコメントアウト
	}

	for(int i=0;i<n;i++) cin>> cl[i+1];

	for(int i=0;i<q;i++){
		cin>> tmp;
		cin>> a;

		cout<< cl[a] <<endl;

		if(tmp==2){
			cin>> b;
			cl[a]=b;
		}else{
			dfs(a);
		}
	}

	return 0;
}