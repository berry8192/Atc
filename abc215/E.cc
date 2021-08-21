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

	int n;
	LLi ans=0;
	string s;
	vector<int> v;
	LLi dp[10][1010][3];
	//コンテスト名、ステップ、もう塊おわったか

	cin>> n >> s;
	v.resize(n+1);

	rep(i, n){
		v[i+1]=int(s[i]-'A');
	}

	rep(i, n) {
		if (v[i]) ans++;
	}

	rep(i, 10){
		dp[i][0][0]=1;
		dp[i][0][1]=0;
	}

	for(int i=0;i<10;i++){
		for(int j=0;j<n;j++){
			//塊=0まだ出てない
			dp[i][j+1][0]=dp[i][j][0];
			dp[i][j+1][2]=dp[i][j][2];
			if(v[j]==i){
				dp[i][j+1][1]=dp[i][j][1];
				dp[i][j+1][1]+=dp[i][j][0];
			}
			if(v[j]!=i) dp[i][j+1][2]+=dp[i][j][1];
			
			dp[i][j+1][0]=dp[i][j+1][0]%mod;
			dp[i][j+1][1]=dp[i][j+1][1]%mod;
			dp[i][j+1][2]=dp[i][j+1][2]%mod;
		}
	}
	
	for(int i=0;i<10;i++){
		ans+=dp[i][n][0]+dp[i][n][1]+dp[i][n][2];
	}
	cout<< ans%mod <<endl;
 
	return 0;
}