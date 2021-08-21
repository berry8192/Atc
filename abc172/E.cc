#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

LLi mod=1000000007;

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

int main(){

	LLi n, m, ans=0, tmp;
	vector<LLi> v;
	vector<LLi> con(1), par;

	cin>> n >> m;
	par.resize(m+1);
	
	con[0]=1;
	for(int i=1;i<=m;i++){
		tmp=con[i-1];
		tmp*=n+1-i;
		tmp=tmp%mod;
		tmp*=modinv((LLi)i);
		tmp=tmp%mod;
		con.push_back(tmp);
		//cout<< n << "C" << i << "=" << con[i] <<endl;
	}

	par[m]=1;
	for(int i=0;i<n;i++){
		par[m]*=(m-i);
		par[m]=par[m]%mod;
	}
	for(int i=m-1;i>0;i--){
		par[i]=par[i+1]*modinv((LLi)i+1);
		par[i]=par[i]%mod;
	}
	par[0]=1;

	//rep(i, m+1) cout<< par[i] <<endl;

	for(int i=0;i<=n;i++){
		tmp=con[i]*par[m-i];
		tmp=tmp%mod;
		if(i%2==0) ans+=tmp;
		else ans-=tmp;
		ans=(mod+ans)%mod;
	}

	ans*=par[m];
	ans=ans%mod;

	cout<< ans << endl;
 
	return 0;
}