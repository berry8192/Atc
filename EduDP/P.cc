#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
ll mod=1000000007;
//using mint = modint=998244353;

ll dp[100010][2];
vector<int> flag(100010);
vector<vector<int>> e;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

void dfs(int x, int pre){
	//cout<< x <<endl;
	if(flag[x]) return;
	flag[x]=1;

	dp[x][0]=1;
	dp[x][1]=1;
	rep(i, e[x].size()){
		if(pre==e[x][i]) continue;
		dfs(e[x][i], x);
		dp[x][0]*=(dp[e[x][i]][0]+dp[e[x][i]][1])%mod;
		dp[x][1]*=dp[e[x][i]][0];
		dp[x][0]%=mod;
		dp[x][1]%=mod;
	}
	//cout<< x SP << dp[x][0] SP << dp[x][1] <<endl;
}

int main(){

	int n, x, y;

	cin>> n;
	e.resize(n+1);

	rep(i, n-1){
		cin >> x >> y;
		//cout<< "in" << x SP << y <<endl;
		e[x].push_back(y);
		e[y].push_back(x);
	}

	dfs(1, 0);

	cout<< (dp[1][0]+dp[1][1])%mod << endl;
 
	return 0;
}