#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=998244353;

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

	LLi a, b, c, ans;
	cin>> a >> b >> c;

	ans=c*(c+1)/2;
	ans=ans%mod;
	ans*=(b*(b+1)/2)%mod;
	ans=ans%mod;
	ans*=(a*(a+1)/2)%mod;
	ans=ans%mod;

	cout<< ans <<endl;
 
	return 0;
}