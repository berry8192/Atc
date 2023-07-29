#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
using mint = modint998244353;

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
			cout << pvv[i][j].val() SP;
		}
		cout << endl;
	}
}

int main(){

	string s;
	cin>> s;
	int sz=s.size();
	vector<mint> dp(sz+1);
	dp[0]=1;

	rep(i, sz){
		vector<mint> ndp(sz+1);
		if(s[i]=='('){
			rep(j, sz){
				ndp[j+1]=dp[j];
			}
		}else if(s[i]==')'){
			rep(j, sz){
				ndp[j]=dp[j+1];
			}
		}else{
			rep(j, sz){
				if(j) ndp[j]+=dp[j-1];
				ndp[j]+=dp[j+1];
			}
		}
		dp=ndp;
		// rep(j, sz+1) cout<< dp[j].val() SP;
		// cout<< endl;
	}

	cout<< dp[0].val() << endl;
 
	return 0;
}