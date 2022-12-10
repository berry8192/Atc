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
	int sz=s.size();

	if(sz!=8){
		cout<< "No" << endl;
		return 0;
	}
	if(s[0]<'A' || 'Z'<s[0]){
		cout<< "No" << endl;
		return 0;
	}
	if(s[sz-1]<'A' || 'Z'<s[sz-1]){
		cout<< "No" << endl;
		return 0;
	}
	rep3(i, sz-1, 1){
		if(s[i]<'0' || '9'<s[i]){
			cout<< "No" << endl;
			return 0;
		}
	}
	if(s[1]=='0'){
		cout<< "No" << endl;
		return 0;
	}
	cout<< "Yes" << endl;
 
	return 0;
}