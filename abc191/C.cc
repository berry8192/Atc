#include <bits/stdc++.h>
using namespace std;

int a, b;
vector< vector<char> > board;

int main(){

	int ans=0;
	cin>> a >> b;
	board.resize(a);
	//seen.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);
	//for(int i=0;i<a;i++) seen[i].resize(b, 0);

	//1字ずつ入力する場合
	/*for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cin>> board[i][j];
		}
	}*/

	//1行ずつ入力する場合
	for(int i=0;i<a;i++){
		string tmp;
		cin>> tmp;
		for(int j=0;j<b;j++){
			board[i][j]=tmp[j];
		}
	}

	//dis表示
	int tmp2;
	for(int i=1;i<a-1;i++){
		for(int j=1;j<b-1;j++){
			tmp2=0;
			if(board[i][j]=='#') {
				for(int k=-1;k<=1;k++){
					for(int l=-1;l<=1;l++){
						if(k*l!=0) continue;
						if(board[i+k][j+l]=='.') tmp2++;
					}
				}
				if(tmp2==4) ans+=4;
				if(tmp2==3) ans+=2;
				if(tmp2==2 && board[i+1][j]!=board[i-1][j]) ans+=1;
			}else{
				for(int k=-1;k<=1;k++){
					for(int l=-1;l<=1;l++){
						if(k*l!=0) continue;
						if(board[i+k][j+l]=='#') tmp2++;
					}
				}
				if(tmp2==3) ans+=2;
				if(tmp2==2 && board[i+1][j]!=board[i-1][j]) ans+=1;
			}
		}
	}

	cout<< ans <<endl;

	return 0;
}