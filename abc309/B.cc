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

	int n;
	cin>> n;
	vector<string> s(n), b(n);

	rep(i, n){
		cin>> s[i];
		b[i]=s[i];
	}
	rep(i, n-1) b[0][i+1]=s[0][i];
	rep(i, n-1) b[i+1][n-1]=s[i][n-1];
	rep(i, n-1) b[n-1][i]=s[n-1][i+1];
	rep(i, n-1) b[i][0]=s[i+1][0];

	rep(i, n) cout<< b[i] <<endl;

	return 0;
}