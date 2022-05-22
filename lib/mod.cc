#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;

ll mod=1000000007;
vector<ll> fac(1), facin(1), ten(1);

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//vector<ll>を出力
void PVL(vector<ll> pvv) {
	rep(i, (int)pvv.size()) cout << pvv[i] SP;
	cout << endl;
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
 
ll modpow(ll a, ll n) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

ll modabs(ll x){
	if(x>=0) return (x%mod);

	ll tmp=abs(x);
	ll di=(tmp+mod-1)/mod;
	return (mod*di+x)%mod;
}

//xCyを計算
ll conb(ll x, ll y){
	if(x<y) cout<< "conb x<y" << x SP << y <<endl;
	return ((fac[x]*facin[y])%mod*facin[x-y])%mod;
}

//xPyを計算
ll perm(ll x, ll y){
	if(x<y) cout<< "perm x<y" << x SP << y <<endl;
	return (fac[x]*facin[x-y])%mod;
}

//modの各桁を配列で出す
// aは2とか10、lenが長さ
vector<ll> modvec(ll a, int len){
	vector<ll> rtn(len);
	rtn[0]=a;
	for(int i=1;i<len;i++){
		rtn[i]=(rtn[i-1]*a)%mod;
		//rtn[i]=(rtn[i-1]*10)%mod;
	}
	return rtn;
}

int main(){

	int n;
	ll tmp, ans=1;
	cin>> n;

	//fac, facinをメモ化
	fac[0]=1;
	facin[0]=1;
	for(int i=1;i<=n;i++){
		tmp=fac[i-1];
		tmp*=i;
		tmp=tmp%mod;
		fac.push_back(tmp);
		facin.push_back(modinv(tmp));
		//cout<< fac[i] << " " << facin[i] << " " << (fac[i]*facin[i])%mod <<endl;
	}

	//10^xのmodをメモ化
    ten[0]=1;
  	rep(i, n-1) ten.push_back((ten[i]*10)%mod);

	//modinvテスト
	//rep(i, n) cout<< -i << " " << modabs(-i) <<endl;

	//conbテスト
	/*rep(i, n){
		for(int j=0;j<=i;j++){
			cout<< i << "C" << j << "=" << conb(i, j) <<endl;
		}
	}*/

	//permテスト
	/*rep(i, n){
		for(int j=0;j<=i;j++){
			cout<< i << "P" << j << "=" << perm(i, j) <<endl;
		}
	}*/

	

	/*
	//四則演算と余り
	ans+=x;
	ans+=mod-x;
	ans*=x;
	ans*=modinv(x, mod);
	ans*=modpow(x, y, mod);
	ans=ans%mod;
	*/

	return 0;
}

//0と1のコーナーケースに気をつける