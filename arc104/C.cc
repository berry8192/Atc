#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod;

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
 
LLi modpow(LLi a, LLi n) {
    LLi res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int main(){

	LLi n, k, ans, ma;
	vector<LLi> v;
	LLi dp[505010];
	dp[0]=1;

	cin>> n >> k >> mod;

	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++){
			for(int l=1;l<=k;k++){
				
			}
		}
	}
	for(int i=n;i>=1;i--) v[i]=v[n-i+1];

	for(int i=1;i<=n;i++) cout<< v[i] << endl;
 
	return 0;
}