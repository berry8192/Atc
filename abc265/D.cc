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

	ll n, p, q, r;
	vector<ll> v, w;

	cin>> n >> p >> q >> r;
	v.resize(n);

	rep(i, n) cin >> v[i];
	w=ruiseki(v);
	//PV(w);

	rep3(i, n+1, 1) {
		ll pp=w[i]-p;
		ll qq=w[i]+q;
		ll rr=w[i]+q+r;
		auto plb=lower_bound(all(w), pp);
		auto pub=upper_bound(all(w), pp);
		auto qlb=lower_bound(all(w), qq);
		auto qub=upper_bound(all(w), qq);
		auto rlb=lower_bound(all(w), rr);
		auto rub=upper_bound(all(w), rr);
		if(plb!=pub && qlb!=qub && rlb!=rub){
			cout<< "Yes" << endl;
			return 0;
		}
	}

	cout<< "No" << endl;
 
	return 0;
}