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

void ac(string s){
	cout<< s <<endl;
	exit(0);
}

int main(){

	int n, tmp=0;
	cin>> n;
	string s, t;
	cin>> s;

	rep(i, n){
		t+=s[i];
		if(i>1 && t[t.size()-3]=='f' && t[t.size()-2]=='o' && t[t.size()-1]=='x'){
			t.pop_back();
			t.pop_back();
			t.pop_back();
		}
	}

	cout<< t.size() <<endl;
 
	return 0;
}