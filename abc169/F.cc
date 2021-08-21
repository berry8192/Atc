#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

const int MOD = 998244353;

// 入力
int n, A;
int a[3010], v[3010];
long long int ans=0;

// DPテーブル
int dp[3010][3010];
 
LLi modpow(LLi aa, LLi nn) {
    LLi res = 1;
    while (nn > 0) {
        if (nn & 1) res = res * aa % MOD;
        aa = aa * aa % MOD;
        nn >>= 1;
    }
    return res;
}

int main() {
  cin >> n >> A;
  for (int i = 0; i < n; ++i) cin >> a[i];

  memset(dp, 0, sizeof(dp));   // 一旦すべて 0 に
  dp[0][0] = 1;                // dp[0][0] だけ 1 に

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= A; ++j) {
      (dp[i+1][j] += dp[i][j]) %= MOD;
      if (j >= a[i]) (dp[i+1][j] += dp[i][j-a[i]]) %= MOD;
    }
  }

	for(int j=1;j<A;j++){
		//cout << dp[j][n-1] <<" ";
		v[j]=dp[j][n-1]-dp[j-1][n-1];
		//cout<< v[j] <<endl;
	}

	for(int i=1;i<A;i++){
		ans+=(v[i]*modpow(2, n-v[i]))%MOD;
		ans=ans%MOD;
	}

	cout<< ans <<endl;

}