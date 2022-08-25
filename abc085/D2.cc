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

	ll n, h, ans=imax, us=0;
	vector<ll> a, b;

	cin>> n >> h;
	a.resize(n);
	b.resize(n);

	rep(i, n){
		cin >> a[i] >> b[i];
	}
	sort(all(a), greater<ll>());
	sort(all(b), greater<ll>());

	rep(i, n){
		if(b[i]<a[0]) break;
		h-=b[i];
		if(h<=0){
			ans=i+1;
			cout<< ans <<endl;
			return 0;
		}
		us++;
	}

	cout<< (h+a[0]-1)/a[0]+us <<endl;

	return 0;
}