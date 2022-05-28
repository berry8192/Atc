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

template <class T> vector<ll> ruiseki(T vv){
	vector<ll> xx;
  	xx.resize(vv.size()+1);
	xx[0]=0;
	for(int i=0;i<(int)vv.size();i++){
		xx[i+1]=xx[i]+vv[i];
		xx[i+1]=xx[i+1]%mod;
	}
	return xx;
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

	ll n, m, k, ans=0;
	vector<vector<ll>> v;
	vector<ll> w;

	cin>> n >> m >> k;

	if(k==0){
		cout<< modpow(m, n) <<endl;
		return 0;
	}

	v.resize(n);
	rep(i, n) v[i].resize(m+1);

	rep3(i, m+1, 1) v[0][i]=1;
	w=ruiseki(v[0]);
	//PV(w);
	rep3(i, n, 1){
		rep3(j, m+1, 1){
			int l=max(0LL, j-k);
			int r=min(m+1, j+k);
			v[i][j]+=w[l+1];
			//cout<< "l: " << v[i][j] <<endl;
			v[i][j]+=(w[m+1]-w[r]+mod);
			//cout<< "r: " << v[i][j] <<endl;
			v[i][j]%=mod;
			//cout<< v[i][j] <<endl;
		}
		//cout<< endl;
		w=ruiseki(v[i]);
	}

	rep3(i, m+1, 1){
		ans+=v[n-1][i];
		ans%=mod;
	}
	cout<< ans << endl;
 
	return 0;
}