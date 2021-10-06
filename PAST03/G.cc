#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

int a, b, ans=0;
vector< vector<char> > board;
vector< vector<int> > dis;
queue<int> qh, qw;
int imax=2147483647;

void bfs(int h, int w){
	//移動してきた時の処理

	//移動する処理
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if(i==0 && j==0) continue;
			if(i==-1 && j==-1) continue;
			if(i==1 && j==-1) continue;
			if(-1<h+i && h+i<a && -1<w+j && w+j<b){
				if(board[h+i][w+j]=='#' || dis[h+i][w+j]<=dis[h][w]+1) continue;
				qh.push(h+i);
				qw.push(w+j);
				dis[h+i][w+j]=dis[h][w]+1;
			}
		}
	}
}

int main(){

	a=411;
	b=411;
	board.resize(a);
	dis.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b, '.');
	for(int i=0;i<a;i++) dis[i].resize(b, imax);
	
	int n, x, y, tx, ty;
	cin>> n >> x >> y;
	x+=205;
	y+=205;
	rep(i, n){
		cin>> tx >> ty;
		board[tx+205][ty+205]='#';
	}

	qh.push(205);
	qw.push(205);
	dis[205][205]=0;
  	while (!qh.empty()) {
    	bfs(qh.front(), qw.front());
    	qh.pop();
    	qw.pop();
  	}

	//dis表示
	/*for(int i=195;i<206;i++){
		for(int j=195;j<206;j++){
			if(i==x && j==y){
				cout<< dis[i][j] << "<";
				continue;
			}
			if(dis[i][j]==imax) cout<< "x ";
			else cout<< dis[i][j] << " ";
		}
		cout<< endl;
	}*/

	if(dis[x][y]!=imax) cout<< dis[x][y] <<endl;
	else cout<< "-1" <<endl;

	return 0;
}