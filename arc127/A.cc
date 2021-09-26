/*#include<cstdio>
#include<bits/stdc++.h>

using namespace std;

//Nは桁数が大きい場合があるので文字列として受け取る
string N;
vector<int> n;  //Nの各桁の数字を格納するベクター
long long dp[20][2][20][2];
//桁数、small、1が何個連続してるか、1が連続していないフラグ＝の個数
long long ans=0;

int main(){
  cin>>N;

  //ベクターnを構成
  for(auto a : N){
    n.push_back(a-'0');
  }
  int l = N.size();  //nの長さ

  //dp[0][0][0][0] = 1;  //初期条件。他は0で初期化されている
    for(int i = 0; i < l; i++){
        for(int smaller = 0; smaller < 2; smaller++){
            for(int j = 0; j < l; j++){
                //for(int k=0;k<2;k++){
			        for(int x = 0; x <= (smaller ? 9 : n[i]); x++){
				        dp[i + 1][smaller || x < n[i]][j][x!=1] += dp[i][smaller][j][0];
                    }
                //}
			}
        }
    }

	// for(int i=1;i<l;i++){
	// 	ans+=dp[l][0][i][1]
  cout << dp[l][0][1] + dp[l][1][1] << endl;
  cout << dp[l][0][1] <<endl;
  cout << dp[l][1][1] << endl;

  return 0;
}*/