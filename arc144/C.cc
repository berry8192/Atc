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

	ll n, k, lp;
	vector<ll> v, w;

	cin>> n >> k;
	w.resize(n);

	if(k*2>n){
		cout<< -1 <<endl;
		return 0;
	}

	//if(n-lp==2*k-1) return 1;

	rep(i, n) v.push_back(i+1);
	//PV(v);
	
	lp=(n-2*k)/k*k;

	for(int i=0;i<lp;i+=2*k){
		rep(j, k) swap(v[i+j], v[i+j+k]);
		//PV(v);
	}
	//cout<< lp <<endl;

	rep(i, n-lp){
		w[lp+i]=v[lp+(i+k)%(n-lp)];
	}
	rep(i, n-lp){
		v[lp+i]=w[lp+i];
	}
	// ll su=0;
	// rep(i, n){
	// 	// if(0<v[i] && v[i]<=n){
	// 	// }else{
	// 	// 	return 1;
	// 	// }
	// 	su+=v[i];
	// }
	// assert(su==n*(n+1)/2);
	PV(v);
	// PV(w);

	// while(1){
	// 	if(n>=k){

	// 	}
	// }
 
	return 0;
}