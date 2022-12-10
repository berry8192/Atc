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

ll dp[110][110][110];

int main(){

	ll n, k, d;
	vector<ll> v;

	cin>> n >> k >> d;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, 110){
		rep(j, 110){
			rep(l, 110){
				dp[i][j][l]=-lmax;
			}
		}
	}

	dp[0][1][v[0]%d]=v[0];
	dp[0][0][0]=0;

	rep3(i, n, 1) {
		rep(j, k+1){
			rep(l, d){
				// cout<< ((l-v[i])%d*100000000000LL+d)%d <<endl;
				// assert(((l-v[i])%d*100000000000LL+d)%d>=);
				// assert(((l-v[i])%d+d)%d>=d);
				dp[i][j+1][l]=max(dp[i][j+1][l], dp[i-1][j][((l-v[i])%d+d*100000000000LL)%d]+v[i]);
				dp[i][j][l]=max(dp[i][j][l], dp[i-1][j][l]);
			}
		}
	}
	// rep(i, d) cout<< dp[n-1][k][i] SP;
	// cout<< endl;

	if(dp[n-1][k][0]<0) cout<< -1 << endl;
	else cout<< dp[n-1][k][0] << endl;
 
	return 0;
}