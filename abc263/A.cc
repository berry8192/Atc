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

	int n, ans=1;
	vector<int> v(5);

	rep(i, 5) cin >> v[i];
	sort(all(v));

	if(v[0]==v[1] && v[1]==v[2] && v[3]==v[4]){
		cout<< "Yes" << endl;
		return 0;
	}
	reverse(all(v));
	if(v[0]==v[1] && v[1]==v[2] && v[3]==v[4]){
		cout<< "Yes" << endl;
		return 0;
	}
	else cout<< "No" << endl;
 
	return 0;
}