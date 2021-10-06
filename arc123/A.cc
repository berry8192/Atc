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

	LLi a, b, c, tmp, l, s;
	cin>> a >> b >> c;

	if(b<=a && b<=c){
		tmp=(a+c);
		if(tmp%2==0) cout<< tmp/2-b <<endl;
		else cout<< (tmp+1)/2-b+1 <<endl;
	}else if(a<b && c<b){
		tmp=b+(b-a);
		cout<< tmp-c <<endl;
	}else{
		l=max(a, c);
		s=min(a, c);
		if(l-b<=b-s){
			cout<< abs(l-b-(b-s)) <<endl;
		}else if((l+s)%2==0) {
			cout<< (l+s)/2-b <<endl;
		}else{
			cout<< (l+s+1)/2-b+1 <<endl;
		}
	}
 
	return 0;
}