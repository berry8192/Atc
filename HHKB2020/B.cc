#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int a, b, ans=0;
	cin>> a >> b;
	vector< vector<char> > board;
	board.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);

	for(int i=0;i<a;i++){
		string tmp;
		cin>> tmp;
		for(int j=0;j<b;j++){
			board[i][j]=tmp[j];
		}
	}
	
	for(int i=0;i<a;i++){
		for(int j=1;j<b;j++){
			if(board[i][j]=='.' && board[i][j-1]=='.') ans++;
		}
	}

	for(int i=0;i<b;i++){
		for(int j=1;j<a;j++){
			if(board[j][i]=='.' && board[j-1][i]=='.') ans++;
		}
	}

	cout<< ans << endl;
 
	return 0;
}