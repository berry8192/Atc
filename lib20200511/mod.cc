#include <bits/stdc++.h>
using namespace std;

long long int mod=1000000007;
 
long long int modinv(long long int a, long long int m) {
    long long int b = m, u = 1, v = 0;
    while (b) {
        long long int t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= m;
    if (u < 0) u += m;
    return u;
}
 
long long int modpow(long long int a, long long int n, long long int mod) {
    long long int res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int main(){

	int n;
	long long int tmp, ans=1;
	vector<long long int> con(1), par(1), fra(1);
	cin>> n;

	//nCxをメモ化
	con[0]=1;
	for(int i=1;i<=n;i++){
		tmp=con[i-1];
		tmp*=n+1-i;
		tmp=tmp%mod;
		tmp*=modinv(i, mod);
		tmp=tmp%mod;
		con.push_back(tmp);
		//cout<< con[i] <<endl;
	}

	//nPxをメモ化
	par[0]=1;
	for(int i=1;i<=n;i++){
		tmp=par[i-1];
		tmp*=n+1-i;
		tmp=tmp%mod;
		par.push_back(tmp);
		//cout<< par[i] <<endl;
	}

	//x!をメモ化
	fra[0]=1;
	for(int i=1;i<=n;i++){
		tmp=fra[i-1];
		tmp*=i;
		tmp=tmp%mod;
		fra.push_back(tmp);
		//cout<< fra[i] <<endl;
	}

	/*
	ans+=x;
	ans+=mod-x;
	ans*=x;
	ans*=modinv(x, mod);
	ans*=modpow(x, y, mod);
	ans=ans%mod;
	*/

	return 0;
}