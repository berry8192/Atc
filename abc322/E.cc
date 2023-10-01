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
ll lmax=92233720368547758;
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

	ll n, k, p;
	cin>> n >> k >> p;
	vector<ll> c(n);
	vector<vector<ll>> a(n, vector<ll>(5));
	rep(i, n){
		cin>> c[i];
		rep(j, k) cin>> a[i][j];
		rep3(j, 5, k) a[i][j]=5;
	}
	ll dp[110][6][6][6][6][6];
	rep(i, 110){
		rep(i0, 6){
			rep(i1, 6){
				rep(i2, 6){
					rep(i3, 6){
						rep(i4, 6){
							dp[i][i0][i1][i2][i3][i4]=lmax;
						}
					}
				}
			}
		}
	}
	dp[0][0][0][0][0][0]=0;

	rep(i, n){
		// cout<< "i: " << i <<endl;
		rep(i0, 6){
			rep(i1, 6){
				rep(i2, 6){
					rep(i3, 6){
						rep(i4, 6){
							dp[i+1][min(p, i0+a[i][0])][min(p, i1+a[i][1])][min(p, i2+a[i][2])][min(p, i3+a[i][3])][min(p, i4+a[i][4])]=min(dp[i+1][min(p, i0+a[i][0])][min(p, i1+a[i][1])][min(p, i2+a[i][2])][min(p, i3+a[i][3])][min(p, i4+a[i][4])], dp[i][i0][i1][i2][i3][i4]+c[i]);
							// if(dp[i+1][i0][i1][i2][i3][i4]!=lmax) cout<< dp[i+1][i0][i1][i2][i3][i4] SP << i0 SP << i1 SP << i2 SP << i3 SP << i4 <<endl;
							
							dp[i+1][i0][i1][i2][i3][i4]=min(dp[i+1][i0][i1][i2][i3][i4], dp[i][i0][i1][i2][i3][i4]);
						}
					}
				}
			}
		}
	}

	if(dp[n][p][p][p][p][p]==lmax) cout<< -1 << endl;
	else cout<< dp[n][p][p][p][p][p] << endl;
 
	return 0;
}