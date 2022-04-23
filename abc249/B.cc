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

	int A=0, a=0;
	string s;
	cin>> s;

	rep(i, s.size()){
		for(int j=i+1;j<s.size();j++){
			if(s[i]==s[j]){
				cout<< "No" << endl;
				return 0;
			}
		}
		if(s[i]<='Z') A=1;
		if('a'<=s[i]) a=1;
	}
 
	if(A&&a) cout<< "Yes" << endl;
	else cout<< "No" << endl;

	return 0;
}