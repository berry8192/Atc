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

	int n, q;
	vector<int> v, l, r, w;

	cin>> n;
	v.resize(n);
	w.resize(n);
	rep(i, n) cin >> v[i];

	cin>> q;
	l.resize(q);
	r.resize(q);
	rep(i, q) cin>> l[i] >> r[i];
	rep(i, n-1){
		if(i%2==0){
			w[i]=0;
		}else{
			w[i]=v[i+1]-v[i];
		}
	}
	vector<ll> x=ruiseki(w);
	// PV(v);
	// PV(w);
	// PV(x);
	rep(i, q) {
		auto llb=lower_bound(all(v), l[i]);
		auto rlb=lower_bound(all(v), r[i]);

		int le=llb-v.begin();
		int ri=rlb-v.begin();
		// cout<< le SP << ri SP << v[le] SP << v[ri] <<endl;
		ll ans=x[ri]-x[le];
		if(le%2==0) ans+=v[le]-l[i];
		if(ri%2==0) ans-=v[ri]-r[i];
		cout<< ans <<endl;
	}
 
	return 0;
}