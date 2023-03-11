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
ll mod;

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

int main(){

	ll a, x, m, lans=0, ans=0, tmp=1, lp;

	cin>> a >> x >> m;
	mod=m;
	a%=m;

	rep(i, min(x, 1000000LL)) {
		ans+=tmp;
		tmp*=a;
		ans%=m;
		tmp%=m;
	}
	if(x<=1000000){
		cout<< ans <<endl;
		return 0;
	}

	lans=ans;
	lp=x/1000000;
	ll r=modpow(a, 1000000);
	r%=m;
	// cout<< r <<endl;
	rep3(i, lp, 1){
		ans*=r;
		ans%=m;
		lans+=ans;
		lans%=m;
	}
	ll l=(x/1000000)*1000000, rr=x;
	// cout<< l <<endl;
	for(ll i=l;i<rr;i++){
		lans+=modpow(a, i);
		lans%=m;
	}

	cout<< lans << endl;
 
	return 0;
}