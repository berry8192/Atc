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

	LLi l, r;
	cin>> l >> r;

	for(LLi i=r-l;i>0;i--){
		for(LLi j=l;i+j<r+1;j++){
			//cout<< j SP << i+j <<endl;
			if(__gcd(j, i+j)==1){
				cout<< i <<endl;
				return 0;
			}
		}
	}
 
	return 0;
}