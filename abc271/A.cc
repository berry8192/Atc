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

	int a;
	cin>> a;
	int b=a/16;
	int c=a%16;
	string ans;
	if(b<10) ans+=to_string(b);
	else ans+=('A'+(b-10));
	if(c<10) ans+=to_string(c);
	else ans+=('A'+(c-10));

	cout<< ans << endl;
 
	return 0;
}