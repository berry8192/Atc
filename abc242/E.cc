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
//LLi mod=1000000007;
LLi mod=998244353;

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

LLi dp[1000000][2][26];

int main(){

	int t;
	LLi ans=0;
	vector<int> n;
	vector<string> s;

	cin>> t;
	n.resize(t);
	s.resize(t);
	
	rep(i, t){
		cin>> n[i];
		cin>> s[i];
	}

	rep(i, t){
		dp[0][0][0]=1;

		rep(j, (n[i]+1)/2){
			rep(k, 2){
				// rep(l, 26){
				// 	if (!k && (char(l+'A') > s[i][j])) continue;
				// 	if (l < s[i][j]) k2 = 1;
				// 	dp[j+1][j2][k2] += dp[j][j][k]; // 遷移式
				// }
				rep(l, 26){
					dp[j+1][1][l]=0;
					rep(m, 26){
						dp[j+1][1][l]+=dp[i][1][m];
						dp[j+1][1][l]%=mod;
					}
					
					rep(m, s[i][j]-'A'){
						dp[j+1][1][l]+=dp[i][0][m];
						dp[j+1][1][l]%=mod;
					}
					dp[j+1][0][l]=dp[j][0][l];
				}
			}
		}

		ans=0;
		rep(j, 26){
			ans+=dp[(n[i]+1)/2][0][0];
			ans+=dp[(n[i]+1)/2][1][0];
		}
		ans%=mod;
		cout<< ans <<endl;

		rep(j, (n[i]+10)/2){
			rep(k, 26){
				dp[j][0][k]=0;
				dp[j][1][k]=0;
			}
		}
	}

	return 0;
}