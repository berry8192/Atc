#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define SP << " " 

using namespace std;

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

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

	long long int n, m, k, ans=0, tmp, div=998244353;
	vector<long long int> con(1);

	cin>> n >> m >> k;

	con[0]=1;
	rep(i, n){
		tmp=con[i];
		tmp*=n-1-i;
		tmp=tmp%div;
		tmp*=modinv(i+1, div);
		tmp=tmp%div;
		con.push_back(tmp);

		//cout<< con[i+1] <<endl;
	}
	//cout<< endl;

	rep(i, k+1) {
		tmp=m;
		tmp*=modpow(m-1, n-1-i, div);
		tmp=tmp%div;
		tmp*=con[i];
		tmp=tmp%div;

		ans+=tmp;
		ans=ans%div;
		//cout<< ans << endl;
	}

	cout<< ans << endl;
 
	return 0;
}