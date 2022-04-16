#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=998244353;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int n, m, k;
	LLi ans=0;
	vector<int> v;
	LLi dp[60][3000];
	rep(i, 60){
		rep(j, 3000) dp[i][j]=0;
	}

	cin>> n >> m >> k;
	dp[0][0]=1;

	rep(i, n){
		rep(j, 2501){
			if(dp[i][j]>0){
				rep(l, m){
					dp[i+1][j+l+1]+=dp[i][j];
					dp[i+1][j+l+1]%=mod;
				}
			}
		}
	}

	rep(i, k) {
		ans+=dp[n][i+1];
		ans%=mod;
	}

	cout<< ans << endl;
 
	return 0;
}