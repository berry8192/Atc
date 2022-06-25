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

//3 factor sort
struct ed{
	ll x1;
	ll x2;
	ll x3;

	bool operator<(const ed &in) const{
		return x1!=in.x1 ? x1<in.x1 : x2!=in.x2 ? x2<in.x2 : x3<in.x3;
	};
};

int main(){

	ll n, flag2=0;
	vector<ll> x, y, p;
	vector<ed> v;
	queue<ll> q;

	cin>> n;
	x.resize(n);
	y.resize(n);
	p.resize(n);

	rep(i, n) cin >> x[i] >> y[i] >> p[i];

	rep(i, n) {
		rep(j, n){
			ed tmp;
			ll dis=abs(x[i]-x[j])+abs(y[i]-y[j]);
			if(dis%p[i]==0) tmp.x1=dis/p[i];
			else tmp.x1=(dis+p[i]-1)/p[i];
			tmp.x2=i+1;
			tmp.x3=j+1;
			v.push_back(tmp);
		}
	}

	sort(all(v));
	//rep(i, v.size()) cout<< v[i].x1 SP << v[i].x2 SP << v[i].x3 <<endl;

	ll le=0, ri=5000000000, mi;
	while(ri-le>1){
		flag2=0;
		mi=(le+ri)/2;
		vector<vector<ll>> g(n+1);
		rep(i, v.size()){
			if(v[i].x1<=mi) g[v[i].x2].push_back(v[i].x3);
		}
		rep3(j, n+1, 1){
			q.push(j);
			vector<ll> seen(n+1); 
			while(!q.empty()){
				ll p=q.front();
				q.pop();
				seen[p]=1;
				rep(k, g[p].size()){
					if(!seen[g[p][k]]) q.push(g[p][k]);
				}
			}
			ll flag=1;
			rep3(k, n+1, 1){
				if(seen[k]==0){
					flag=0;
					break;
				}
			}
			if(flag){
				flag2=1;
				break;
			}
		}
		if(flag2) ri=mi;
		else le=mi;
	}

	cout<< ri << endl;
 
	return 0;
}