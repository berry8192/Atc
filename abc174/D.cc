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

	int n, w=0, r=0, mi, tmp=0;
	string s;

	cin>> n >> s;

	rep(i, n){
		if(s[i]=='W') w++;
		else r++;
	}

	mi=min(w, r);

	rep(i, r) {
		if (s[i]=='W') tmp++;
	}

	cout<< min(mi, tmp) << endl;
 
	return 0;
}