#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
vector<LLi> fac(1), facin(1);

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

//xCyを計算
LLi conb(LLi x, LLi y){
	if(x<y) cout<< "conb x<y" << x SP << y <<endl;
	return ((fac[x]*facin[y])%mod*facin[x-y])%mod;
}

int main(){

	LLi s, ans=0, lmt, ba, tmp;

	cin>> s;

	if(s<3){
		cout<< 0<<endl;
		return 0;
	}
	
	fac[0]=1;
	facin[0]=1;
	for(int i=1;i<=4010;i++){
		tmp=fac[i-1];
		tmp*=i;
		tmp=tmp%mod;
		fac.push_back(tmp);
		facin.push_back(modinv(tmp));
		//cout<< fac[i] << " " << facin[i] << " " << (fac[i]*facin[i])%mod <<endl;
	}

	lmt=s/3;

	for(LLi i=1;i<=lmt;i++) {
		ba=s-i*3;
		ans+=(conb(ba+i-1, ba)%mod);
		ans=ans%mod;
	}

	cout<< ans << endl;
 
	return 0;
}