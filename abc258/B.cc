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

vector<int> dih8={1, 1, 1, 0, 0, -1, -1, -1};
vector<int> diw8={-1, 0, 1, -1, 1, -1, 0, 1};

int main(){

	ll ans=0;
	int n;
	vector<vector<char>> v;

	cin>> n;
	v.resize(n);
	rep(i, n) v[i].resize(n);

	rep(i, n){
		rep(j, n){
			cin>> v[i][j];
		}
	}

	rep(i, n){
		rep(j, n){
			rep(d, 8){
				string tmp;
				rep(l, n){
					tmp+=v[(i+dih8[d]*l+n)%n][(j+diw8[d]*l+n)%n];
				}
				ans=max(ans, stoll(tmp));
			}
		}
	}

	cout<< ans << endl;
 
	return 0;
}