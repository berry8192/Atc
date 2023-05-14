#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;
ll mod=998244353;

int main(){

	int a;
	cin>> a;
	rep(lp, a){
		int n;
		cin>> n;
		ll ans=0;
		for(int i=1;i*i<=n;i++){
			ans+=3*(i-1);
			ans++;
			ans+=6LL*((n/i)-i)*(i-1);
			ans%=mod;
			ans+=3LL*((n/i)-i);
			ans%=mod;
			// cout<< ans <<endl;
		}
		cout<< ans <<endl;
	}
 
	return 0;
}