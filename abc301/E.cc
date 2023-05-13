#include <bits/stdc++.h>
#define LOOP(n) for (int _i = 0; _i < (n); _i++)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define RREP(i, n) for (int i = (n); i >= 0; --i)
#define FOR(i, r, n) for (int i = (r); i < (n); ++i)
#define ALL(obj) begin(obj), end(obj)
using namespace std;
using ll = long long;
const int INF = 1000100100;

template <class T>
bool chmin(T &a, const T &b) {
    if (b < a) {
        a = b;
        return 1;
    }
    return 0;
}

int V;
int G[20][20];  // グラフ
int dp[300000][20];
int dh[]={0, -1, 0, 1}, dw[]={1, 0, -1, 0};

int main() {
    int h, w, t, osz;
	int sh, sw, gh, gw;
	vector<int> oh, ow;
	cin>> h >> w >> t;
	vector<string> a(h);
	REP(i, h){
		cin>> a[i];
		REP(j, w){
			if(a[i][j]=='S'){
				sh=i;
				sw=j;
			}else if(a[i][j]=='G'){
				gh=i;
				gw=j;
			}else if(a[i][j]=='o'){
				oh.push_back(i);
				ow.push_back(j);
			}
		}
	}
	osz=oh.size();
	vector<vector<vector<int>>> dis;
	vector<vector<int>> disg;
	dis.resize(2+osz);
	REP(i, 2+osz) dis[i].resize(h);
	REP(i, 2+osz){
		REP(j, h) dis[i][j].resize(w, INF);
	}
	disg.resize(h);
	REP(i, h) disg[i].resize(w, INF);

	REP(i, 1+osz){
		queue<int> qh, qw, qd;
		if(i==0){
			qh.push(sh);
			qw.push(sw);
		}else{
			qh.push(oh[i-2]);
			qw.push(ow[i-2]);
		}
		qd.push(0);
		dis[i][qh.front()][qw.front()]=0;

		while(!qd.empty()){
			int ch=qh.front();
			int cw=qw.front();
			int cd=qd.front();
			qh.pop();
			qw.pop();
			qd.pop();
			REP(j, 4){
				int cch=ch+dh[j];
				int ccw=cw+dw[j];
				// cout<< cch << " " << ccw <<endl;
				if(cch<0 || h<=cch || ccw<0 || w<=ccw) continue;
				if(a[cch][ccw]=='#') continue;
				if(dis[i][cch][ccw]<=cd) continue;
				dis[i][cch][ccw]=cd+1;
				qh.push(cch);
				qw.push(ccw);
				qd.push(cd+1);
			}
		}

		G[i][0]=dis[i][sh][sw];
		REP(j, osz){
			G[i][j+1]=dis[i][oh[j]][ow[j]];
		}

		// REP(j, h){
		// 	REP(k, w){
		// 		cout<< dis[i][j][k] << " ";
		// 	}
		// 	cout<< endl;
		// }
	}
	// REP(i, osz) G[i][0]=disg[oh[i]][ow[i]];
	
	queue<int> qh, qw, qd;
	qh.push(gh);
	qw.push(gw);
	qd.push(0);
	disg[qh.front()][qw.front()]=0;

	while(!qd.empty()){
		int ch=qh.front();
		int cw=qw.front();
		int cd=qd.front();
		qh.pop();
		qw.pop();
		qd.pop();
		REP(j, 4){
			int cch=ch+dh[j];
			int ccw=cw+dw[j];
			// cout<< cch << " " << ccw <<endl;
			if(cch<0 || h<=cch || ccw<0 || w<=ccw) continue;
			if(a[cch][ccw]=='#') continue;
			if(disg[cch][ccw]<=cd) continue;
			disg[cch][ccw]=cd+1;
			qh.push(cch);
			qw.push(ccw);
			qd.push(cd+1);
		}
	}

    // // グラフの初期化
    // REP(i, 20) {
    //     REP(j, 20){
	// 		cout<< G[i][j] << " ";
	// 	}
	// 	cout<< endl;
    // }
	// return 0;

    // dp の初期化
    REP(i, 300000) {
        REP(j, 20) { dp[i][j] = INF; }
    }
    dp[0][0] = 0;  // スタートを頂点 0 とする

	V=osz;

    REP(S, 1 << V) {
        REP(v, V) {
            REP(u, V) {
                if (S != 0 && !(S & (1 << u))) continue; // u を含まない場合を除く
                if ((S & (1 << v)) == 0) {
                    if (v != u) chmin(dp[S | (1 << v)][v], dp[S][u] + G[u][v]);
                }
            }
        }
    }

	int ma;
	// cout<< disg[sh][sw] <<endl;
	if(disg[sh][sw]<=t) ma=0;
	else{
		cout<< -1 <<endl;
		return 0;
	}
	REP(S, 1 << V) {
		cout<< dp[S][0] << " " << S << " " << __builtin_popcount(S) <<endl;
		REP(j, osz){
			if (dp[S][j]+disg[oh[j]][ow[j]]<=t) {
				ma=max(ma, __builtin_popcount(S));
			}
		}
	}
	cout<< ma <<endl;

    return 0;
}