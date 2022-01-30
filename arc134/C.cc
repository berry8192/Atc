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
LLi mod=998244353;
vector<LLi> fac(1), facin(1);

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

//xCyを計算
LLi conb(LLi x, LLi y){
	// cout<< x SP << y <<endl;
	// if(x<y) cout<< "conb x<y" << x SP << y <<endl;
	// return ((fac[x]*facin[y])%mod*facin[x-y])%mod;
	y=min(y, x-y);
	LLi tmp=1;
	rep(i, y){
		tmp*=x-i;
		tmp%=mod;
		tmp*=modinv(1+i);
		tmp%=mod;
	}
	return tmp;
}

int main(){

	LLi n, k, ans=1, tmp, su=0;
	vector<LLi> v;

	cin>> n >> k;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		if(i) su+=v[i];
	}
	
	// fac[0]=1;
	// facin[0]=1;
	// for(int i=1;i<=n+k;i++){
	// 	tmp=fac[i-1];
	// 	tmp*=i;
	// 	tmp=tmp%mod;
	// 	fac.push_back(tmp);
	// 	facin.push_back(modinv(tmp));
	// 	//cout<< fac[i] << " " << facin[i] << " " << (fac[i]*facin[i])%mod <<endl;
	// }
	//cout<< conb(5, 3) <<endl;

	v[0]=v[0]-su-k;
	if(v[0]<0){
		cout<< 0 <<endl;
		return 0;
	}
	//cout<< "v1=" << v[0] <<endl;
	
	rep(i, n){
		tmp=conb(v[i]+k-1, v[i]);
		ans=(ans*tmp)%mod;
		//cout<< ans << endl;
	}
	cout<< ans << endl;
 
	return 0;
}