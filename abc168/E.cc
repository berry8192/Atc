#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

LLi mod=1000000007;
long double iv=0.0000000000000000009;

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

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

struct dv{
	long double di;
	LLi sm;

	bool operator<(const dv &in) const{
		return di!=in.di ? di<in.di : sm<in.sm;
	};
};

int main(){

	long long int n, a, b, ans=0, ba=0, l, u;
	vector<dv> v;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> a >> b;
		v[i].di=1.0*a/b;
		v[i].sm=abs(a)+abs(b);
	}
	sort(v.begin(), v.end());

	rep(i, n) {
		auto lb = lower_bound(all(v.di), -1/v[i].di-iv);
		auto ub = lower_bound(all(v.di), -1/v[i].di+iv);
		l=lb-v.begin();
		u=ub-v.begin();
		for(int j=l;j<u;j++){
			if(v[j]%v[i].sm==0 || v[i].sm%v[j]==0) ba++;
		}
	}

	ans=modpow(2, n)-1;
	ans=ans%mod;
	ans+=mod-ba;
	ans=ans%mod;

	cout<< ans << endl;
 
	return 0;
}