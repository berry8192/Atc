#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

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

int main(){

	int t, n, m;

	cin>> t;
	rep(lp, t){
		cin>> n >> m;
		vector<int> c(n), u(m), v(m);
		vector<vector<int>> g(n);
		rep(i, n) cin >> c[i];
		rep(i, m){
			cin >> u[i] >> v[i];
			u[i]--;
			v[i]--;
			g[u[i]].push_back(v[i]);
			g[v[i]].push_back(u[i]);
		}

		vector<vector<int>> dp(n, vector<int>(n, -1));
		dp[n-1][0]=0;
		queue<int> ao, tk;
		ao.push(n-1);
		tk.push(0);
		while(!ao.empty()){
			int aoki=ao.front();
			int taka=tk.front();
			ao.pop();
			tk.pop();
			int prev=dp[aoki][taka];
			rep(i, g[aoki].size()){
				rep(j, g[taka].size()){
					if(c[g[aoki][i]]!=c[g[taka][j]] && dp[g[aoki][i]][g[taka][j]]==-1){
						dp[g[aoki][i]][g[taka][j]]=prev+1;
						ao.push(g[aoki][i]);
						tk.push(g[taka][j]);
					}
				}
			}
		}
		cout<< dp[0][n-1] << endl;
	}
 
	return 0;
}