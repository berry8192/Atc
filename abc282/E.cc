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

ll w[510][510];

int main(){

	int n, m;
	ll ans=0;
	cin>> n >> m;
	vector<ll> v(n), rem(n);
	mod=m;

	rep(i, n) cin >> v[i];

	rep(i, n){
		rep(j, n){
			w[i][j]=(modpow(v[i], v[j])+modpow(v[j], v[i]))%mod;
		}
	}

	rep(lp, n-1){
		ll mi=lmax;
		int midx;
		rep(i, n){
			ll ma=-1;
			if(rem[i]) continue;
			rep(j, n){
				if(i==j) continue;
				ma=max(w[i][j], ma);
			}
			if(ma<mi){
				mi=ma;
				midx=i;
			}
		}
		
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}