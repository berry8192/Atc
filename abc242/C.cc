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
LLi v[9][1000010];

int main(){

	int n;
	LLi ans=0;

	cin>> n;
	n--;
	rep(i, 9) v[i][0]=1;

	rep(i, n) {
		rep(j, 9){
			v[j][i+1]=v[j][i];
			if(j!=0) v[j][i+1]+=v[j-1][i];
			if(j!=8) v[j][i+1]+=v[j+1][i];
			v[j][i+1]%=mod;
		}
	}

	rep(i, 9) ans+=v[i][n];
	cout<< ans%mod << endl;
 
	return 0;
}