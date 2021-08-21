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

	int n;
	LLi ans=1;
	vector<int> v;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];
	sort(v.begin(), v.end());

	rep(i, n) {
		ans*=(v[i]-i);
		ans=ans%mod;
	}

	cout<< ans << endl;
 
	return 0;
}