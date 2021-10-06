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

	int a, b, x, y, r, t;
	cin>> a >> b >> x >> y;

	t=x;

	r=abs(a-b);
	if(a>b) r=max(0, r-1);

	t+=min(2*r*x, r*y);

	cout<< t <<endl;
 
	return 0;
}