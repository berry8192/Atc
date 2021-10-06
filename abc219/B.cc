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

	string s1, s2, s3, t, ans;
	cin>> s1 >> s2 >> s3 >> t;

	rep(i, t.size()){
		if(t[i]=='1') ans+=s1;
		if(t[i]=='2') ans+=s2;
		if(t[i]=='3') ans+=s3;
	}

	cout<< ans <<endl;
 
	return 0;
}