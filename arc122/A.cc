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

LLi modpow(LLi a, LLi n) {
    LLi res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
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

LLi modabs(LLi x){
	if(x>=0) return (x%mod);

	LLi tmp=abs(x);
	LLi di=(tmp+mod-1)/mod;
	return (mod*di+x)%mod;
}

int main(){

	int n;
	LLi ans=0;
	vector<int> v;
	vector<LLi> p, m, pp, mm;

	cin>> n;
	v.resize(n);
	p.resize(n+1);
	m.resize(n+1);
	pp.resize(n+1);
	mm.resize(n+1);

	rep(i, n) cin >> v[i];

	p[0]=1;
	for(int i=1;i<=n;i++) {
		p[i]=p[i-1]+m[i-1];
		m[i]=p[i-1];
		p[i]=p[i]%mod;
		m[i]=m[i]%mod;
		//cout<< p[i] << " " << m[i] <<endl;
	}
	
	/*pp[0]=p[n];
	for(int i=1;i<n;i++) {
		pp[i]=n-1*/
	ans+=v[0]*p[n];
	ans=ans%mod;
	for(int i=1;i<n;i++) {
		//cout<< v[i] << " " << (mod+p[n-i]-m[n-i])%mod <<endl;
		ans+=(v[i]*(mod+p[n-i]*p[i]-m[n-i]*m[i])%mod)%mod;
		ans=ans%mod;
		//cout<< ans <<endl;
	}

	cout<< ans <<endl;

	return 0;
}