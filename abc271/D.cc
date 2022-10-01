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

	int n, s;
	vector<int> a, b;
	string ans;

	cin>> n >> s;
	a.resize(n);
	b.resize(n);
	vector<vector<int>> dp(n+1, vector<int>(s+1));

	rep(i, n) cin >> a[i] >> b[i];
	dp[0][0]=1;
	// PV(dp[0]);

	rep3(i, n+1, 1) {
		repr(j, s+1){
			if(dp[i-1][j]==1 && j+a[i-1]<=s) dp[i][j+a[i-1]]=1;
			if(dp[i-1][j]==1 && j+b[i-1]<=s) dp[i][j+b[i-1]]=1;
		}
		// PV(dp[i]);
	}

	if(dp[n][s]==0) cout<< "No" << endl;
	else{
		cout<< "Yes" << endl;
		int nu=s;
		repr(i, n){
			if(nu-a[i]>=0 && dp[i][nu-a[i]]){
				ans+="H";
				nu-=a[i];
			}else{
				ans+="T";
				nu-=b[i];
			}
		}
		reverse(all(ans));
		cout<< ans <<endl;
	}
 
	return 0;
}