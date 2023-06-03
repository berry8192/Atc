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

	int n, m, k, Q;
	cin>> n >> m;
	vector<int> u(m), v(m);
	rep(i, m) cin >> u[i] >> v[i];
	cin>> k;
	vector<int> x(k), y(k);
	rep(i, k) cin >> x[i] >> y[i];
	cin>> Q;
	vector<int> p(Q), q(Q);
	rep(i, Q) cin >> p[i] >> q[i];
	dsu d(n);
	set<ll> st;

	rep(i, m) {
		d.merge(u[i]-1, v[i]-1);
	}
	rep(i, k){
		ll xx=d.leader(x[i]-1);
		ll yy=d.leader(y[i]-1);
		ll tmp=xx*1000000000+yy;
		st.insert(tmp);
		tmp=yy*1000000000+xx;
		st.insert(tmp);
	}
	rep(i, Q){
		ll xx=d.leader(p[i]-1);
		ll yy=d.leader(q[i]-1);
		ll tmp=xx*1000000000+yy;
		ll tmp2=yy*1000000000+xx;

		if(st.find(tmp)==st.end() && st.find(tmp2)==st.end()) cout<< "Yes" << endl;
		else cout<< "No" << endl;
	}
 
	return 0;
}