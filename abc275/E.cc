#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
// using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
// using mint = modint998244353;
ll mod=998244353;

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
 
ll modinv(ll a) {
    ll b = mod, u = 1, v = 0;
    while (b) {
        ll t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= mod;
    if (u < 0) u += mod;
    return u;
}

int main(){

	int n, m, k;
	// mint mm;
	// mm=m;
	vector<ll> v(1020), v2(1020, 1);
	// vector<mint> v(1020);

	cin>> n >> m >> k;
	v[0]=1;

	rep(i, k){
		vector<ll> tmp(1020), tmp2(1020, 1);
		// vector<mint> tmp(1020);
		rep(j, n){
			if(v[j]==0) continue;
			rep3(l, m+1, 1){
				tmp[j+l]=((tmp[j+l]*v2[j])%mod+(tmp2[j+l]*v[j])%mod)%mod;
				tmp2[j+l]=((v2[j]*m)%mod*tmp2[j+l])%mod;
				if(tmp[j+l]==0) tmp2[j+l]=1;
				// tmp[j+l]=v[j]/mm;
				// cout<< tmp[j+l].val() <<endl;
			}
		}
		// rep(j, n+1) cout<< tmp[j] SP << tmp2[j] <<endl;
		// cout<<endl;
		rep3(j, m+1, 1){
			tmp[n-j]=((tmp[n-j]*tmp2[n+j])%mod+(tmp2[n-j]*tmp[n+j])%mod)%mod;
			tmp2[n-j]=(tmp2[n-j]*tmp2[n+j])%mod;
			// tmp[n-j]+=tmp[n+j];
		}
		rep(j, n+1){
			v[j]=tmp[j];
			v2[j]=tmp2[j];
		}
		// PV(v);
		// PV(v2);
		
	}

	// cout<< v[n] SP << v2[n] <<endl;
	// cout<< v[n].val() <<endl;
	cout<< (v[n]*modinv(v2[n]))%mod << endl;
 
	return 0;
}