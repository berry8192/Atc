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

// 乱数の準備
auto seed=(unsigned)time(NULL);
// int seed=1;
mt19937 mt(seed);

int main(){

	int h, w;
	cin>> h >> w;
	string base;
	rep(i, w) base+='.';
	vector<string> board(h, base);

	rep(i, h){
		rep(j, w){
			if(i==0 || i==h-1 || j==0 || j==w-1) board[i][j]='#';
		}
	}

	//開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

	while (true) { // 時間の許す限り回す
        current = chrono::system_clock::now(); // 現在時刻
        if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) break;

		int start_h=(mt()%(h/2+1))*2;
		int start_w=(mt()%(w/2+1))*2;
		int cd=mt()%4;
		int lp=0;
		int search_h;
		int search_w;
		while(1){
			lp++;
			search_h=start_h+dh[cd]*lp;
			search_w=start_w+dw[cd]*lp;
			if(search_h<0 || h-1<search_h) break;
			if(search_w<0 || w-1<search_w) break;
			if(board[search_h][search_w]=='#') break;
		}
		if(lp<4) continue;
		lp/=2;
		lp--;
		lp=mt()%lp;
		lp++;
		lp*=2;
		// int goal_h=start_h+dh[cd]*lp;
		// int goal_w=start_w+dw[cd]*lp;

		if(board[start_h][start_w]!='#') continue;
		// if(goal_h<0 || h-1<goal_h) continue;
		// if(goal_w<0 || w-1<goal_w) continue;
		// if(board[goal_h][goal_w]=='#') continue;
		rep3(i, lp+1, 1) board[start_h+dh[cd]*i][start_w+dw[cd]*i]='#';
		// board[(goal_h+start_h)/2][(goal_w+start_w)/2]='#';
	}

	cout<< h SP << w <<endl;
	rep(i, h) cout<< board[i] <<endl;

	return 0;
}