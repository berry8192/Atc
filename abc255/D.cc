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

// 累積和
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

	ll n, q;
	vector<ll> v, w, x;

	cin>> n >> q;
	v.resize(n);
	x.resize(q);

	rep(i, n) cin >> v[i];
	rep(i, q) cin >> x[i];
	sort(all(v));
	w=ruiseki(v);
	//PV(w);

	rep(i, q) {
		auto lb = lower_bound(all(v), x[i]);
		ll pos=lb-v.begin();
		//cout<< pos <<endl;
		ll tmp=w[n]-n*x[i];
		tmp+=(pos*x[i]-w[pos])*2;
		cout<< tmp <<endl;
	}

	return 0;
}