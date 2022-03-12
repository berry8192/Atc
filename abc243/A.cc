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

	int a;
	cin>> a;
	int b;
	cin>> b;
	int c;
	cin>> c;
	int d;
	cin>> d;
	int lp=0;

	while(1){
		if(lp%3==0){
			a-=b;
			if(a<0){
				cout<< "F" <<endl;
				return 0;
			}
		}else if(lp%3==1){
			a-=c;
			if(a<0){
				cout<< "M" <<endl;
				return 0;
			}
		}else{
			a-=d;
			if(a<0){
				cout<< "T" <<endl;
				return 0;
			}
		}
		lp++;
	}
 
	return 0;
}