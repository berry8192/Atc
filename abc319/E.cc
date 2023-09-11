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

	ll n, x, y, q;
	cin>> n >> x >> y;
	vector<ll> p(n-1), t(n-1);
	rep(i, n-1) cin>> p[i] >> t[i];
	cin>> q;
	vector<ll> qq(q);
	rep(i, q) cin>> qq[i];

	vector<ll> use_time(840); // [時間]にバス停1についたとき、バス停Nまでの所要時間
	rep(i, 840){
		ll current_time=i;
		rep(j, n-1){
			while(current_time%p[j]) current_time++;
			current_time+=t[j];
		}
		use_time[i]=current_time-i;
	}

	rep(i, q) {
		cout<< qq[i]+use_time[(qq[i]+x)%840]+x+y <<endl;
	}
 
	return 0;
}