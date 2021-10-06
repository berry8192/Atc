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

	LLi a, b, c, d, bl=0, re=0;
	cin>> a >> b >> c >> d;

	if(b>c*d) {
		cout<< -1 <<endl;
		return 0;
	}
	/*if(b==c && d==1){
		cout<< -1 <<endl;
		return 0;
	}*/
	
	bl=a;
	for(int i=1;i<1000000;i++){
		bl+=b;
		re+=c;
		if(bl<=re*d){
			cout<< i <<endl;
			return 0;
		}
	}
		cout<< -1 <<endl;
 
	return 0;
}