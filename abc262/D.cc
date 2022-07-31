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
ll dp[110][110][110];

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
	vector<int> v;
	ll ans=0;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep3(i, n+1, 1){
		rep(j, 110){
			rep(k, i){
				rep(l, i+1){
					dp[j][k][l]=0;
				}
			}
		}
		dp[0][0][0]=1;
		
		rep3(j, n+1, 1){
			rep(k, i){
				rep3(l, i+1, 1){
					dp[j][k][l]+=dp[j-1][k][l];
					dp[j][k][l]+=dp[j-1][(k-((v[j-1])%i)+i)%i][l-1];
					dp[j][k][l]%=mod;
				}
			}
		}
		ans+=dp[n][0][i];
		ans%=mod;
		//cout<< ans <<endl;
	}

	cout<< ans << endl;
 
	return 0;
}