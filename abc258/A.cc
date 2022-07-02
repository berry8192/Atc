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

	int a, b=21;
	cin>> a;
	string s;
	if(a>=60){
		b++;
		a-=60;
	}
	s=to_string(b);
	s+=':';
	if(a<10) s+='0';
	s+=to_string(a);

	cout<< s << endl;
 
	return 0;
}