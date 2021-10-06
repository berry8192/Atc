#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=998244353;
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

LLi modabs(LLi x){
	if(x>=0) return (x%mod);

	LLi tmp=abs(x);
	LLi di=(tmp+mod-1)/mod;
	return (mod*di+x)%mod;
}

//xCyを計算
LLi conb(LLi x, LLi y){
	if(x<y) cout<< "conb x<y" << x SP << y <<endl;
	return ((fac[x]*facin[y])%mod*facin[x-y])%mod;
}

int main(){

	int n, tmp;
	LLi l, r, m, fig;
	vector<int> v, f(1), g(1);
	vector<LLi> tw(1), d(10);
	//2^index が入っている
	tw[0]=1;
	rep(i, n+1){
		tw.push_back((tw[i]*2)%mod);
	}

	fac[0]=1;
	facin[0]=1;
	for(int i=1;i<=n;i++){
		tmp=fac[i-1];
		tmp*=i;
		tmp=tmp%mod;
		fac.push_back(tmp);
		facin.push_back(modinv(tmp));
		//cout<< fac[i] << " " << facin[i] << " " << (fac[i]*facin[i])%mod <<endl;
	}

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];
	f[0]=v[0];
	g[0]=v[n-1];

	tmp=f[0];
	rep(i, n-1) {
		f.push_back((tmp+v[i+1])%10);
		tmp=(tmp+v[i+1])%10;
	}
	tmp=g[0];
	for(int i=n-2;i>=0;i--) {
		g.push_back((tmp*v[i])%10);
		tmp=(tmp*v[i])%10;
	}
	//PV(f);
	//PV(g);
	//PVL(tw);
	//F, Gの操作を合計n-1回行う

	if(n==2){
		d[(v[0]+v[1])%10]++;
		d[(v[0]*v[1])%10]++;
	}else{
		rep(i, n){
			//Fをi回、Gをn-i-1回行う
			if(i==0){
				d[g[n-1]]++;
				continue;
			}
			if(i==n-1){
				d[f[n-1]]++;
				continue;
			}
			l=f[i-1];
			r=g[n-i-2];
			m=v[i];
			cout<< l SP << m SP << r << endl;
			if(n>3) fig=conb(n-3, i-1);
			else fig=1;
			d[((l+m)*r)%10]+=fig;
			d[((l+m)*r)%10]=d[((l+m)*r)%10]%mod;
			d[(l+m*r)%10]+=fig;
			d[(l+m*r)%10]=d[(l+m*r)%10]%mod;
		}
	}

	rep(i, 10) cout<< d[i] <<endl;
 
	return 0;
}