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
	string s;
	cin>> s;
	string t;
	cin>> t;

	rep(i, a){
		if(s[i]==t[i]) continue;
		if(s[i]=='0' && t[i]=='o') continue;
		if(s[i]=='1' && t[i]=='l') continue;
		if(s[i]=='o' && t[i]=='0') continue;
		if(s[i]=='l' && t[i]=='1') continue;
		cout<< "No" << endl;
		return 0;
	}

	cout<< "Yes" << endl;
 
	return 0;
}