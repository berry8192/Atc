#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;

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

	string s;
	LLi e=1, a=0, b=0, c=0;

	cin>> s;

	rep(i, s.size()){
		if(s[i]=='?') c=(c*3)%mod;
		if(s[i]=='C' || s[i]=='?') c=(c+b)%mod;
		if(s[i]=='?') b=(b*3)%mod;
		if(s[i]=='B' || s[i]=='?') b=(b+a)%mod;
		if(s[i]=='?') a=(a*3)%mod;
		if(s[i]=='A' || s[i]=='?') a=(a+e)%mod;
		if(s[i]=='?') e=(e*3)%mod;
		//cout<< e SP << a SP << b SP << c <<endl;
	}
	
	cout<< c << endl;
 
	return 0;
}
