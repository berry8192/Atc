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

	LLi n;
	cin>> n;

	rep(i, 100){
		LLi tmp=1;
		rep(j, i){
			tmp*=2;
		}
		if(tmp>n){
			cout<< i-1 << endl;
			return 0;
		}
	}
 
	return 0;
}