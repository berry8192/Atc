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

	ll n, ans=0;
	vector<vector<ll>> v(10);

	cin>> n;
	rep(i, 10) v[i].resize(10);

	rep(i, n) {
		string s=to_string(i+1);
		v[int(s[0]-'0')][(i+1)%10]++;
	}

	// PVV(v);

	rep3(i, 10, 1){
		rep3(j, 10, 1){
			ans+=v[i][j]*v[j][i];
		}
	}

	cout<< ans << endl;
 
	return 0;
}