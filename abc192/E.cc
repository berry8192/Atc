#include <bits/stdc++.h>
using namespace std;

#define LLi long long int
long long int llimax=9223372036854775807;

struct pos{
	int ob;
	LLi t;
	LLi k;
};

int n, m, x, y, ans=0; //n頂点　m辺
vector< vector<pos> > g;
vector<LLi> dis;
queue<int> q;
//vector<int> seen;


int main(){

	cin>> n >> m >> x >> y;

	g.resize(n+1);
	dis.resize(n+1, llimax);
	//seen.resize(n+1, 0);

	for(int i=0;i<m;i++){
		int a, b;
		LLi it, ik;
		pos tmp;

		cin>> a >> b >> it >> ik;
		tmp.ob=b;
		tmp.t=it;
		tmp.k=ik;
		g[a].push_back(tmp);
		tmp.ob=a;
		g[b].push_back(tmp);//有向グラフの場合はコメントアウト
	}

	q.push(x);
	dis[x]=0;
  	while (!q.empty()) {
		int tmpf=q.front();
		q.pop();
		for(int i=0;i<g[tmpf].size();i++){
			if(dis[g[tmpf][i].ob]<=((dis[tmpf]+g[tmpf][i].k-1)/g[tmpf][i].k)*g[tmpf][i].k+g[tmpf][i].t) continue;
			q.push(g[tmpf][i].ob);
			dis[g[tmpf][i].ob]=((dis[tmpf]+g[tmpf][i].k-1)/g[tmpf][i].k)*g[tmpf][i].k+g[tmpf][i].t;
		}
  	}

	//for(int i=1;i<=n;i++){
		if(dis[y]==llimax) cout<< -1 <<endl;
		else cout<< dis[y] <<endl;
	//}

	return 0;
}