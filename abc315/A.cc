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

	string s, ans;
	cin>> s;
	rep(i, s.size()){
		if(s[i]!='a' && s[i]!='i' && s[i]!='u' && s[i]!='e' && s[i]!='o') ans+=s[i];
	}

	cout<< ans << endl;
 
	return 0;
}