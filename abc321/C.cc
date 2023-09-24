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

vector<ll> ans;

void dfs(ll x){
	ans.push_back(x);
	int d=x%10;
	for(int i=d-1;i>=0;i--){
		ll tmp=10*x+i;
		dfs(tmp);
	}
}

int main(){

	int k;
	cin>> k;

	rep3(i, 10, 1) dfs(i);
	sort(all(ans));
	// rep(i, 30) cout<< ans[i] <<endl;

	cout<< ans[k-1] << endl;
	// PV(ans);

	return 0;
}