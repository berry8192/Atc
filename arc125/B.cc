#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
LLi llimax=9223372036854775807;
LLi mod=998244353;

int main(){

	LLi n, ans=0;
	cin>> n;
	vector<LLi> v;

	//for(LLi i=1;i<n;i++) cout<< i*i-(i-1)*(i-1) <<endl;

	for(LLi i=1;i*i<=n;i++){
		ans+=(n-i*i)/i/2+1;
		ans=ans%mod;
	}
	
	cout<< ans <<endl;
	
	return 0;
}