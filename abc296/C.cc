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

	int n, x, ans=0;
	vector<int> v;
	set<int> st;

	cin>> n >> x;
	v.resize(n);

	if(x==0){
		cout<< "Yes" << endl;
		return 0;
	}

	rep(i, n){
		cin >> v[i];
		int f1=v[i]-x, f2=v[i]+x;
		if(st.find(f1)!=st.end() || st.find(f2)!=st.end()){
			cout<< "Yes" << endl;
			return 0;
		}
		st.insert(v[i]);
	}

	cout<< "No" << endl;
 
	return 0;
}