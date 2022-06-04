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
	int v[30][30];

	rep(i, a){
		rep(j, i+1){
			if(j==0 || j==i) v[i][j]=1;
			else v[i][j]=v[i-1][j-1]+v[i-1][j];
			cout<< v[i][j] SP;
		}
		cout<< endl;
	}
 
	return 0;
}