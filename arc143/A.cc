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
ll mod=1000000007;

int main(){

	ll su;
	vector<ll> a(3);
	cin>> a[0] >> a[1] >> a[2];

	sort(all(a));

	su=a[0]+a[1];

	if(su>=a[2]) cout<< a[2] << endl;
	else cout<< -1 << endl;
 
	return 0;
}