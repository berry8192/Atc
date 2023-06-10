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

	vector<int> v={0, 3, 4, 8, 9, 14, 23};
	char p, q;
	cin>> p >> q;

	cout<< abs(v[p-'A']-v[q-'A']) << endl;
 
	return 0;
}