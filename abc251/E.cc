#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

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

	int n;
	ll ans;
	vector<int> v;
	ll dp[300010];

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, 300010) dp[i]=lmax;

	dp[0]=v[0];
	dp[1]=v[0]+v[1];
	rep3(i, n, 2) {
		dp[i]=min(dp[i-1]+v[i], dp[i-2]+v[i]);
		//dp[i+1]=dp[i];
	}
	//rep(i, n) cout<< dp[i] SP;
	//cout<< endl;
	ans=min(dp[n-2], dp[n-1]);
	//cout<< dp[n-2] SP << dp[n-1] <<endl;

	rep(i, 300010) dp[i]=lmax;
	v.push_back(v[0]);
	v.erase(v.begin());
	//PV(v);

	dp[0]=v[0];
	dp[1]=v[0]+v[1];
	rep3(i, n, 2) {
		dp[i]=min(dp[i-1]+v[i], dp[i-2]+v[i]);
		//dp[i+1]=dp[i];
	}
	//rep(i, n) cout<< dp[i] SP;
	//cout<< endl;
	ans=min(ans, min(dp[n-2], dp[n-1]));
	//cout<< dp[n-2] SP << dp[n-1] <<endl;

	cout<< ans << endl;
 
	return 0;
}