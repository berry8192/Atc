#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
using namespace atcoder;

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

	int n, m;
	ll su=0, ma=lmax;
	vector<int> v;
	vector<ll> c;

	cin>> n >> m;
	v.resize(n);
	c.resize(n);
	dsu d(n);

	rep(i, n){
		cin >> v[i];
		su+=v[i];
	}
	sort(all(v));
	// PV(v);

	rep(i, n-1) {
		if(abs(v[i]-v[i+1])<=1) d.merge(i, i+1);
	}
	if(v[0]==0 && v[n-1]==m-1) d.merge(0, n-1);

	vector<vector<int>> dd=d.groups();
	rep(i, dd.size()){
		ll tmp=0;
		rep(j, dd[i].size()){
			tmp+=v[dd[i][j]];
			// cout<< v[d.groups()[i][j]] SP;
		}
		// cout<< endl;
		// cout<< su-tmp <<endl;
		ma=min(ma, su-tmp);
	}

	cout<< ma << endl;
 
	return 0;
}