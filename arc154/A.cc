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

	int n;
	cin>> n;
	string a;
	cin>> a;
	string b;
	cin>> b;
	ll aa=0, bb=0, d=1;

	rep(i, n){
		if(a[i]>b[i]) swap(a[i], b[i]);
	}
	// cout<< a <<endl;
	// cout<< b <<endl;
	repr(i, n){
		aa+=d*(a[i]-'0');
		aa%=mod;
		bb+=d*(b[i]-'0');
		bb%=mod;
		d*=10;
		d%=mod;
	}
	cout<< (aa*bb)%mod <<endl;
 
	return 0;
}