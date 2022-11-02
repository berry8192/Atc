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

int main(){

	int h, w;
	cin>> h >> w;
	vector<string> board(h);
	vector<vector<int>> dis(h, vector<int>(w, imax));
	queue<int> qh, qw;

	rep(i, h){
		cin>> board[i];
	}

	qh.push(1);
	qw.push(1);
	dis[1][1]=0;
	while (!qh.empty()) { // 時間の許す限り回す
        int ch=qh.front();
        int cw=qw.front();
    	qh.pop();
    	qw.pop();
		rep(i, 4){
			int nh=ch+dh[i];
			int nw=cw+dw[i];
			if(nh<0 || h-1<nh) continue;
			if(nw<0 || w-1<nw) continue;
			if(board[nh][nw]=='#') continue;
			if(dis[nh][nw]<=dis[ch][cw]+1) continue;
			dis[nh][nw]=dis[ch][cw]+1;
			qh.push(nh);
			qw.push(nw);
		}
	}

	int ch=h-2;
	int cw=w-2;
	int cd=dis[ch][cw];
	while(dis[ch][cw]!=0){
		rep(i, 4){
			if(dis[ch+dh[i]][cw+dw[i]]==dis[ch][cw]-1){
				board[ch+dh[i]][cw+dw[i]]=dir[(i+2)%4];
				ch+=dh[i];
				cw+=dw[i];
				cd--;
				break;
			}
		}
	}
	board[h-2][w-2]='G';

	// cout<< h SP << w <<endl;
	rep(i, h) cout<< board[i] <<endl;

	return 0;
}