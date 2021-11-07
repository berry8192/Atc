#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
//LLi mod=1000000007;
LLi mod=998244353;

vector< vector<int> > g;
vector<int> seen;
int x, y;

void dfs(int k){
	seen[k]=1;
	x++;
	y+=g[k].size();
	rep(i, g[k].size()){
		if(seen[g[k][i]]==0) dfs(g[k][i]);
	}
	return;
}

int main(){

	int n, m, u, v;
	LLi ans=1;

	cin>> n >> m;
	g.resize(n+1);
	seen.resize(n+1);

	rep(i, m){
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	rep(i, n) {
		if (seen[i+1]==0){
			x=0;
			y=0;
			dfs(i+1);
			if(y==2*x) ans=(ans*2)%mod;
			else{
				cout<< 0 <<endl;
				return 0;
			}
		}
	}

	cout<< ans << endl;
 
	return 0;
}