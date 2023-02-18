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
using mint = modint998244353;
ll mod=998244353;

//int型vectorを出力
// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) cout << pvv[i].val() SP;
// 	cout<< pvv[pvv.size()-1].val() <<endl;
// }

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

vector<ll> fac(1), facin(1);

ll conb(ll x, ll y){
	if(x<y){
		// cout<< "conb x<y" << x SP << y <<endl;
		return 1;
	}
	return ((fac[x]*facin[y])%mod*facin[x-y])%mod;
}

int main(){

	int n, k;
	vector<mint> v;
	set<int> st;
	mint ans=0;

	cin>> n >> k;
	v.resize(n);

	ll tmp;
	fac[0]=1;
	facin[0]=1;
	for(int i=1;i<=n+k+k+1;i++){
		tmp=fac[i-1];
		tmp*=i;
		tmp=tmp%mod;
		fac.push_back(tmp);
		facin.push_back(modinv(tmp));
		//cout<< fac[i] << " " << facin[i] << " " << (fac[i]*facin[i])%mod <<endl;
	}

	int inx;
	rep(i, n){
		cin >> inx;
		st.insert(inx);
		v[i]=inx;
	}
	// sort(all(v));
	// PV(v);
	int mex=0;
	rep(i, n+k){
		// cout<< k+i-1 SP << k-i+mex-1 SP << conb(k+i-1, k-i+mex-1) <<endl;
		ll tama=k-i+mex-1;
		ll hako=i+1;
		if(tama<0) break;
		ans+=conb(hako+tama-1, tama);
		if(st.find(i)!=st.end()) mex++;
		// cout<< ans.val() <<endl;
	}

	cout<< ans.val() << endl;
 
	return 0;
}