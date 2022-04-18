#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;
using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;
using mint = modint1000000007;
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

	int n, W;
	LLi ans=0;
	vector<LLi> w, v;
	vector<vector<LLi>> dp;

	cin>> n >> W;
	w.resize(n);
	v.resize(n);
	dp.resize(n+1);
	rep(i, n+1) dp[i].resize(W+1);

	rep(i, n) cin >> w[i] >> v[i];

	rep(i, n) {
		rep(j, W){
			//cout<< i SP << j <<endl;
			dp[i+1][j]=max(dp[i+1][j], dp[i][j]);
			if(j+w[i]>W) continue;
			dp[i+1][j+w[i]]=max(dp[i][j]+v[i], dp[i+1][j+w[i]]);
		}
	}

	// rep(i, n+1){
	// 	rep(j, W+1){
	// 		if(dp[i][j]==-llimax) cout<< -1 SP;
	// 		else cout<< dp[i][j] SP;
	// 	}
	// 	cout<< endl;
	// }

	rep(i, W+1) ans=max(ans, dp[n][i]);
	cout<< ans << endl;
 
	return 0;
}