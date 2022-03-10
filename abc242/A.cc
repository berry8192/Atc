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
	
	cout << fixed << setprecision(12);

	int a;
	cin>> a;
	int b;
	cin>> b;
	int c;
	cin>> c;
	int d;
	cin>> d;

	if(d<=a) cout<< 1 << endl;
	else if(d<=b) cout<< 1.0*c/(b-a) << endl;
	else cout<< 0 <<endl;
 
	return 0;
}