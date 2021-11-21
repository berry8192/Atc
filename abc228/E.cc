#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
//LLi mod=1000000007;
LLi mod=998244353;

//new mod pow
LLi modpow(LLi a, LLi n) {
	a=a%mod;
    LLi res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int main(){

	LLi n, k, m, r, ans=0;
	vector<int> v;

	cin>> n >> k >> m;
	if(m%mod==0){
		cout<< 0 <<endl;
		return 0;
	}
	mod--;
	r=modpow(k, n);
	mod++;
	ans=modpow(m, r);

	cout<< ans << endl;
 
	return 0;
}