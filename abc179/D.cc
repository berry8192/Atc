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

	LLi n, k, ans=0;
	vector<int> l, r;
	vector<LLi> dp, rdp;

	cin>> n >> k;
	l.resize(k);
	r.resize(k);
	dp.resize(n+1);
	rdp.resize(n+1);

	rep(i, k) cin >> l[i] >> r[i];

	dp[0]=0;
	dp[1]=1;
	rdp[0]=0;
	rdp[1]=1;

	for(int i=2;i<=n;i++) {
		for(int j=0;j<k;j++){
			dp[i]+=(mod+rdp[max(0, i-l[j])]-rdp[max(0, i-r[j]-1)])%mod;
		}
		dp[i]=dp[i]%mod;
		rdp[i]=(rdp[i-1]+dp[i])%mod;
		//cout<< dp[i] <<endl;
	}

	cout<< dp[n] << endl;
 
	return 0;
}