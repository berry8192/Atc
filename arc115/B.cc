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

	int n;
	LLi tmp, ans=0;
	vector<int> v;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		ans+=(v[i]*v[i])%mod;
		ans=ans%mod;
	}

	sort(v.begin(), v.end());

	tmp=v[n-1];
	for(int i=n-2;i>=0;i--){
		//cout<< ans <<endl;
		ans+=(tmp*v[i])%mod;
		ans=ans%mod;
		tmp*=2;
		tmp+=v[i];
		tmp=tmp%mod;
	}
	cout<< ans <<endl;
 
	return 0;
}