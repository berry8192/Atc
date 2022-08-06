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

	int n, l, r;
	ll su=0, mi;
	vector<ll> v, rl, rr;
	multiset<ll> st;
	cin>> n >> l >> r;
	v.resize(n);
	rl.resize(n);
	rr.resize(n);

	rep(i, n){
		cin >> v[i];
		su+=v[i];
	}

	rl[0]=l-v[0];
	rep3(i, n, 1) {
		rl[i]=rl[i-1]+l-v[i];
	}
	reverse(all(v));
	rr[0]=r-v[0];
	rep3(i, n, 1) {
		rr[i]=rr[i-1]+r-v[i];
	}
	// reverse(all(v));
	// PV(rl);
	//PV(rr);

	rep(i, n) st.insert(rr[i]);

	mi=min(su, su+*st.begin());
	rep(i, n){
		auto lb=st.lower_bound(rr[n-1-i]);
		st.erase(lb);
		auto itr=st.begin();
		ll tmp=*itr;
		if(st.empty()) tmp=0;
		// cout<< "i=" << i SP;
		// cout<< rl[i] SP << tmp <<endl;
		// for(auto itr2 = st.begin(); itr2 != st.end(); ++itr2) {
        // 	std::cout << *itr2 SP;      // イテレータの指す先のデータを表示
    	// }
		// cout<< endl;
		mi=min(mi, su+rl[i]+tmp);
	}

	cout<< mi << endl;
 
	return 0;
}