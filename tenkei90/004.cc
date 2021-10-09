#include <bits/stdc++.h>
using namespace std;

int a, b, ans=0;
vector< vector<int> > board;
//vector< vector<int> > seen;
vector<int> suh, suw;

int main(){

	cin>> a >> b;
	board.resize(a);
	suh.resize(a);
	suw.resize(b);
	//seen.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);
	//for(int i=0;i<a;i++) seen[i].resize(b, 0);

	//1字ずつ入力する場合
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cin>> board[i][j];
		}
	}

	int tmp;
	for(int i=0;i<a;i++){
		tmp=0;
		for(int j=0;j<b;j++){
			tmp+=board[i][j];
		}
		suh[i]=tmp;
	}

	for(int i=0;i<b;i++){
		tmp=0;
		for(int j=0;j<a;j++){
			tmp+=board[j][i];
		}
		suw[i]=tmp;
	}

	//表示
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cout<< suh[i]+suw[j]-board[i][j] << " ";
		}
		cout<< endl;
	}

	return 0;
}