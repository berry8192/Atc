#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;
ll mod=1000000007;

double TIME_LIMIT=900;

int dh[]={1, 0, -1, 0};
int dw[]={0, 1, 0, -1};
string dir="DRUL";

// 乱数の準備
auto seed=(unsigned)time(NULL);
// int seed=1;
mt19937 mt(seed);

template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int h, w;
	cin>> h >> w;
	vector<string> board(h);
	vector<vector<int>> dis(h, vector<int>(w, imax));
	queue<int> qh, qw;
	int sh, sw;

	rep(i, h){
		cin>> board[i];
		rep(j, w){
			if(board[i][j]=='S'){
				sh=i;
				sw=j;
			}
		}
	}

	rep(i, 4){
		if(sh+dh[i]<0 || h-1<sh+dh[i]) continue;
		if(sw+dw[i]<0 || w-1<sw+dw[i]) continue;
		if(board[sh+dh[i]][sw+dw[i]]=='.'){
			dis[sh+dh[i]][sw+dw[i]]=1+i;
			qh.push(sh+dh[i]);
			qw.push(sw+dw[i]);
		}
	}

	while (!qh.empty()) {
        int ch=qh.front();
        int cw=qw.front();
    	qh.pop();
    	qw.pop();
		rep(i, 4){
			int nh=ch+dh[i];
			int nw=cw+dw[i];
			if(nh<0 || h-1<nh) continue;
			if(nw<0 || w-1<nw) continue;
			if(board[nh][nw]!='.') continue;
			if(dis[nh][nw]==dis[ch][cw]) continue;
			if(dis[nh][nw]<5){
				// PVV(dis);
				cout<< "Yes" <<endl;
				return 0;
			}
			dis[nh][nw]=dis[ch][cw];
			qh.push(nh);
			qw.push(nw);
		}
	}

	// cout<< h SP << w <<endl;
	cout<< "No" <<endl;

	return 0;
}