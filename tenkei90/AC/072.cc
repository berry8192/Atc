#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;

int a, b, ans=0;
vector< vector<char> > board;

template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] << " ";
		}
		cout << endl;
	}
}

void dfs(vector< vector<int> > bo, int h, int w, int d){
	//移動してきた時の処理
	/*if(seen[h][w]) return;
	seen[h][w]=1;*///一度踏んだらもう踏めなくする（いる？）

	//移動する処理
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if(i==0 && j==0) continue;
			if(i*j!=0) continue;//8方向にする場合はコメントアウト
			if(-1<h+i && h+i<a && -1<w+j && w+j<b){
				if(bo[h+i][w+j]==0){
					ans=max(ans, d);
					//if(d==14) PVV(bo);
				}
				if(board[h+i][w+j]=='#' || bo[h+i][w+j]<=bo[h][w]+1) continue;
				//qh.push(h+i);
				//qw.push(w+j);
				int tmp=bo[h+i][w+j];
				bo[h+i][w+j]=bo[h][w]+1;
				dfs(bo, h+i, w+j, d+1);
				bo[h+i][w+j]=tmp;
			}
		}
	}
}

int main(){

	cin>> a >> b;
	board.resize(a);
	//seen.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);
	//for(int i=0;i<a;i++) seen[i].resize(b, 0);

	//1行ずつ入力する場合
	for(int i=0;i<a;i++){
		string tmp;
		cin>> tmp;
		for(int j=0;j<b;j++){
			board[i][j]=tmp[j];
		}
	}

	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			if(board[i][j]=='#') continue;
			vector< vector<int> > bo;
			bo.resize(a);
			for(int k=0;k<a;k++) bo[k].resize(b, 99);
			bo[i][j]=0;
			dfs(bo, i, j, 1);
		}
	}

	if(ans<4) ans=-1;
	cout<< ans <<endl;

	return 0;
}