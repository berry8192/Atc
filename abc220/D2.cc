#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=998244353;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int n, ans=0, f, g;
	vector<int> v;
	vector<LLi> upv;
	LLi dp[100010][10];

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];
	rep(i, 10) dp[0][i]=0;
	dp[0][v[0]]=1;

	rep(i, n-1) {
		upv.clear();
		upv.resize(10);
		rep(j, 10){
			f=(j+v[i+1])%10;
			g=(j*v[i+1])%10;
			upv[f]+=dp[i][j];
			upv[g]+=dp[i][j];
		}
		rep(j, 10){
			dp[i+1][j]=upv[j];
			dp[i+1][j]=dp[i+1][j]%mod;
		}
	}

	rep(i, 10) cout<< dp[n-1][i] <<endl;
 
	return 0;
}