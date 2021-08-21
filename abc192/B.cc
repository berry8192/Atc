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

	string s;
	cin>> s;

	for(int i=0;i<s.size();i++){
		char c=s[i];
		if('A'<=c && c<='Z' && i%2==0) ac("No");
		if('a'<=c && c<='z' && i%2==1) ac("No");
	}
	ac("Yes");
 
	return 0;
}