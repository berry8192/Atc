#include <bits/stdc++.h>
using namespace std;

int a, b, ans=0;
vector< vector<char> > board;
vector< vector<int> > seen;

void dfs(int h, int w){
	//移動してきた時の処理
	if(seen[h][w]) return;
	seen[h][w]=1;

	//移動する処理
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if(i==0 && j==0) continue;
			if(i*j!=0) continue;//8方向にする場合はコメントアウト
			if(-1<h+i && h+i<a && -1<w+j && w+j<b){
				dfs(h+i, w+j);
			}
		}
	}
}

int main(){

	cin>> a >> b;
	board.resize(a);
	seen.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);
	for(int i=0;i<a;i++) seen[i].resize(b, 0);

	//1字ずつ入力する場合
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cin>> board[i][j];
		}
	}

	//1行ずつ入力する場合
	for(int i=0;i<a;i++){
		string tmp;
		cin>> tmp;
		for(int j=0;j<b;j++){
			board[i][j]=tmp[j];
		}
	}

	//board表示
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cout<< board[i][j];
		}
		cout<< endl;
	}

	dfs(0, 0);

	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			if(seen[i][j]) ans++;
		}
	}

	cout<< ans <<endl;

	return 0;
}