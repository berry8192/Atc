#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

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

ll dp[410][410];
vector<ll> v, w;

ll dfs(int l, int r){
	if(dp[l][r]!=-1) return dp[l][r];
	if(l==r){
		//cout<< l SP << r SP << v[l] <<endl;
		dp[l][r]=v[l];
		return v[l];
	}
	ll tmp=lmax;
	for(int i=l;i<r;i++){
		tmp=min(tmp, dfs(l, i)+dfs(i+1, r));
	}
	dp[l][r]=tmp+w[r+1]-w[l];
	//cout<< l SP << r SP << tmp <<endl;
	return dp[l][r];
}

template <class T> vector<ll> ruiseki(T vv){
	vector<ll> xx;
  	xx.resize(vv.size()+1);
	xx[0]=0;
	for(int i=0;i<(int)vv.size();i++){
		xx[i+1]=xx[i]+vv[i];
		// xx[i+1]=xx[i+1]%mod;
	}
	return xx;
}

int main(){

	int n;

	cin>> n;
	v.resize(n);
	rep(i, 410) rep(j, 410){
		dp[i][j]=-1;
	}

	rep(i, n) cin >> v[i];
	w=ruiseki(v);

	cout<< dfs(0, n-1)-w[n] << endl;
 
	return 0;
}