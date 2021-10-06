#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
vector<int> bi;
vector< vector<char> > board;
int a, b, k, ans=0;

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


void bitgen(int len){

	//生成完了時の処理
	if(len==0){
		//for(int i=0;i<bi.size();i++) cout<< bi[i] << " ";
		//cout<< endl;

		int su=0;

		//for(int l=0;l<bi.size();l++){
			for(int i=0;i<a;i++){
				for(int j=0;j<b;j++){
					if(board[i][j]=='#' && bi[i]==0 && bi[j+a]==0) su++;
				}
			}
		//}

		if(su==k) ans++;

		return;
	}

	//再帰部分
	for(int i=0;i<2;i++){
		bi[len-1]=i;
		bitgen(len-1);
	}
}

int main(){

	cin>> a >> b >> k;

	board.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);

	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cin>> board[i][j];
		}
	}

	bi.resize(a+b);
	bitgen(a+b);

	cout<< ans << endl;
 
	return 0;
}