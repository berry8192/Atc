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
ll mod=998244353;

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

ll n, m, q;

ll rui(ll h, ll w){
	ll tmp1=((h+1)/2)*((1+((h+1)/2-1)*m)%mod);
	tmp1%=mod;
	//cout<< "tmp1_1:" << tmp1 <<endl;
	tmp1=(w+1)/2*((tmp1+((w+1)/2-1)*((h+1)/2))%mod);
	tmp1%=mod;
	//cout<< "tmp1_2:" << tmp1 <<endl;
	ll tmp2=h/2*(((m+2)+(h/2-1)*m)%mod);
	tmp2%=mod;
	//cout<< "tmp2_1:" << tmp2 <<endl;
	tmp2=w/2*((tmp2+(w/2-1)*(h/2))%mod);
	tmp2%=mod;
	//cout<< "tmp2_2:" << tmp2 <<endl;
	//cout<< "rui:" << tmp1 SP << tmp2 <<endl;
	return (tmp1+tmp2)%mod;
}

int main(){
	cin>> n >> m >> q;

	vector<ll> a(q), b(q), c(q), d(q);

	rep(i, q) cin >> a[i] >> b[i] >> c[i] >> d[i];

	rep(i, q) {
		ll tmp=0;
		//cout<< "loop:" << i <<endl;
		tmp+=rui(b[i], d[i]);
		//cout<< tmp <<endl;
		tmp-=rui(a[i]-1, d[i]);
		//cout<< tmp <<endl;
		tmp-=rui(b[i], c[i]-1);
		//cout<< tmp <<endl;
		tmp+=rui(a[i]-1, c[i]-1);
		tmp%=mod;
		tmp=(tmp+mod)%mod;
		cout<< tmp <<endl;
	}
 
	return 0;
}