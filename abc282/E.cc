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
ll mod;
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

ll modpow(ll a, ll n) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

//最大全域木、クラスカル法
//3 factor sort
struct ed{
	ll x1;
	int x2;
	int x3;

	bool operator<(const ed &in) const{
		return x1!=in.x1 ? x1>in.x1 : x2!=in.x2 ? x2<in.x2 : x3<in.x3;
	};
};

int main(){

	int n, m;
	ll ans=0;
	cin>> n >> m;
	vector<ll> v(n);
	vector<ed> edge;
	dsu d(n);
	mod=m;

	rep(i, n) cin >> v[i];

	rep(i, n){
		rep3(j, n, i+1){
			ed tmp;
			tmp.x1=(modpow(v[i], v[j])+modpow(v[j], v[i]))%mod;
			tmp.x2=i;
			tmp.x3=j;
			edge.push_back(tmp);
		}
	}

	sort(all(edge));

	rep(i, edge.size()){
		if(!d.same(edge[i].x2, edge[i].x3)){
			d.merge(edge[i].x2, edge[i].x3);
			ans+=edge[i].x1;
		}
	}

	cout<< ans << endl;
 
	return 0;
}