#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main(){

	int a, b;
	vector< vector<int> > board;

	cin>> a >> b;
	board.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);

	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cin>> board[i][j];
		}
	}

	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cout<< board[i][j] << " ";
		}
		cout<< endl;
	}

}

/*
a=2
b=3

1
2
3
4
5
6

1 2 3 
4 5 6 
*/
