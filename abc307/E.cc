#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
using mint = modint998244353;

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

	int n, m;
	mint ans, tmp;

	cin>> n >> m;
	vector<mint> v(n), w(n);
	v[0]=m;
	w[0]=0;
	rep3(i, n, 1){
		v[i]=w[i-1];
		w[i]=v[i-1]*(m-1)+w[i-1]*(m-2);
		// cout<< v[i].val() SP << w[i].val() <<endl;
	}

	// ans=m;
	// rep3(i, n, 1){
	// 	ans*=m-1;
	// }
	// tmp=m;
	// rep3(i, n-3, 1){
	// 	ans*=m-1;
	// }


	cout<< w[n-1].val() << endl;
 
	return 0;
}