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

	int n, ans=0;
	vector<ll> v, imo1, imo2;

	cin>> n;
	v.resize(n);
	imo1.resize(n+2);
	imo2.resize(n+2, 1);

	rep3(i, n, 1) cin >> v[i];

	rep3(i, n, 1) {
		ll p1=2;
		ll p2=v[i];
		ll i1=imo1[i+1];
		ll i2=imo2[i+1];
		imo1[i+1]=(p1*i2+p2*i1)%mod;
		imo2[i+1]=(i1*i2)%mod;
		imo1[i+2]=(p1*i2+p2*i1)%mod;
		imo2[i+1]=(i1*i2)%mod;
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}