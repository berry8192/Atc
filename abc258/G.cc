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
	vector<string> s;

	cin>> n;
	s.resize(n);
	// bitsetで高速に
	vector<bitset<3000>> v(n);

	rep(i, n){
		cin>> s[i];
		rep3(j, n, i+1){
			if(s[i][j]=='1') v[i].set(j, 1);
		}
	}

	rep(i, n){
		rep3(j, n, i+1){
			if(s[i][j]=='1'){
				auto tmp=(v[i]&v[j]);
				ans+=tmp.count();
				//cout<< i SP << j SP << tmp.count() << endl;
			}
		}
	}

	cout<< ans << endl;
 
	return 0;
}