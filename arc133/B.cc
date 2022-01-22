#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

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

	int n, x, mi;
	vector<int> p, q, qinv, dp;

	cin>> n;
	p.resize(n);
	q.resize(n);
	qinv.resize(n+1);
	dp.resize(n, imax);

	rep(i, n) cin >> p[i];
	rep(i, n){
		cin >> q[i];
		qinv[q[i]]=i;
	}

	// rep(i, n) {
	// 	x=p[i];
	// 	mi=99999999;
	// 	for(int j=x;j<=n;j+=x){
	// 		mi=qinv[j];
	// 		cout<< mi <<endl;
	// 		auto ub = lower_bound(all(dp), mi);
	// 		*ub=mi;
	// 		PV(dp);
	// 	}
	// }
	rep(i, n) {
		x=p[i];
		mi=99999999;
		for(int j=x;j<=n;j+=x){
			mi=min(mi, qinv[j]);
		}
		auto ub = upper_bound(all(dp), mi);
		*ub=mi;
		PV(dp);
	}
	dp.push_back(imax);

	rep(i, n+1){
		if(dp[i]==imax){
			cout<< i << endl;
			return 0;
		}
	}
	return 0;
}