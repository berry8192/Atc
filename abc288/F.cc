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

int main(){

	int n;
	string s;
	cin>> n;
	vector<int> x(n);
	vector<ll> he(n);
	ll ans=0;

	cin>> s;

	rep(i, n) x[i]=s[i]-'0';
	// PV(x);
	he[0]=x[0];
	rep3(i, n, 1) he[i]=(10*he[i-1]+x[i])%mod;
	// PV(he);

	ll b1=0, b2=1, b3, b4;
	repr(i, n) {
		ans+=he[i]*keta;
		keta*=x[i];
		keta%=mod;
		base+=x[i];
	}

	cout<< ans << endl;
 
	return 0;
}