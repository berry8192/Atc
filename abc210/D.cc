#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=922337203685477580;

int main(){

	LLi a, b, c, ans=llimax;
	vector< vector<LLi> > boa, box, board, board2;

	cin>> a >> b >> c;
	boa.resize(a+1);
	box.resize(a+1);
	board.resize(a+1);
	board2.resize(a+1);
	for(int i=0;i<a+1;i++) boa[i].resize(b+1, llimax);
	for(int i=0;i<a+1;i++) box[i].resize(b+1, llimax);
	for(int i=0;i<a+1;i++) board[i].resize(b+1);
	for(int i=0;i<a+1;i++) board2[i].resize(b+1);

	for(int i=1;i<a+1;i++){
		for(int j=1;j<b+1;j++){
			cin>> board[i][j];
		}
	}
	for(int i=1;i<a+1;i++){
		for(int j=1;j<b+1;j++){
			board2[i][j]=board[i][b+1-j];
		}
	}
	
	// for(int i=1;i<a+1;i++){
	// 	for(int j=1;j<b+1;j++){
	// 		cout<< board2[i][j] << " ";
	// 	}
	// 	cout<< endl;
	// }

	for(int i=1;i<a+1;i++){
		for(int j=1;j<b+1;j++){
			boa[i][j]=min(min(boa[i-1][j]+c, boa[i][j-1]+c), board[i][j]);
			box[i][j]=min(boa[i-1][j], boa[i][j-1])+c+board[i][j];
			ans=min(ans, box[i][j]);
			//cout<< boa[i][j] << " ";
		}
		//cout<< endl;
	}
	boa.clear();
	box.clear();
	boa.resize(a+1);
	box.resize(a+1);
	for(int i=0;i<a+1;i++) boa[i].resize(b+1, llimax);
	for(int i=0;i<a+1;i++) box[i].resize(b+1, llimax);
	
	for(int i=1;i<a+1;i++){
		for(int j=1;j<b+1;j++){
			boa[i][j]=min(min(boa[i-1][j]+c, boa[i][j-1]+c), board2[i][j]);
			box[i][j]=min(boa[i-1][j], boa[i][j-1])+c+board2[i][j];
			ans=min(ans, box[i][j]);
			//cout<< boa[i][j] << " ";
		}
		//cout<< endl;
	}

	cout<< ans <<endl;

	return 0;
}