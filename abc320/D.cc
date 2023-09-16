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

struct Pos{
	ll to;
    ll h;
    ll w;

    Pos(){};
    Pos(ll ito, ll hh, ll ww){
		to=ito;
        h=hh;
        w=ww;
    }

	Pos operator+(const Pos pos){
        Pos rtn;
		rtn.to=to+pos.to;
        rtn.h=h+pos.h;
        rtn.w=w+pos.w;
        return rtn;
    }
	void print(){
		cout<< h SP << w <<endl;
	}
};

int main(){

	ll n, m;
	cin>> n >> m;
	vector<ll> a(m), b(m), x(m), y(m);
	dsu d(n);
	vector<vector<Pos>> g(n);

	rep(i, m){
		cin >> a[i] >> b[i] >> x[i] >> y[i];
		a[i]--;
		b[i]--;
		d.merge(a[i], b[i]);
		g[a[i]].push_back({b[i], x[i], y[i]});
		g[b[i]].push_back({a[i], -x[i], -y[i]});
	}
	// if(d.size(0)!=n){
	// 	cout<< "undecidable " <<endl;
	// 	return 0;
	// }
	vector<Pos> seen(n, Pos(0, 0, 0));
	seen[0]={1, 0, 0};
	queue<Pos> q;
	q.push({0, 0, 0});
	while(!q.empty()){
		Pos pos=q.front();
		q.pop();
		rep(i, g[pos.to].size()){
			if(seen[g[pos.to][i].to].to!=0LL) continue;
			Pos npos=pos+g[pos.to][i];
			seen[g[pos.to][i].to]={1, npos.h, npos.w};
			q.push({g[pos.to][i].to, npos.h, npos.w});
		}
	}

	rep(i, n){
		if(seen[i].to!=0) seen[i].print();
		else cout<< "undecidable " << endl;
	}

	return 0;
}