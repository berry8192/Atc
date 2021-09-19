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

	int n, x, y, mi=9999;
	vector<int> a, b;
	int dp[310][310][310];
	//aコメの弁当箱まででたこbこ、たいcこ食える。valこ買ってる

	cin>> n >> x >> y;
	a.resize(n);
	b.resize(n);

	rep(i, n) cin >> a[i] >> b[i];
	// cout<< "n " << n <<endl;
	// cout<< "x " << x <<endl;
	// cout<< "y " << y <<endl;
	// rep(i, n) cout<< a[i] SP << b[i] <<endl;

	rep(i, n+1){
		rep(j, x+1){
			rep(k, y+1){
				dp[i][j][k]=9999;
			}
		}
	}

	dp[0][0][0]=0;

	rep(i, n) {
		//cout<< "i=" << i <<endl;
		rep(j, x+1){
			rep(k, y+1){
				//cout<< j SP << k SP << dp[i][j][k]+1 SP << dp[i][min(x, j+a[i])][min(y, k+b[i])] <<endl;//

				dp[i+1][min(x, j+a[i])][min(y, k+b[i])]=min(min(dp[i][min(x, j+a[i])][min(y, k+b[i])], dp[i][j][k]+1), dp[i+1][min(x, j+a[i])][min(y, k+b[i])]);
				//cout<< min(x, j+a[i]) SP << min(y, k+b[i]) SP << dp[i+1][min(x, j+a[i])][min(y, k+b[i])] <<endl;//
				dp[i+1][j][k]=min(dp[i+1][j][k], dp[i][j][k]);
			}
		}
		
		// rep(j, x+1){
		// 	rep(k, y+1){
		// 		cout<< dp[i+1][j][k] <<" ";
		// 	}
		// 	cout<< endl;
		// }
		// cout<< endl;
	}
	

	if(dp[n][x][y]==9999) cout<< -1 <<endl;
	else cout<< dp[n][x][y] << endl;
 
	return 0;
}