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
	string t;
	cin>> t;

	if(t.size()<s.size()){
		cout<< "No" << endl;
		return 0;
	}
	int flag=1;
	rep(i, s.size()){
		if(s[i]!=t[i]){
			cout<< "No" << endl;
			return 0;
		}
	}

	cout<< "Yes" << endl;
 
	return 0;
}