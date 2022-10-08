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

	int n, m, k, ans=0, y;
	vector<vector<int>> v;
	vector<int> x;

	cin>> n >> m;
	v.resize(n);
	rep(i, n) v[i].resize(n);

	rep(i, m){
		cin >> k;
		x.clear();
		rep(j, k){
			cin>> y;
			rep(l, x.size()){
				v[y-1][x[l]-1]=1;
				v[x[l]-1][y-1]=1;
			}
			x.push_back(y);
		}
	}
		
	rep(i, n) {
		rep(j, n){
			if(v[i][j]) ans++;
		}
	}

	if(ans==n*(n-1)) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}