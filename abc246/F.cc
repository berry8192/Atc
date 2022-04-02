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

LLi modpow(LLi a, LLi n) {
    LLi res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int main(){

	LLi n, l, ans=0;
	vector<string> s;

	cin>> n >> l;
	s.resize(n);

	rep(i, n) cin >> s[i];

	for (int bit = 1; bit < (1<<n); ++bit) {
		vector<int> st(26);
		//全ての桁に対する処理
        for (int i = 0; i < n; ++i) {
			//探索対象となっているbitかどうかを判定
            if(bit & (1<<i)){
				rep(j, s[i].size()){
					st[int(s[i][j]-'a')]++;
				}
			}
        }
		LLi tmp=0;
		rep(i, 26) if(st[i]==__builtin_popcount(bit)) tmp++;

		//cout<< bit SP << tmp <<endl;
		if(__builtin_popcount(bit)%2) ans+=modpow(tmp, l);
		else ans-=modpow(tmp, l);
		ans=(ans+mod)%mod;
		//cout<< bit SP << ans <<endl;
    }

	cout<< ans << endl;
 
	return 0;
}