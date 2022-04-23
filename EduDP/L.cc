#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;
//using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

LLi dp[3010][3010];

int main(){

	int n, ans=0;
	vector<int> v;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		dp[i][i]=v[i];
	}
	rep(i, n-1){
		dp[i][i+1]=max(dp[i][i], dp[i+1][i+1])-min(dp[i][i], dp[i+1][i+1]);
		if(n%2) dp[i][i+1]*=-1;
	}

	rep3(i, n-1, 1) {
		rep(j, n-1-i){
			//cout<< "kukan " << j SP << j+i+1 <<endl;
			if(!((n%2)^(i%2))){
				dp[j][j+i+1]=max(v[j+i+1]+dp[j][j+i], v[j]+dp[j+1][j+i+1]);
				//cout<<"自分がとる " << dp[j][j+i] SP << v[j+i+1] SP << dp[j+1][j+i+1] SP << v[j] <<endl;
			}else{
				dp[j][j+i+1]=min(dp[j][j+i]-v[j+i+1], dp[j+1][j+i+1]-v[j]);
				//cout<<"相手がとる " << dp[j][j+i] SP << v[j+i+1] SP << dp[j+1][j+i+1] SP << v[j] <<endl;
			}
			//cout<< dp[j][j+i+1] << endl;
		}
	}

	cout<< dp[0][n-1] << endl;
 
	return 0;
}