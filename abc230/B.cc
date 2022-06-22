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

	int ans=0, flag, sz;
	string s, t;
	cin>> s;
	sz=s.size();

	t="oxxoxxoxxoxxoxxoxxoxxoxxoxxoxxoxxoxxoxxoxxoxxoxx";

	rep(i, 3){
		flag=1;
		rep(j, sz){
			if(s[j]!=t[j+i]){
				flag=0;
				break;
			}
		}
		if(flag) ans=1;
	}

	if(ans) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}