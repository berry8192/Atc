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

	LLi a, s, p;
	cin>> s >> p;

	for(LLi i=1;i*i<=p;i++){
		if(p%i!=0) continue;
		if(p/i+i==s) ac("Yes");
		//cout<< i <<endl;
	}
	ac("No");
 
	return 0;
}