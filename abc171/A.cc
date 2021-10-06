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

	char c;
	cin>> c;

	if('A'<=c && c<='Z'){
		//大文字
		//cout<< "large" <<endl;

		//大文字を小文字に
		cout<< 'A' <<endl;
	}
	if('a'<=c && c<='z'){
		//小文字
		//cout<< "small" <<endl;

		//小文字を大文字に
		cout<< 'a' <<endl;
	}
 
	return 0;
}