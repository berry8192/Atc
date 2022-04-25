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

	int n;
	ll ans=0, ma, mv;
	vector<ll> v, a;

	cin>> n;
	v.resize(n);
	a.resize(n);

	rep(i, n) cin >> v[i];
	a[0]=(1LL<<v[0]);
	ma=v[0];
	mv=a[0];

	// rep(i, n-1) {
	// 	if(ma>v[i+1]) a[i+1]=a[i]+(1ll<<v[i+1]);
	// 	else if(ma==v[i+1]) a[i+1]=mv+(1ll<<(v[i+1]+1));
	// 	else a[i+1]=(1ll<<(v[i+1]));
	// 	if(ma<=v[i+1]){
	// 		ma=v[i+1];
	// 		mv=a[i+1];
	// 	}
	// }
	rep(i, n-1){
		if(a[i]<(1ll<<v[i+1])){
			//cout<< "t1" <<endl;
			a[i+1]=(1ll<<v[i+1]);
		}else if(a[i]%(1ll<<v[i+1]+1)==0){
			//cout<< "t2" <<endl;
			a[i+1]=a[i]+(1ll<<v[i+1]);
		}else{
			//cout<< "t3" <<endl;
			ll tmp=a[i]%(1ll<<v[i+1]);
			if((a[i]-tmp)%(1ll<<v[i+1]+1)==0){
				a[i+1]=a[i]-tmp+(1ll<<v[i+1]);
			}else{
				a[i+1]=a[i]-tmp+(1ll<<(v[i+1]+1));
			}
		}
	}
	//PV(a);

	cout<< a[n-1] << endl;
 
	return 0;
}