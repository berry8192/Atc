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

ll dp[100010][5];

int main(){

	int n, pos=0;
	ll ans=0;
	vector<ll> t, x, a;

	cin>> n;
	t.resize(n);
	x.resize(n);
	a.resize(n);

	rep(i, n) cin >> t[i] >> x[i] >> a[i];

	rep(i, 100010){
		rep(j, 5){
			dp[i][j]=-lmax;
		}
	}
	dp[0][0]=0;

	rep(i, t[n-1]+1) {
		if (t[pos]==i){
			dp[t[pos]][x[pos]]+=a[pos];
			pos++;
		}
		rep(j, 5){
			rep(k, 3){
				if(j+k-1==-1 || j+k-1==5) continue;
				dp[i+1][j]=max(dp[i+1][j], dp[i][j+k-1]);
			}
		}
		// rep(j, 5) cout<< dp[i][j] SP;
		// cout<< endl;
	}

	rep(i, 5) ans=max(ans, dp[t[n-1]][i]);

	cout<< ans << endl;
 
	return 0;
}