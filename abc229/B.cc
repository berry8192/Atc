#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
LLi llimax=9223372036854775807;
LLi mod=1000000007;

int main(){

	string s;
	cin>> s;
	string t;
	cin>> t;

	reverse(all(s));
	reverse(all(t));

	rep(i, s.size()-t.size()) t+="0";
	rep(i, t.size()-s.size()) s+="0";

	// cout<< s <<endl;
	// cout<< t <<endl;

	rep(i, s.size()){
		if(int(s[i]-'0')+int(t[i]-'0')>=10){
			cout<< "Hard" <<endl;
			return 0;
		}
	}
	
	cout<< "Easy" <<endl;

	return 0;
}