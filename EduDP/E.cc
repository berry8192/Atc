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
	int ans=0;
	vector<LLi> w, v;
	vector<vector<LLi>> dp;

	cin>> n >> W;
	w.resize(n);
	v.resize(n);
	dp.resize(n+1);
	rep(i, n+1) dp[i].resize(100001, imax);
	dp[0][0]=0;

	rep(i, n){
		cin >> w[i] >> v[i];
		//v[i]/=10;
	}

	rep(i, n) {
		rep(j, 100001){
			//cout<< i SP << j <<endl;
			dp[i+1][j]=min(dp[i+1][j], dp[i][j]);
			if(dp[i][j]+w[i]>W) continue;
			dp[i+1][j+v[i]]=min(dp[i][j]+w[i], dp[i][j+v[i]]);
		}
	}

	// rep(i, n+1){
	// 	rep(j, 10){
	// 		if(dp[i][j]==imax) cout<< -1 SP;
	// 		else cout<< dp[i][j] SP;
	// 	}
	// 	cout<< endl;
	// }

	rep(i, 100001){
		if(dp[n][i]<=W) ans=max(ans, i);
	}
	cout<< ans << endl;
 
	return 0;
}