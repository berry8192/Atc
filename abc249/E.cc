#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int
#define ll long long
#define repi(i, a, b) for (int i = (int)(a); i < (int)(b); i++)

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
long long MOD;
long long fact[10000], inv_fact[10000], inv[10000];

// メモを計算する
void init() {
    // 初期値設定と1はじまりインデックスに直す
    fact[0] = 1;
    fact[1] = 1;
    inv[0] = 1;
    inv[1] = 1;
    inv_fact[0] = 1;
    inv_fact[1] = 1;
    // メモの計算
    repi(i, 2, 5000){
        // 階乗
        fact[i] = fact[i - 1] * i % MOD;
        // 逆元
        inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
        // 逆元の階乗
        inv_fact[i] = inv_fact[i - 1] * inv[i] % MOD;
    }
}

// 二項係数の実体
ll nCk(int n, int k) {
    ll x = fact[n]; // n!の計算
    ll y = inv_fact[n-k]; // (n-k)!の計算
    ll z = inv_fact[k]; // k!の計算
    if (n < k) return 0; // 例外処理
    if (n < 0 || k < 0) return 0; // 例外処理
    return x * ((y * z) % MOD) % MOD; //二項係数の計算
}

int main(){

	ll n, p, ans=0;
	vector<ll> s;

	cin>> n >> p;
	MOD=p;
	
  	init();

	//文字の入れ方
	s.resize(10010);
	s[0]=1;
	s[1]=26;
	for(int i=1;i<10000;i++) s[i+1]=(s[i]*25)%p;

	for(int i=0;i<(n-1)/2;i++){
		//i=文字の個数
		ans+=(nCk(n-1, i)*s[i+1])%p;
		//cout<< nCk(n-1, i-1) << " " << s[i+1] <<endl;
		ans%=p;
		//cout<< ans <<endl;
	}

	cout<< ans << endl;
 
	return 0;
}