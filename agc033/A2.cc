#include <bits/stdc++.h>
#include <vector>

using namespace std;

vector< vector<int> > board;

int sol(int h, int w, int dep){
	if(0<h) board[h-1][w]=min(board[h-1][w], board[h][w]);
	if(h+1<a) board[h+1][w]=min(board[h+1][w], board[h][w]);
	if(0<w) board[h][w-1]=min(board[h][w-1], board[h][w]);
	if(w+1<b) board[h][w+1]=min(board[h][w+1], board[h][w]);

int main(){

	int a, b, mi=9999;
	char s;

	cin>> a >> b;
	board.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);

	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cin>> s;
			if(s=='#'){
				board[i][j]=1;
			}else{
				board[i][j]=0;
			}
		}
	}

	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			if(board[i][j]==1) continue;
			mi=min(mi, sol(i, j, 0));
		}
	}

	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cout<< board[i][j] << " ";
		}
		cout<< endl;
	}

}
