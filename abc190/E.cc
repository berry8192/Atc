#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define int long long
const int inf = 100100100100100;
const int mod = 1000000007;

const int maxn = 17;
int n, m;
int dist[maxn][maxn];
int dp[1<<maxn][maxn];

int dfs(int s, int v){

    if(dp[s][v] >= 0){
        return dp[s][v];
    }

    if(s == (1<<n)-1 && v == 0){
        return dp[s][v] = 0;
    }

    int ans = inf;
    rep(u,0,n){
        if(!(s >> u & 1)){
            ans = min(ans, dfs(s | 1 << u, u) + dist[v][u]);
        }
    }

    dp[s][v] = ans;
    return ans;


}

signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    
    cin >> n >> m;

    memset(dp,-1,sizeof(dp));
    fill(dist[0],dist[0]+maxn*maxn,inf);

    

    
    rep(i,0,m){
        int f, t;
        cin >> f >> t;
        dist[f][t] = 1;
    }

	int k;
	vector<int> c;
	c.resize(k);
	cin>> k;
	for(int i=0;i<k;i++) cin>> c[i];
    int ans = dfs(0,0);
    cout << (ans == inf ? -1 : ans) << endl;

}