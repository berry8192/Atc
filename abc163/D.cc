#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
vector<LLi> fac(1), facin(1);

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

	LLi n, k;
	LLi ans=0, mi, ma;

	cin>> n >> k;

	for(LLi i=k;i<=n+1;i++){
		mi=i*(i-1)/2;
		ma=i*(2*(n-i+1)+i-1)/2;
		ans+=ma-mi+1;
		ans=ans%mod;
		//cout<< mi SP << ma SP << ans <<endl;
	}

	cout<< ans << endl;
 
	return 0;
}