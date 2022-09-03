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
ll lmax=4223372036854775807;
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

ll dp[2010][2010];

int main(){

	ll n, m, ma=-lmax;
	vector<ll> v;

	cin>> n >> m;
	v.resize(n);

	rep(i, n) cin >> v[i];
	rep(i, 2010){
		rep(j, 2010){
			dp[i][j]=-lmax;
		}
	}
	rep(i, 2010) dp[i][0]=0;

	rep(i, n){
		rep(j, m){
			dp[i+1][j+1]=max(dp[i][j+1], dp[i][j]+v[i]*(j+1));
			//cout<<dp[i+1][j+1] SP;
		}
		//cout<< endl;
	}

	cout<< dp[n][m] << endl;
 
	return 0;
}