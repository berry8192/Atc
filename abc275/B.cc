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

int main(){

	ll ans=0, tmp=0;
	vector<ll> v(6);

	rep(i, 6){
		cin >> v[i];
		v[i]%=mod;
	}

	ans=v[0];
	ans%=mod;
	ans*=v[1];
	ans%=mod;
	ans*=v[2];
	ans%=mod;
	tmp=v[3];
	tmp%=mod;
	tmp*=v[4];
	tmp%=mod;
	tmp*=v[5];
	tmp%=mod;

	cout<< (ans-tmp+mod)%mod << endl;
 
	return 0;
}