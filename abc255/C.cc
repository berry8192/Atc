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

	ll x, a, d, n, ans;
	ll la;

	cin>> x >> a >> d >> n;

	la=a+(n-1)*d;

	if(0<=d){
		if(x<=a){
			cout<< a-x <<endl;
			return 0;
		}
		if(la<=x){
			cout<< x-la <<endl;
			return 0;
		}
	}else{
		if(x>=a){
			cout<< x-a <<endl;
			return 0;
		}
		if(la>=x){
			cout<< la-x <<endl;
			return 0;
		}
	}

	x-=a;
	x=abs(x)%abs(d);
	ans=x;
	ans=min(ans, abs(d)-x);

	cout<< ans << endl;
 
	return 0;
}