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
ll mod=998244353;
vector<ll> fac(1), facin(1);

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

//xCyを計算
ll conb(ll x, ll y){
	if(x<y) cout<< "conb x<y" << x SP << y <<endl;
	//if(x==y || y==0) return 1;
	return ((fac[x]*facin[y])%mod*facin[x-y])%mod;
}

int main(){

	int n, m, k;
	ll ans=0, ev=0, od=0, tmp;
	vector<int> u, v, io;

	cin>> n >> m >> k;
	u.resize(m);
	v.resize(m);
	io.resize(n);

	fac[0]=1;
	facin[0]=1;
	for(int i=1;i<=400010;i++){
		tmp=fac[i-1];
		tmp*=i;
		tmp=tmp%mod;
		fac.push_back(tmp);
		facin.push_back(modinv(tmp));
		//cout<< fac[i] << " " << facin[i] << " " << (fac[i]*facin[i])%mod <<endl;
	}
	//cout<< conb(n, m) <<endl;

	rep(i, m){
		cin >> u[i] >> v[i];
		io[u[i]-1]++;
		io[v[i]-1]++;
	}

	rep(i, n) {
		if(io[i]%2) od++;
		else ev++;
	}
	//cout<< ev SP << od <<endl;

	for(ll i=0;i<=od;i+=2){
		// 偶数k-i個、奇数i個
		if(ev<k-i || k-i<0) break;
		tmp=conb(ev, k-i)*conb(od, i);
		tmp%=mod;
		ans+=tmp;
		ans%=mod;
	}

	cout<< ans << endl;
 
	return 0;
}