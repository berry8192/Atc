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

//2 factor sort
struct cho{
	ll val;
	int idx;

	bool operator<(const cho &in) const{
		return val!=in.val ? val<in.val : idx<in.idx;
	};
};

int main(){

	ll n, m, pos=0, ma=0;
	ll ans=0;
	vector<ll> a, u, v;
	vector<cho> h;
	vector<set<int>> g;
	set<cho> st;

	cin>> n >> m;
	a.resize(n);
	h.resize(n);
	u.resize(m);
	v.resize(m);
	g.resize(n);

	rep(i, n){
		cin>> a[i];
		h[i].idx=i;
	}
	rep(i, m){
		cin>> u[i] >> v[i];
		u[i]--;
		v[i]--;
		g[u[i]].insert(v[i]);
		g[v[i]].insert(u[i]);
		h[u[i]].val+=a[v[i]];
		h[v[i]].val+=a[u[i]];
	}
	//sort(all(h));
	rep(i, n) st.insert(h[i]);
	//rep(i, n) cout<< h[i].idx SP << h[i].val <<endl;

	rep(i, n){
		cho tmp=*st.begin();
		ma=max(ma, tmp.val);
		//cout<< "del:" << tmp.idx SP << tmp.val <<endl;
		st.erase(tmp);
		for(auto itr = g[tmp.idx].begin(); itr != g[tmp.idx].end(); ++itr) {
			//cout<< "dec:" << *itr SP << h[*itr].val <<endl;
			g[*itr].erase(tmp.idx);
			st.erase(h[*itr]);
			h[*itr].val-=a[tmp.idx];
			st.insert(h[*itr]);
		}
		// for(auto itr = st.begin(); itr != st.end(); ++itr) {
		// 	cout << (*itr).val << " ";
		// }
		// cout<< endl;
	}

	cout<< ma << endl;
 
	return 0;
}