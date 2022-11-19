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
	vector<int> v;

	rep(i, a){
		int tmp;
		cin>> tmp;
		if(i>b-1) v.push_back(tmp);
	}
	rep(i, b) v.push_back(0);
	
	rep(i, a) cout<< v[i] SP;
	cout<< endl;
 
	return 0;
}