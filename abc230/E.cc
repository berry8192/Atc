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

	ll n, ans=0;

	cin>> n;

	ll i;
	for(i=1;i*i<=n;i++){
		ans+=n/i;
		//cout<< n/i << endl;
	}
	//cout<< "i=" << i <<endl;
	for(;i<=n;i++){
		ll tmp=n/(n/i);
		ans+=n/i*(tmp-i+1);
		//cout<< n/i SP << (tmp-i) SP << n/i*(tmp-i) << endl;
		i=tmp;
	}

	cout<< ans << endl;
 
	return 0;
}