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
 
LLi modinv(LLi a) {
    LLi b = mod, u = 1, v = 0;
    while (b) {
        LLi t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= mod;
    if (u < 0) u += mod;
    return u;
}

int main(){

	int n;
	LLi sq=0, ans=0;
	vector<LLi> v;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		sq+=v[i]*v[i];
		sq=sq%mod;
		ans+=v[i];
	}

	ans=ans%mod;
	ans=ans*ans;
	ans=ans%mod;
	ans=ans+mod-sq;
	ans=ans%mod;
	ans=ans*modinv(2);
	ans=ans%mod;

	cout<< ans << endl;
 
	return 0;
}