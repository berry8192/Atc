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

	int t;
	cin>> t;

	rep(lp, t){
		int n, tmp, ans=0;
		cin>> n;
		rep(i, n){
			cin>> tmp;
			if(tmp%2) ans++;
		}
		cout<< ans << endl;
	}
 
	return 0;
}