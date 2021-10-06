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

	int d, sz, tmp;
	LLi dp[10010][2][110];
	LLi ans=0;
	string s;

	cin>> d;
	cin>> s;

	sz=s.size();

	memset(dp, 0, sizeof(dp));

	dp[0][0][0]=1;

	//大きい桁から見ていく
	for(int i=0;i<sz;i++){

		//頭からi桁目をintに変換
		tmp=(int)(s[i]-'0');
		//未満フラグ
		for(int j=0;j<2;j++){

			//頭からi桁目までの数字の和の余りがkとなるものの数
			for(int k=0;k<d;k++){

				//未満フラグが1(true)なら0~9、0ならtmpまで回す
				for(int l=0;l<=(j ? 9 : tmp);l++){
					dp[i+1][j || (l<tmp)][(k+l)%d]+=dp[i][j][k];
					dp[i+1][j || (l<tmp)][(k+l)%d]=dp[i+1][j || (l<tmp)][(k+l)%d]%1000000007;
				}
			}
		}
	}

	cout<< dp[sz][0][0]+dp[sz][1][0]-1 <<endl;

	return 0;
}