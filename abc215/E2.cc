#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
int mod=998244353;

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

int dp[1010][20][1030];

int main(){

	int n;
	string s;

	cin>> n;
	cin>> s;

	rep(i, n){
		int x=s[i]-'A';
		rep(j, 10){
			rep(k, 1024){
				dp[i+1][j][k]+=dp[i][j][k];
				dp[i+1][j][k]%=mod;
				if(j==x){
					dp[i+1][j][k]+=dp[i][j][k];
					dp[i+1][j][k]%=mod;
				}
			}
		}
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}