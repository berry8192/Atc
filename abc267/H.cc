#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

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

const int MAX = 110000;
const int MOD = 998244353;

long long fac[MAX], finv[MAX], inv[MAX];
// テーブルを作る前処理
void COMinit() {
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAX; i++){
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
        finv[i] = finv[i - 1] * inv[i] % MOD;
    }
}

// 二項係数計算
long long COM(int n, int k){
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}

ll s[11][1000010][2];

int main(){

    // 前処理
    COMinit();
	int n, m, ans=0;
	vector<int> v, d(11);

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		d[v[i]]++;
	}

	rep(i, 11){
		rep(j, 1000010){
			s[i][j][0]=0;
			s[i][j][1]=0;
		}
	}
	s[0][0][0]=1;

	for(int i=10;i>0;i--){
		repr(j, d[i]+1){
			if(j==0) break;
			s[i*j]
		}
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}