#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long
using namespace std;
const double INF = 1000100100;

template <class T>
bool chmin(T &a, const T &b) {
    if (b < a) {
        a = b;
        return 1;
    }
    return 0;
}

ll n;
int G[20][20];  // グラフ
double dp[140000][18];

int main() {
    cin >> n;
	vector<string> s(n);
	rep(i, n) cin>> s[i];

    // グラフの初期化
    rep(i, n) {
        rep(j, n) { 
			if(i==j) G[i][j]=0;

			if(s[i][s[i].size()-1]==s[j][0]) G[i][j]=1;
			else G[i][j]=0;
		}
    }

    // dp の初期化
    rep(i, 140000) {
		rep(j, 18) { dp[i][j] = INF; }
    }
    dp[0][0] = 0;  // スタートを頂点 0 とする

    rep(S, 1 << (n)) {
		rep(v, n+m) {
			rep(u, n+m) {
				// if (S != 0 && !(S & (1 << u))) continue; // u を含まない場合を除く
				if ((S & (1 << v)) == 0) {
					if (v != u){
						if(G[u][v]==0)
						if(n<=u) chmin(dp[S | (1 << v)][b+1][v], dp[S][b][u] + G[u][v]/(1 << b));
						else chmin(dp[S | (1 << v)][b][v], dp[S][b][u] + G[u][v]/(1 << b));
					}
				}
			}
		}
    }

	double ans=INF;
    // rep(i, (1<<m)) cout<< dp[(1 << (n+m)) - 1][i][0] <<endl;
    rep(i, m){
		rep(j, (1 << (n+m))){
			if((j & ((1<<n)-1)) != ((1<<n)-1)) continue;
			chmin(ans, dp[j][i][0]);
		}
	}

	// cout<< ans <<endl;
	printf("%.12lf\n", ans);

    return 0;
}