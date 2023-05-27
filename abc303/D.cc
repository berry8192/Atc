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

	ll x, y, z, ans1=0, ans2=0;
	string s;
	cin>> x >> y >> z;
	// cout<< x SP << y SP << z <<endl;
	cin>> s;
	ans2=z;

	rep(i, s.size()){
		if(s[i]=='a'){
			ll tmp=min(ans1+x, ans2+z+x);
			ans2=min(ans2+y, ans1+z+y);
			ans1=tmp;
		}else{
			ll tmp=min(ans1+y, ans2+z+y);
			ans2=min(ans2+x, ans1+z+x);
			ans1=tmp;
		}
		// cout<< min(ans1, ans2) << endl;
	}

	cout<< min(ans1, ans2) << endl;
 
	return 0;
}