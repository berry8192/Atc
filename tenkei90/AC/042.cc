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

int main(){

	int k;
	LLi ans=0;
	LLi dp[100020];
	//LLi dp[100010][10];
	// dp[i][j]=x 桁の和がiになるのはx通り

	cin>> k;

	dp[0]=1;
	rep(i, k) dp[i+1]=0;

	rep(i, k){
		rep3(j, 10, 1){
			dp[i+j]+=dp[i];
			dp[i+j]%=mod;
		}
		//cout<< dp[i] <<endl;
	}

	// rep(i, k) {
	// 	v.clear();
	// 	rep(j, 10) v[i]=0;
	// 	// +9はmod9空間だと+0と同じなので0~9でまわす
	// 	rep(j, 9){
	// 		rep(l, 9){
	// 			v[j]
	// 		}
	// 		rep(l, 9) dp[i+1][j]=v[j];
	// 	}
	// }

	if(k%9) cout<< 0 <<endl;
	else cout<< dp[k] << endl;
 
	return 0;
}