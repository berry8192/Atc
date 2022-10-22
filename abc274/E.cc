#include <bits/stdc++.h>
#define LOOP(n) for (int _i = 0; _i < (n); _i++)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define RREP(i, n) for (int i = (n); i >= 0; --i)
#define FOR(i, r, n) for (int i = (r); i < (n); ++i)
#define ALL(obj) begin(obj), end(obj)
using namespace std;
using ll = long long;
const double INF = 1000100100;

template <class T>
bool chmin(T &a, const T &b) {
    if (b < a) {
        a = b;
        return 1;
    }
    return 0;
}

ll n, m;
double G[20][20];  // グラフ
double dp[550000][5][18];

int main() {
    cin >> n >> m;
	vector<ll> x(n+m+1), y(n+m+1);

	REP(i, n+m) cin>> x[i+1] >> y[i+1];
	x[0]=0;
	y[0]=0;
	n++;

    // グラフの初期化
    REP(i, n+m) {
        REP(j, n+m) { 
			ll xx=x[i]-x[j];
			ll yy=y[i]-y[j];
			G[i][j] = sqrt(xx*xx+yy*yy);
		}
    }

    // dp の初期化
    REP(i, 550000) {
		REP(l, 5){
        	REP(j, 18) { dp[i][l][j] = INF; }
		}
    }
    dp[0][0][0] = 0.0;  // スタートを頂点 0 とする

    REP(S, 1 << (n+m)) {
		REP(b, m){
			REP(v, n+m) {
				REP(u, n+m) {
					// if (S != 0 && !(S & (1 << u))) continue; // u を含まない場合を除く
					if ((S & (1 << v)) == 0) {
						if (v != u){
							if(n<=u) chmin(dp[S | (1 << v)][b+1][v], dp[S][b][u] + G[u][v]/(1 << b));
							else chmin(dp[S | (1 << v)][b][v], dp[S][b][u] + G[u][v]/(1 << b));
						}
					}
				}
            }
        }
    }

	double ans=INF;
    // REP(i, (1<<m)) cout<< dp[(1 << (n+m)) - 1][i][0] <<endl;
    REP(i, m){
		REP(j, (1 << (n+m))){
			if((j & ((1<<n)-1)) != ((1<<n)-1)) continue;
			chmin(ans, dp[j][i][0]);
		}
	}

	// cout<< ans <<endl;
	printf("%.12lf\n", ans);

    return 0;
}