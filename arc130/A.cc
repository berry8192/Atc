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

	int n;
	char tmp='0';
	LLi ans=0, com=0;
	cin>> n;
	string s;
	cin>> s;
	s+="0";

	rep(i, n+1){
		if(s[i]==tmp){
			com++;
		}else{
			ans+=com*(com+1)/2;
			com=0;
			tmp=s[i];
		}
	}

	cout<< ans <<endl;
 
	return 0;
}