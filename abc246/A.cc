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

	int x1, x2, x3, y1, y2, y3, x, y;
	cin>> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	x=x1^x2^x3;
	y=y1^y2^y3;

	cout<< x << " " << y << endl;
 
	return 0;
}