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

struct en{
	ll a;
	ll b;
	ll x;
	ll idx;

	bool operator<(const en &in) const{
		return a!=in.a ? a>in.a : idx<in.idx;
	};
};

int main(){

	ll n, m, ans=0;
	vector<ll> a, b, x;
	set<en> st;

	cin>> n >> m;
	a.resize(n);
	b.resize(n);
	x.resize(n);

	rep(i, n){
		cin >> a[i] >> b[i] >> x[i];
		if(x[i]){
			if(b[i]==1){
				st.insert({a[i], 1, 1, i+10000000});
			}else{
				st.insert({a[i]*2, 1, 1, i+10000000});
				st.insert({a[i], b[i]-1, 0, i});
			}
			ans+=a[i];
		}else{
			st.insert({a[i], b[i], 0, i});
		}
		ans+=(b[i]-1)*a[i];
	}
	// cout<< ans <<endl;

	while(m>0){
		en tmp=*st.begin();
		// cout<< tmp.a SP << tmp.b SP << tmp.x SP << tmp.idx <<endl;
		if(tmp.x){
			ans-=tmp.a;
			m--;
			st.erase(st.begin());
		}else{
			ans-=min(m, tmp.b-1)*tmp.a;
			m-=min(m, tmp.b-1);
			st.erase(st.begin());
		}
		if(st.empty()) break;
		// cout<< ans <<endl;
	}

	cout<< ans << endl;
 
	return 0;
}