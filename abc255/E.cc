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

	int n, m, ma=0;
	vector<ll> s, x, v;
	map<ll, int> mp;

	cin>> n >> m;
	s.resize(n-1);
	x.resize(m);
	v.resize(n);

	rep(i, n-1) cin >> s[i];
	rep(i, m) cin >> x[i];

	rep3(i, n, 1) {
		v[i]=s[i-1]-v[i-1];
	}
	//PV(v);

	rep(i, n){
		rep(j, m){
			if(i%2==0) mp[x[j]-v[i]]++;
			else mp[v[i]-x[j]]++;
		}
	}

	for (auto p : mp) {
  		//auto key = p.first;
  		auto val = p.second;
  		// key, valを使う
		ma=max(ma, val);
	}

	cout<< ma << endl;
 
	return 0;
}