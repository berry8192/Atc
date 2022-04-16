#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;
using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=998244353;

LLi fac[200010], finv[200010], inv[200010];

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
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

// テーブルを作る前処理
void COMinit() {
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < 200010; i++){
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = mod - inv[mod%i] * (mod / i) % mod;
        finv[i] = finv[i - 1] * inv[i] % mod;
    }
}

// 二項係数計算
long long COM(int n, int k){
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k] % mod) % mod;
}

int main(){

	int n, k;
	LLi ans, ma=0, mi=0;
	vector<LLi> v;
	// 二項係数
	COMinit();

	cin>> n >> k;
	v.resize(n);

	rep(i, n) cin >> v[i];
	sort(all(v));

	rep(i, n) {
		//自分が選ばれる
		//i=自分よりも小さい数の個数
		LLi tmp=COM(i, k-1)*v[i];
		tmp%=mod;
		//cout<< tmp <<endl;
		ma+=tmp;
		ma%=mod;
	}

	reverse(all(v));
	rep(i, n) {
		//自分が選ばれる
		//i=自分よりも大きい数の個数
		LLi tmp=COM(i, k-1)*v[i];
		tmp%=mod;
		//cout<< tmp <<endl;
		mi+=tmp;
		mi%=mod;
	}

	//cout<< ma SP << mi <<endl;
	ans=ma-mi+mod;
	ans%=mod;

	ans*=modinv(COM(n, k));
	ans%=mod;

	cout<< ans << endl;
 
	return 0;
}