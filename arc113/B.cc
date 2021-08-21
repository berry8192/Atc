#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
LLi llimax=9223372036854775807;
LLi mod=1000000007;

void PVL(vector<long long> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

long long modpow(long long a, long long n, long long mod) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int main(){

	long long a, d, tmp;
	long long sz, p, b, c;
	cin>> a >> b >> c;
	vector<long long> v;

	d=a%10;
	tmp=d;

	v.push_back(d);
	while(tmp>0){
		tmp*=d;
		tmp=tmp%10;
		//cout<< tmp <<endl;
		if(tmp==v[0]) break;
		v.push_back(tmp);
	}
	//PVL(v);

	sz=v.size();
	p=modpow(b, c, sz);
	p=(p-1+sz)%sz;

	cout<< v[p] <<endl;
 
	return 0;
}