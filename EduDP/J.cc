#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;
using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;
using mint = modint1000000007;
//using mint = modint=998244353;

int n;
double dp[310][310][310];

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//sushi メモ化再帰dp[x][y][z]
double dfs(int x, int y, int z){
	if(dp[x][y][z]!=-1.0) return dp[x][y][z];
	//cout<< "in " << x SP << y SP << z <<endl;

	dp[x][y][z]=1.0/(1-(double)(n-x-y-z)/n);
	if(x!=0) dp[x][y][z]+=dfs(x-1, y, z)*x/n/(1-(double)(n-x-y-z)/n);
	if(y!=0) dp[x][y][z]+=dfs(x+1, y-1, z)*y/n/(1-(double)(n-x-y-z)/n);
	if(z!=0) dp[x][y][z]+=dfs(x, y+1, z-1)*z/n/(1-(double)(n-x-y-z)/n);
	
	return dp[x][y][z];
}

int main(){

	int tmp;
	vector<int> d(4);
	cout << fixed << setprecision(12);

	rep(i, 310) rep(j, 310) rep(k, 310) dp[i][j][k]=-1.0;
	dp[0][0][0]=0;

	cin>> n;

	rep(i, n){
		cin >> tmp;
		d[tmp]++;
	}

	cout<< dfs(d[1], d[2], d[3]) << endl;
 
	return 0;
}