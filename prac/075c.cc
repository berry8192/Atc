#include <bits/stdc++.h>
#include <vector>
#include <cmath>

using namespace std;

int n;
int cnt;
vector< vector<int> > board;

void sol(vector< vector<int> > board, vector<int> che, int now){
	int jud=1;

	for(int i=1;i<n;i++) jud*=che[i];
	if(jud==1){
		for(int i=2;i<n;i++) che[i]=0;
		che[1]=1;
		cnt--;
		return;
	}

	for(int i=1;i<n;i++){
		if(board[now][i]>=1 && che[i]==0){
			board[now][i]--;
			che[i]=1;
			sol(board, che, i);
			//board[now][i]=1;
			//che[i]=0;
		}
	}

		
}

int main(){

	int m, a, b;
	vector<int> che;

	cin>> n >> m;
	n++;

	cnt=m;

	che.resize(n);
	for(int i=2;i<n;i++) che[i]=0;
	che[1]=1;
	board.resize(n);
	for(int i=0;i<n;i++) board[i].resize(n);

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			board[i][j]=0;
		}
	}

	for(int i=0;i<m;i++){
		cin>> a >> b;
		board[a][b]=5;
		board[b][a]=5;
	}

	for(int i=1;i<n;i++){
		for(int j=1;j<i;j++){
			if(board[i][j]==5){
				board[i][j]=0;
				board[j][i]=0;
				sol(board, che, 1);
				board[i][j]=5;
				board[j][i]=5;
			}
		}
	}

	cout<< cnt << endl;


}
