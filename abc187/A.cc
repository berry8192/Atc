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

	int a=0, b=0;
	string s, t;
	cin>> s >> t;

	for(int i=0;i<s.size();i++) a+=(int)(s[i]-'0');
	for(int i=0;i<t.size();i++) b+=(int)(t[i]-'0');

	cout<< max(a, b) <<endl;
 
	return 0;
}