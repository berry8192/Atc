#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;
ll mod=1000000007;

int main(){

	int a;
	cin>> a;
	int b;
	cin>> b;
	int c;
	cin>> c;
	double r, rad, x, y;
	r=sqrt(a*a+b*b);
	rad=atan2(b, a)+c*M_PI/180.0;
	x=r*cos(rad);
	y=r*sin(rad);

	//cout<< x SP << y << endl;
	printf("%.12lf %.12lf\n", x, y);
 
	return 0;
}