#include <bits/stdc++.h>
using namespace std;

int a, b, ans=0;
vector< vector<int> > board;
//vector< vector<int> > seen;
vector< vector<int> > dis;
queue<int> qh, qw;

void bfs(int h, int w){
	//移動してきた時の処理
	/*if(seen[h][w]) return;
	seen[h][w]=1;*///一度踏んだらもう踏めなくする（いる？）

	//移動する処理
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if(i==0 && j==0) continue;
			if(i*j!=0) continue;//8方向にする場合はコメントアウト
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

	cin>> a >> b;
	board.resize(a);
	dis.resize(a);
	//seen.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);
	//for(int i=0;i<a;i++) dis[i].resize(b, 9999999);
	//for(int i=0;i<a;i++) seen[i].resize(b, 0);

	//1字ずつ入力する場合
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cin>> board[i][j];
		}
	}

	//dis表示
	for(int i=0;i<b;i++){
		for(int j=0;j<a;j++){
			cout<< board[j][i] << " ";
		}
		cout<< endl;
	}

	return 0;
}