#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;
//using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;
LLi mod=1000000007;

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

	int h, w, ans=0;
	vector<vector<char>> v;
	vector<vector<int>> dp;

	cin>> h >> w;
	v.resize(h);
	dp.resize(h+1);
	rep(i, h) v[i].resize(w);
	rep(i, h+1) dp[i].resize(w+1);

	rep(i, h) rep(j, w) cin >> v[i][j];

	dp[0][1]=1;

	rep(i, h) rep(j, w){
		if(v[i][j]=='.') dp[i+1][j+1]=(dp[i][j+1]+dp[i+1][j])%mod;
	}

	cout<< dp[h][w] << endl;
 
	return 0;
}