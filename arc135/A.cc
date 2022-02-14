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
        if (n & 1LL) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int main(){

	LLi x, flag, ans=1LL;
	vector< map<LLi, LLi> > v(100);

	cin>> x;
    v[0][x]++;

	rep(i, 100){
        flag=1LL;
        //cout<< "i=" << i <<endl;
        for (auto p : v[i]) {
            LLi key = p.first;
            LLi val = p.second;
            // key, valを使う
            //cout<< key << " " << val <<endl;
            if(key>4LL){
                v[i+1][key/2LL]+=val;
                v[i+1][(key+1LL)/2LL]+=val;
                // v[i+1][key/2LL]=v[i+1][key/2LL]%(mod-1);
                // v[i+1][(key+1LL)/2LL]=v[i+1][(key+1LL)/2LL]%(mod-1);
                flag=0LL;
            }else{
                v[i+1][key]+=val;
            }
	    }
        if(flag){
            for (auto p : v[i]) {
                LLi key = p.first;
                LLi val = p.second;
                // while(val!=1LL){
                //     if(val%2LL){
                //         ans*=key;
                //         ans%=mod;
                //         val--;
                //     }else{
                //         key=(key*key)%mod;
                //         val/=2LL;
                //     }
                // }
                // key, valを使う
                //cout<< key << " " << val <<endl;
                ans*=modpow(key, val)%mod;
                ans%=mod;
            }
            break;
        }
    }

	cout<< ans << endl;
 
	return 0;
}