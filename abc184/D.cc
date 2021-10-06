#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

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

	int a, b, c;
	double dp[110][110][110];
  	//queue<LLi> q;

	cin>> a >> b >> c;

	dp[100][100][100]=0;
	dp[100][100][99]=0;
	dp[100][99][100]=0;
	dp[99][100][100]=0;
	dp[100][99][99]=0;
	dp[99][99][100]=0;
	dp[99][100][99]=0;

	for(int i=297;i>=0;i--){
		for(int j=99;j>=0;j--){
			for(int k=i-j;k>=0;k--){
				for(int l=i-j-k;l>=0;l--){
				//if(i+j+k==297) continue;
				dp[j][k][l]=dp[j+1][k][l]+(double)j/(l+j+k);
				dp[j][k][l]+=dp[j][k+1][l]+(double)k/(l+j+k);
				dp[j][k][l]+=dp[j][k][l+1]+(double)l/(l+j+k);
				//cout<< i SP << j SP << k SP << dp[i][j][k] <<endl;
				}
			}
		}
	}

	cout<< dp[a][b][c] <<endl;
 
	return 0;
}