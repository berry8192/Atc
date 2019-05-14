#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main(){

	int h, w;
	vector< vector<char> > board;

	cin>> h >> w;
	board.resize(h+2);

	for(int i=0;i<h+2;i++) board[i].resize(w+2);

	for(int i=0;i<h+2;i++){
		for(int j=0;j<w+2;j++){
			if(i==0 || j==0 || i==h+1 || j==w+1){
				board[i][j]='#';
			}else{
				cin>> board[i][j];
			}
		}
	}

	for(int i=0;i<h+2;i++){
		for(int j=0;j<w+2;j++){
			cout<< board[i][j];
		}
		cout<< endl;
	}

}
