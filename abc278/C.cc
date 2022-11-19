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

	int n, q, ans=0;
	set<ll> st;

	cin>> n >> q;
	vector<ll> t(q), a(q), b(q);
	st.insert(-1);

	rep(i, q){
		cin >> t[i] >> a[i] >> b[i];
		a[i]--;
		b[i]--;
		ll tmp=a[i]*1000000000+b[i];
		ll tmp2=b[i]*1000000000+a[i];
		if(t[i]==1){
			st.insert(tmp);
		}else if(t[i]==2){
			st.erase(tmp);
		}else{
			if(st.find(tmp)!=st.end() && st.find(tmp2)!=st.end()) cout<< "Yes" << endl;
			else cout<< "No" << endl;
		}
	}
 
	return 0;
}