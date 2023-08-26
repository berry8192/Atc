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
	vector<int> v, rem;
	set<int> st;

	cin>> n;
	v.resize(n-1);
	rem.resize(n);

	rep(i, n-1) cin >> v[i];
	sort(all(v), greater<int>());
	repr(i, n-1){
		rem[i]=rem[i+1]+v[i];
	}
	// PV(rem);

	st.insert(v[0]);
	rep3(i, n/2-1, 1) {
		set<int> nst;
		for(auto s : st){
			if(s>rem[i]) nst.insert(s+v[i]);
			if(s<rem[i]) nst.insert(s-v[i]);
		}
		st=nst;
	}

	int ans=imax;
	for(auto s : st){
		ans=min(ans, abs(s));
	}

	cout<< ans << endl;
 
	return 0;
}