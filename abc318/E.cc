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
	ll ans=0;
	vector<int> v;
	vector<vector<ll>> w;

	cin>> n;
	v.resize(n);
	w.resize(300010);

	rep(i, n){
		cin >> v[i];
		w[v[i]].push_back(i);
	}

	rep(i, 300010) {
		if (w[i].size()>1){
			ll tmp=0;
			int prev=w[i][0];
			// PV(w[i]);
			rep(j, w[i].size()){
				tmp+=(w[i][j]-prev-1)*j;
				prev=w[i][j];
				ans+=tmp;
				// cout<< ans <<endl;
			}
		}
	}

	cout<< ans << endl;
 
	return 0;
}