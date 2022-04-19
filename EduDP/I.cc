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

	int n;
	double ans=0.0;
	vector<double> v, dp;

	cin>> n;
	v.resize(n);
	dp.resize(n+1);
	dp[0]=1.0;

	rep(i, n){
		cin >> v[i];
	}
	//PV(v);

	rep(i, n) {
		rep(j, i+1){
			int idx=i+1-j;
			double dlt=dp[idx-1]*v[i];
			//cout<< dp[idx-1] SP << v[i] SP << dp[idx-1]*v[i] <<endl;
			dp[idx]+=dlt;
			dp[idx-1]-=dlt;
		}
	}
	//PV(dp);

	for(int i=n/2+1;i<=n;i++) ans+=dp[i];

	cout << fixed << setprecision(12);
	cout<< ans << endl;
 
	return 0;
}