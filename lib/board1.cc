#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main(){

	int a, b;
	vector< vector<int> > board;

	cin>> a >> b;
	a+=2;
	b+=2;

	board.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);

	for(int i=0;i<a;i++){
		board[i][0]=-9;
		board[i][b-1]=-9;
	}
	for(int i=0;i<b;i++){
		board[0][i]=-9;
		board[a-1][i]=-9;
	}

	for(int i=0;i<a-2;i++){
		for(int j=0;j<b-2;j++){
			/* '#='NG, '.'=OK
			if(s[j]=='#') board[i+1][j+1]=-9;
			else board[i+1][j+1]=0;*/
			cin>> board[i+1][j+1];
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

-1
-2
-3
-4
-5
-6
-9 -9 -9 -9 -9
-9  1  2  3 -9
-9  4  5  6 -9
-9 -9 -9 -9 -9
*/
