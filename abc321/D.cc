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

template <class T> vector<ll> ruiseki(T vv){
	vector<ll> xx;
  	xx.resize(vv.size()+1);
	xx[0]=0;
	for(int i=0;i<(int)vv.size();i++){
		xx[i+1]=xx[i]+vv[i];
		// xx[i+1]=xx[i+1]%mod;
	}
	return xx;
}

int main(){

	ll n, m, p, ans=0;
	cin>> n >> m >> p;
	vector<ll> a(n), b(m), bb;

	rep(i, n) cin >> a[i];
	rep(i, m) cin >> b[i];
	sort(all(b));
	bb=ruiseki(b);
	// PV(bb);

	rep(i, n) {
		ll ma=p-a[i];
		auto lb=lower_bound(all(b), ma);
		// cout<< ma SP << lb-b.begin() <<endl;
		ans+=bb[lb-b.begin()]+a[i]*(lb-b.begin());
		ans+=(m-(lb-b.begin()))*p;
		// cout<< ans <<endl;
	}

	cout<< ans << endl;
 
	return 0;
}