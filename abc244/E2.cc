#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
//LLi mod=1000000007;
LLi mod=998244353;

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

LLi dp[2][2010][2010];

int main(){

	int n, m, k, s, t, x;
	LLi ans=0;
	vector<int> u, v;
	vector< vector<int> > e;

	cin>> n >> m >> k >> s >> t >> x;
	u.resize(m);
	v.resize(m);
	e.resize(n+1);

	rep(i, m){
		cin >> u[i] >> v[i];
		e[u[i]].push_back(v[i]);
		e[v[i]].push_back(u[i]);
	}

	rep(i, 2){
		rep(j, k+1){
			rep(l, n) dp[i][j][l+1];
		}
	}
	dp[0][0][s]=1;

	rep(i, k){
		rep(j, m){
			if(v[j]!=x){
				dp[0][i+1][u[j]]+=dp[0][i][v[j]];
				dp[1][i+1][u[j]]+=dp[1][i][v[j]];
			}else{
				dp[0][i+1][u[j]]+=dp[1][i][v[j]];
				dp[1][i+1][u[j]]+=dp[0][i][v[j]];
			}
			if(u[j]!=x){
				dp[0][i+1][v[j]]+=dp[0][i][u[j]];
				dp[1][i+1][v[j]]+=dp[1][i][u[j]];
			}else{
				dp[0][i+1][v[j]]+=dp[1][i][u[j]];
				dp[1][i+1][v[j]]+=dp[0][i][u[j]];
			}
			dp[0][i+1][u[j]]%=mod;
			dp[1][i+1][u[j]]%=mod;
			dp[0][i+1][v[j]]%=mod;
			dp[1][i+1][v[j]]%=mod;
		}
	}

	cout<< dp[0][k][t] << endl;
 
	return 0;
}