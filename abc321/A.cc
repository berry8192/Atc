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

	string s;
	cin>> s;
	int a=1;
	rep(i, s.size()-1){
		if(s[i]<=s[i+1]) a=0;
	}

	if(a) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}