#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int main(){

	string s, t;
	cin>> s >> t;

	if(s==t){
		cout<< "same" << endl;
		return 0;
	}
 
	rep(i, 3){
		if('a'<=s[i] && s[i]<='z'){
			s[i]=(char)(s[i]-('a'-'A'));
		}
		if('a'<=t[i] && t[i]<='z'){
			t[i]=(char)(t[i]-('a'-'A'));
		}
	}

	if(s==t) cout<< "case-insensitive" << endl;
	else cout<< "different" << endl;

	return 0;
}