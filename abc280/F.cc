#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
using namespace atcoder;

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

struct edge{
	int to;
	ll c;
};

int n, m, q;
vector<ll> a, b, c, x, y, dis, seen, lp;
vector<vector<edge>> gra;

void dfs(int x, int led, ll sco){
	if(seen[x]){
		if(dis[x]!=sco){
			lp[led]=1;
		}
		return;
	}
	seen[x]=1;
	dis[x]=sco;
	rep(i, gra[x].size()){
		dfs(gra[x][i].to, led, sco+gra[x][i].c);
	}
}

int main(){
	cin>> n >> m >> q;
	a.resize(m);
	b.resize(m);
	c.resize(m);
	x.resize(q);
	y.resize(q);
	dis.resize(n);
	seen.resize(n);
	lp.resize(n);
	gra.resize(n);
	dsu g(n);

	rep(i, m){
		cin >> a[i] >> b[i] >> c[i];
		a[i]--;
		b[i]--;
		edge tmp;
		tmp.to=b[i];
		tmp.c=c[i];
		gra[a[i]].push_back(tmp);
		tmp.to=a[i];
		tmp.c=-c[i];
		gra[b[i]].push_back(tmp);
		g.merge(a[i], b[i]);
	}

	rep(i, n){
		int led=g.leader(i);
		if(seen[led]) continue;
		dfs(led, led, 0LL);
	}

	rep(i, q) {
		cin>> x[i] >> y[i];
		x[i]--;
		y[i]--;
		if(g.same(x[i], y[i])){
			if(lp[g.leader(x[i])]){
				cout<< "inf" <<endl;
			}else{
				cout<< dis[y[i]]-dis[x[i]] <<endl;
			}
		}else{
			cout<< "nan" <<endl;
		}
	}

	return 0;
}