#include <bits/stdc++.h>
using namespace std;

int n, m, ans=0; //n頂点　m辺
vector< vector<long long int> > g;
//vector<int> dis;
queue<int> q;
vector<int> seen;
long long int ni=1000000000;

int main(){

	cin>> n >> m;

	g.resize(n+1);
	//dis.resize(n+1, 9999999);
	seen.resize(n+1, 0);

	for(int i=0;i<m;i++){
		int a, b, c;
		cin>> a >> b >> c;
		g[a].push_back(b+ni*c);
		g[b].push_back(a+ni*c);//有向グラフの場合はコメントアウト
	}

	for(int i=2;i<=n;i++) {
		if(g[i].size()==1){
			seen[i]==g[i][0]/ni;
			q.push(g[i][0]%ni);
		}
	}

	q.push(1);
	seen[1]=g[1][0]/ni;
	//dis[1]=0;
  	while (!q.empty()) {
		int tmpf=q.front()%ni;
		//cout<< tmpf <<endl;
		q.pop();
		for(int i=0;i<g[tmpf].size();i++){
			//cout<< seen[g[tmpf][i]%ni] <<endl;
			if(seen[g[tmpf][i]%ni]){
				continue;
			}
			q.push(g[tmpf][i]%ni);
			seen[g[tmpf][i]%ni]=g[tmpf][i]/ni;
			//cout<< tmpf << " " << g[tmpf][i]%ni <<endl;
		}
  	}

	for(int i=1;i<=n;i++) cout<< seen[i] <<endl;

	return 0;
}