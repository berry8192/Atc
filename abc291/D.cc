#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
using mint = modint998244353;

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
	cin>> n;
	vector<int> a(n), b(n);
	vector<mint> dp1(n), dp2(n);

	rep(i, n) cin >> a[i] >> b[i];
	dp1[0]=1;
	dp2[0]=1;

	rep3(i, n, 1) {
		if(a[i-1]!=a[i]) dp1[i]+=dp1[i-1];
		if(b[i-1]!=a[i]) dp1[i]+=dp2[i-1];
		if(a[i-1]!=b[i]) dp2[i]+=dp1[i-1];
		if(b[i-1]!=b[i]) dp2[i]+=dp2[i-1];
	}
	mint ans=dp1[n-1]+dp2[n-1];

	cout<< ans.val() << endl;
 
	return 0;
}