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

	char aa, bb, cc;
	int a;
	cin>> aa;
	int b;
	cin>> bb;
	int c;
	cin>> cc;
	a=int(aa-'0');
	b=int(bb-'0');
	c=int(cc-'0');

	cout<< 111*(a+b+c) << endl;
 
	return 0;
}