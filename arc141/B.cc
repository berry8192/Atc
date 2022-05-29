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
ll mod=998244353;

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

	ll n, m, ans=0;
	vector<ll> mm(64);
	vector<vector<ll>> dp(64);

	cin>> n >> m;
	
	if(n>m || n>=64){
		cout<< 0 <<endl;
		return 0;
	}

	rep(i, 64) dp[i].resize(64);
	mm[1]=1;
	rep3(i, 64, 2){
		mm[i]=mm[i-1]*2;
		
		if(mm[i]*2-1>=m){
			mm[i]-=mm[i]*2-1-m;
			break;
		}
	}
	//PV(mm);
	rep(i, 64) mm[i]%=mod;

	dp[0]=mm;

	rep3(i, n, 1){
		rep3(j, 64, i){
			rep3(k, j, i){
				dp[i][j]+=dp[i-1][k]*mm[j];
				dp[i][j]%=mod;
			}
		}
	}
	//PVV(dp);

	rep(i, 64) ans+=dp[n-1][i];

	cout<< ans%mod << endl;
 
	return 0;
}