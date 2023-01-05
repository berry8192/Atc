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

int imax=1147483647;
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

	int h, n;
	cin>> h >> n;
	vector<int> a(n), b(n);
	vector<int> dp(h+1, imax);
	dp[h]=0;

	rep(i, n) cin >> a[i] >> b[i];

	rep(i, n){
		repr(j, h+1){
			dp[max(0, j-a[i])]=min(dp[max(0, j-a[i])], dp[j]+b[i]);
		}
	}

	cout<< dp[0] << endl;
 
	return 0;
}