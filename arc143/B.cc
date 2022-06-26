#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;
ll mod=998244353;

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

	ll n, ans=1;
	vector<ll> fac;
	cin>> n;
	fac.resize(n*n+1);

	if(n==1){
		cout<< 0 <<endl;
		return 0;
	}

	fac[0]=1;
	rep3(i, n*n+1, 1){
		ans*=i;
		ans%=mod;
		fac[i]=ans;
	}

	rep3(i, n*n+1, 1){
		//cout<< "i=" << i <<endl;
		ll tmp=1;
		if(n*n-i<n-1) continue;
		// rep(j, n-1){
		// 	tmp*=n*n-i-j;
		// 	tmp%=mod;
		// }
		tmp*=fac[n*n-i];
		tmp%=mod;
		tmp*=modinv(fac[n*n-i-(n-1)]);
		tmp%=mod;
		//cout<< tmp <<endl;
		if(i-1<n-1) continue;
		// rep(j, n-1){
		// 	tmp*=i-1-j;
		// 	tmp%=mod;
		// }
		tmp*=fac[i-1];
		tmp%=mod;
		tmp*=modinv(fac[i-1-(n-1)]);
		tmp%=mod;
		//cout<< tmp <<endl;

		tmp*=n*n;
		tmp%=mod;
		tmp*=fac[(n-1)*(n-1)];
		tmp%=mod;
		ans+=mod-tmp;
		ans%=mod;
	}

	cout<< ans << endl;
 
	return 0;
}