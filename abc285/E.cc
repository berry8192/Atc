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

	ll n, ans=0;
	vector<ll> a, aa;

	cin>> n;
	vector<ll> dp(n);
	a.resize(n);

	rep(i, n) cin >> a[i];
	if(n==1){
		cout<< 0 <<endl;
		return 0;
	}
	if(n==2){
		cout<< a[0] <<endl;
		return 0;
	}
	aa=ruiseki(a);
	// PV(aa);

	// rep3(i, n, 1){
	// 	int lp=i*2+1;
	// 	int st=n/lp;
	// 	// 最後尾に
	// }
	ans=aa[n/2]+aa[(n-1)/2];

	// dp[i] i番目を休みとするときのi番目まででの最大値
	rep3(i, n, 3){
		// 連続して休みを置く必要がない
		rep(j, i-2){
			ll sa=i-j;
			ll tmp=aa[sa/2]+aa[(sa-1)/2];
			dp[i]=max(dp[i], dp[j]+tmp);
			ll sa2=n-i;
			ll tmp2=aa[sa2/2]+aa[(sa2-1)/2];
			ans=max(ans, dp[j]+tmp+tmp2);
		}
	}

	cout<< ans << endl;
 
	return 0;
}