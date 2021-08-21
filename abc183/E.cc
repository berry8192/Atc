#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;

int main(){

	int a, b;
	vector<string> board;
	vector< vector<LLi> > dp, x, y, z;
	cin>> a >> b;
	board.resize(a);
	dp.resize(a);
	rep(i, a) dp[i].resize(b);
	x.resize(a);
	rep(i, a) x[i].resize(b);
	y.resize(a);
	rep(i, a) y[i].resize(b);
	z.resize(a);
	rep(i, a) z[i].resize(b);

	for(int i=0;i<a;i++){
		cin>> board[i];
		//cout<< board[i] <<endl;
	}

	dp[0][0]=1;

	rep(i, a){
		rep(j, b){
			if(0<j && board[i][j]!='#'){
				x[i][j]=x[i][j-1]+dp[i][j-1];
				x[i][j]=x[i][j]%mod;
			}
			if(0<i && board[i][j]!='#'){
				y[i][j]=y[i-1][j]+dp[i-1][j];
				y[i][j]=y[i][j]%mod;
			}
			if(0<i && 0<j && board[i][j]!='#'){
				z[i][j]=z[i-1][j-1]+dp[i-1][j-1];
				z[i][j]=z[i][j]%mod;
			}
			dp[i][j]+=x[i][j]+y[i][j]+z[i][j];
			dp[i][j]=dp[i][j]%mod;
			//cout<< dp[i][j] << " ";
		}
		//cout<< endl;
	}

	cout<< dp[a-1][b-1] << endl;
 
	return 0;
}