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

template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int n, tmp;
	vector<int> a;
	vector< vector<int> > dp;
	// dp[l][r]: lからrの間の最小コスト

	cin>> n;
	a.resize(2*n);
	dp.resize(2*n+1);
	rep(i, 2*n+1) dp[i].resize(2*n+1, imax);

	rep(i, 2*n) cin >> a[i];

	for(int i=1;i<2*n;i+=2){
		//cout<< "i=" << i <<endl;
		for(int j=0;j<2*n-i;j++){
			if(i==1){
				dp[j][j+1]=abs(a[j]-a[j+1]);
				//cout<< dp[j][j+1] <<endl;
				continue;
			}
			//cout<< "j=" << j <<endl;

			dp[j][j+i]=dp[j+1][j+i-1]+abs(a[j]-a[j+i]);
			//cout<< dp[j][j+i] SP;
			//cout<< j+1 << ", " << j+i-1 SP << j << ", " << j+i <<endl;
			for(int k=1;k<i;k+=2){
				//cout<< j << ", " << j+k SP << j+k+1 << ", " << j+i <<endl;
				tmp=dp[j][j+k]+dp[j+k+1][j+i];
				dp[j][j+i]=min(tmp, dp[j][j+i]);
				//cout<< tmp SP;
			}
			//cout<< endl;
			//cout<< dp[j][j+i] <<endl;
		}
	}

	cout<< dp[0][2*n-1] << endl;
 
	return 0;
}