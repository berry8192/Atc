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

	int b=0, k, r1=-1, r2;
	string s;
	cin>> s;

	rep(i, 8){
		if(s[i]=='B') b+=i;
		if(s[i]=='K') k=i;
		if(s[i]=='R' && r1==-1) r1=i;
		if(s[i]=='R' && r1!=-1) r2=i;
	}

	if(b%2 && r1<k && k<r2) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}