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

	LLi a, ans=0;
	string b;

	cin>> a >> b;

	LLi tmp=(LLi)(b[0]-'0');
	ans+=(LLi)(a*tmp)*100;

	if(b.size()>2){
		tmp=(LLi)(b[2]-'0');
		ans+=(LLi)(a*tmp)*10;
	}

	if(b.size()>3){
		tmp=(LLi)(b[3]-'0');
		ans+=(LLi)(a*tmp);
	}

	cout<< ans/100 <<endl;
 
	return 0;
}