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

int main(){

	ll n, a, b, ans=0;
	vector<ll> v;

	cin>> n >> a >> b;
	v.resize(n);

	rep(i, n) cin >> v[i];

	ll ri, le, mi;
	ri=1000000001;
	le=0;
	while(ri-le>1){
		mi=(ri+le)/2;
		//cout<< mi <<endl;
		ll tmp=0;
		rep(i, n){
			ll d=v[i]-mi;
			if(0<d){
				tmp+=d/b;
			}else{
				tmp-=(-d+a-1)/a;
			}
		}
		if(tmp<0) ri=mi;
		else le=mi;
	}
	cout<< le <<endl;
 
	return 0;
}