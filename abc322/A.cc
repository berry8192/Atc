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
	string s;
	cin>> s;

	rep(i, a-2){
		if(s.substr(i, 3)=="ABC"){
			cout<< i+1 <<endl;
			return 0;
		}
	}

	cout<< -1 << endl;
 
	return 0;
}