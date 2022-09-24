#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

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
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
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

LLi dp[10010][2];

int main(){

	int n, k;
	LLi ans=0;
	string s;
	set<string> st;
	vector<int> v;

	cin>> n>>k;
	v.resize(k);

	rep(i, k){
		cin >> v[i];
	}
	rep(i, 10010){
		dp[i][0]=-imax;
		dp[i][1]=-imax;
	}
	dp[n][0]=n;
	
	repr(i, n){
		int idx=i+1;
		rep(j, k){
			if(idx-v[j]<0) continue;
			dp[idx-v[j]][1]=max(dp[idx-v[j]][1], dp[idx][0]-v[j]);
			dp[idx-v[j]][0]=max(dp[idx-v[j]][0], dp[idx][1]);
			ans=max(ans, dp[idx-v[j]][1]);
		}
	}

	cout<< ans << endl;
 
	return 0;
}
