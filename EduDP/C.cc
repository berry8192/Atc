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

	int n, ans=0;
	vector<vector<int>> v, dp;

	cin>> n;
	v.resize(n);
	dp.resize(n+1);
	rep(i, n) v[i].resize(3);
	rep(i, n+1) dp[i].resize(3);

	rep(i, n) cin >> v[i][0] >> v[i][1] >> v[i][2];

	rep(i, n) {
		rep(j, 3){
			int tmp=0;
			rep(k, 3){
				if(j==k) continue;
				tmp=max(tmp, dp[i][k]+v[i][j]);
			}
			dp[i+1][j]=tmp;
			//cout<< tmp <<" ";
		}
		//cout<< endl;
	}

	cout<< max(dp[n][0], max(dp[n][1], dp[n][2])) << endl;
 
	return 0;
}