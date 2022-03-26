#include<bits/stdc++.h>

using namespace std;

using int64 = long long;
const int mod = 1e9 + 7;

const int64 infll = (1LL << 62) - 1;
const int inf = (1 << 30) - 1;

vector<vector<int>> re, g;
vector<int> cyc, dis;

void dfsr(int x){
	for(int i=0;i<re[x].size();i++){
		if(cyc[re[x][i]]) continue;
		cyc[re[x][i]]=1;
		dfsr(re[x][i]);
	}
}

void dfs(int x, int u){
	if(u==dis[x]){
		cyc[x]=1;
		dfsr(x);
	}
	//if(dis[x]!=0) return;
	dis[x]=u;
	for(int i=0;i<re[x].size();i++){
		if(cyc[re[x][i]]) continue;
		dfs(re[x][i], u);
	}
}

int main() {
    int N, M, ans=0, a, b;
    cin >> N >> M;
	cyc.resize(N+1);
	dis.resize(N+1);
	re.resize(N+1);
	g.resize(N+1);

	//cout<<"#" <<endl;
	for(int i=0;i<M;i++){
		cin>> a >> b;
		g[a].push_back(b);
		re[b].push_back(a);
	}
	//cout<<"#" <<endl;
	for(int i=1;i<=N;i++){
		dfs(i, i);
	}

	// for(int i=1;i<=N;i++){
	// 	if(cyc[i]) dfsr(i);
	// }
	for(int i=1;i<=N;i++){
		if(cyc[i]){
			ans++;
			//cout<< i <<endl;
		}
	}
	cout<< ans <<endl;
}