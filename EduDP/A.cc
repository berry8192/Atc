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
	vector<int> v, dp;

	cin>> n;
	v.resize(n);
	dp.resize(n, imax);

	rep(i, n) cin >> v[i];
	dp[0]=0;
	dp[1]=abs(v[1]-v[0]);

	rep3(i, n, 2) {
		dp[i]=min(dp[i-1]+abs(v[i]-v[i-1]), dp[i-2]+abs(v[i]-v[i-2]));
	}

	cout<< dp[n-1] << endl;
 
	return 0;
}