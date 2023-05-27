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

	int n;
	cin>> n;
	int m;
	cin>> m;
	vector<vector<int>> v(m, vector<int>(n));
	vector<vector<int>> w(n, vector<int>(n));

	rep(i, m){
		rep(j, n){
			cin>> v[i][j];
			if(j){
				w[v[i][j]-1][v[i][j-1]-1]=1;
				w[v[i][j-1]-1][v[i][j]-1]=1;
			}
		}
	}

	int ans=0;
	rep(i, n){
		rep(j, n){
			if(i!=j && w[i][j]==0) ans++;
		}
	}

	cout<< ans/2 << endl;
 
	return 0;
}