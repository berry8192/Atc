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

	ll n, hav=0, su=0, rem;
	cin>> n;
	vector<ll> x(n), y(n), z(n), v, zz;

	rep(i, n){
		cin >> x[i] >> y[i] >> z[i];
		su+=z[i];
		if(y[i]>x[i]){
			v.push_back(((y[i]-x[i])+1)/2);
			zz.push_back(z[i]);
		}else{
			hav+=z[i];
		}
	}
	rem=su-2*hav+1;
	rem/=2;
	// cout<< su SP << hav SP << rem <<endl;
	// cout<< su-hav-rem SP << hav+rem <<endl;
	if(hav*2>su){
		cout<< 0 <<endl;
		return 0;
	}
	// PV(v);
	// PV(zz);
	vector<vector<ll>> dp(v.size()+1, vector<ll>(su+1, lmax/2));
	// dp[i地区目までみて][もらえる票がjのとき]=val人鞍替え
	dp[0][0]=0;
	rep(i, v.size()){
		// v[i]=地区iのz[i]人を獲得するために必要な鞍替え人数
		rep(j, su+1){
			dp[i+1][j]=dp[i][j];
			// if(i==v.size()-1 && j==65) cout<< "##" << dp[i][j-zz[i]] SP << v[i] <<endl;
			if(j-zz[i]>=0) dp[i+1][j]=min(dp[i][j-zz[i]]+v[i], dp[i+1][j]);
			// cout<< dp[i][j-z[i]]+v[i] SP;
			// if(dp[i+1][j]<1000000000) cout<< dp[i+1][j] SP;
			// else cout<< -1 SP;
		}
		// cout<<endl;
	}
	ll ans=lmax;
	// PV(dp[v.size()]);
	rep3(i, su+1, rem){
		// cout<< i SP << dp[v.size()][i] <<endl;
		ans=min(ans, dp[v.size()][i]);
	}

	cout<< ans << endl;
 
	return 0;
}