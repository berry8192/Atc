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
map<poi, int> mp;

struct poi{
	int x1;
	int x2;

	bool operator<(const poi &in) const{
		return x1!=in.x1 ? x1<in.x1 : x2<in.x2;
	};
};

bool dl(int x, int y){
	if (g[x].size()==0){
		return false;
	}else if(g[x].size()==1){
		
}

int main(){

	int n, m, u, v;
	poi tmp;

	cin>> n >> m;
	g.resize(n+1);
	si.resize(n+1);

	rep(i, n){
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
		tmp.x1=u;
		tmp.x2=v;
		mp[tmp]=2;
		tmp.x1=v;
		tmp.x2=u;
		mp[tmp]=2;
	}

	rep(i, n) {
		if (g[i+1].size()==0){
			cout<< 0 <<endl;
			return 0;
		}else if(g[i+1].size()==1){
			dl(i+1, g[i+1][0]);
		}
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}