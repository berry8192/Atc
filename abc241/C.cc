#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int n, tmp;
	vector<int> v;
	vector< vector<char> > board, board2;

	cin>> n;

	board.resize(n);
	for(int i=0;i<n;i++) board[i].resize(n);
	board2.resize(n);
	for(int i=0;i<n;i++) board2[i].resize(n);

	for(int i=0;i<n;i++){
		string tmp;
		cin>> tmp;
		for(int j=0;j<n;j++){
			board[i][j]=tmp[j];
		}
	}

	rep(i, n) {
		tmp=0;
		rep(j, n) {
			if(board[i][j]=='#') tmp++;
			if(j-6>=0 && board[i][j-6]=='#') tmp--;
			if(tmp>=4){
				cout<< "Yes" <<endl;
				return 0;
			}
		}
	}

	rep(i, n) {
		tmp=0;
		rep(j, n) {
			if(board[j][i]=='#') tmp++;
			if(j-6>=0 && board[j-6][i]=='#') tmp--;
			if(tmp>=4){
				cout<< "Yes" <<endl;
				return 0;
			}
		}
	}

	rep(i, n-5) {
		tmp=0;
		rep(j, n) {
			if(i+j>=n) break;
			if(board[i+j][j]=='#') tmp++;
			if(j-6>=0 && board[i+j-6][j-6]=='#') tmp--;
			if(tmp>=4){
				cout<< "Yes" <<endl;
				return 0;
			}
		}
	}

	rep(i, n-5) {
		tmp=0;
		rep(j, n) {
			if(i+j>=n) break;
			if(board[j][i+j]=='#') tmp++;
			if(j-6>=0 && board[j-6][i+j-6]=='#') tmp--;
			if(tmp>=4){
				cout<< "Yes" <<endl;
				return 0;
			}
		}
	}

	rep(i, n){
		rep(j, n){
			board2[i][j]=board[i][n-1-j];
		}
	}

	rep(i, n-5) {
		tmp=0;
		rep(j, n) {
			if(i+j>=n) break;
			if(board2[i+j][j]=='#') tmp++;
			if(j-6>=0 && board2[i+j-6][j-6]=='#') tmp--;
			if(tmp>=4){
				cout<< "Yes" <<endl;
				return 0;
			}
		}
	}

	rep(i, n-5) {
		tmp=0;
		rep(j, n) {
			if(i+j>=n) break;
			if(board2[j][i+j]=='#') tmp++;
			if(j-6>=0 && board2[j-6][i+j-6]=='#') tmp--;
			if(tmp>=4){
				cout<< "Yes" <<endl;
				return 0;
			}
		}
	}
	
	cout<< "No" << endl;
 
	return 0;
}
/*
6
......
.####.
...#..
....#.
.....#
......
*/