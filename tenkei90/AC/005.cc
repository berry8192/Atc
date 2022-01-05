#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;

string tob(LLi n, int lng=0, string fil="0")
{
    string r, rtn="";
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
	while(lng>r.size()) r+=fil;
    return r;
}

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
 
LLi modpow(LLi a, LLi n) {
    LLi res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

//modの各桁を配列で出す
// aは2とか10、bが各ステップでかける数、lenが長さ、mdがmod
vector<LLi> modvec(LLi a, LLi b, int len, LLi md){
	vector<LLi> rtn(len);
	rtn[0]=a;
	for(int i=1;i<len;i++){
		rtn[i]=(rtn[i-1]*b)%md;
		//rtn[i]=(rtn[i-1]*10)%md;
	}
	return rtn;
}

int main(){

	string bn;
	LLi n, b, k;
	vector<LLi> c, ten={10};
	vector< vector<LLi> > dp, ans;

	cin>> n >> b >> k;
	bn=tob(n, 64);
	//cout<< bn <<endl;
	c.resize(k);
	dp.resize(b);
	ans.resize(b);
	for(int i=0;i<b;i++) dp[i].resize(64);
	for(int i=0;i<b;i++) ans[i].resize(64);

	rep(i, k){
		cin >> c[i];
		dp[c[i]%b][0]++;
	}
	ans[0][0]=1;

	rep(i, 64){
		ten.push_back((ten[i]*ten[i])%b);
		//cout<< ten[i] SP;
	}
	//cout<< endl;

	rep(i, 64){
		rep(j, b){
			rep(l, b){
				//cout<< j SP << l SP << (j*ten[i]+l)%b <<endl;
				dp[(j*ten[i]+l)%b][i+1]+=dp[j][i]*dp[l][i];
				dp[(j*ten[i]+l)%b][i+1]%=mod;
			}
		}
	}

	//PVV(dp);
	//cout<< endl;

	rep(i, bn.size()){
		if(int(bn[i]-'0')){
			rep(j, b){
				rep(l, b){
					//cout<< j SP << l SP << (j*ten[i]+l)%b <<endl;
					ans[(j*ten[i]+l)%b][i+1]+=ans[j][i]*dp[l][i];
					ans[(j*ten[i]+l)%b][i+1]%=mod;
				}
			}
		}else{
			rep(j, b) ans[j][i+1]=ans[j][i];
		}
	}
	//PVV(ans);

	cout<< ans[0][63] <<endl;

	return 0;
}