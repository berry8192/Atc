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

	int n, cnt;
	vector<vector<int>> bo, r;
	int dp[55][55];

	cin>> n;
	bo.resize(n);
	for(int i=0;i<n;i++) bo[i].resize(n);
	// r.resize(n+1);
	// for(int i=0;i<n+1;i++) r[i].resize(n+1);

	//1行ずつ入力する場合
	for(int i=0;i<n;i++){
		string tmp;
		cin>> tmp;
		for(int j=0;j<n;j++){
			if(tmp[j]=='#') bo[i][j]=1;
			else bo[i][j]=0;
		}
	}

	// rep(i, n){
	// 	rep(j, n){
	// 		if(bo[i][j]=='#') r[i+1][j+1]++;
	// 	}
	// }
	// rep(i, n){
	// 	rep(j, n){
	// 		r[i+1][j+1]+=r[i+1][j];
	// 	}
	// }
	// rep(i, n){
	// 	rep(j, n){
	// 		r[i+1][j+1]+=r[i][j+1];
	// 	}
	// }

	//PVV(r);

	rep(i, n){
		rep(j, n){
			if(bo[i][j]) dp[i][j]=1;
			else dp[i][j]=0;
		}
	}

	rep3(i, n, 2){
		rep(j, n-i){
			rep(k, n-i){
				cnt=0;
				rep3(l, j, j+i){
					rep3(m, k, k+i){
						
					}
				}
			}
		}
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}