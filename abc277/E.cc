#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

struct path{
	int to;
	int a;
};

int main(){

	int n, m, k, tmp;
	vector<int> u, v, a, s;
	vector<vector<ll>> dist;
	queue<int> qx, qa;
	vector<vector<path>> g;

	cin>> n >> m >> k;
	u.resize(m);
	v.resize(m);
	a.resize(m);
	s.resize(n+1);
	dist.resize(n+1, vector<ll>(2, lmax));
	g.resize(n+1);

	rep(i, m){
		cin >> u[i] >> v[i] >> a[i];
		g[u[i]].push_back({v[i], a[i]});
		g[v[i]].push_back({u[i], a[i]});
	}
	rep(i, k){
		cin>> tmp;
		s[tmp]=1;
	}

	qx.push(1);
	qa.push(1);
	dist[1][1]=0;
	
	while(!qa.empty()){
		int xx=qx.front();
		int aa=qa.front();
		qx.pop();
		qa.pop();
		// cout<< "xx:" << xx SP << "aa:" << aa <<endl;
		if(s[xx]){
			dist[xx][0]=min(dist[xx][0], dist[xx][1]);
			dist[xx][1]=min(dist[xx][0], dist[xx][1]);
		}
		rep(i, g[xx].size()){
			if(g[xx][i].a==aa || s[xx]){
				if(dist[g[xx][i].to][g[xx][i].a]!=lmax) continue;
				dist[g[xx][i].to][g[xx][i].a]=dist[xx][g[xx][i].a]+1;
				qx.push(g[xx][i].to);
				qa.push(g[xx][i].a);
			}
		}
	}

	// rep(i, n){
	// 	cout<< dist[i+1][0] SP << dist[i+1][1] <<endl;
	// }
	ll ans=min(dist[n][0], dist[n][1]);
	if(ans!=lmax) cout<< min(dist[n][0], dist[n][1]) << endl;
	else cout<< -1 <<endl;
 
	return 0;
}