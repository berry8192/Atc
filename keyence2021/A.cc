#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

int main(){

	LLi n, ans=0, ma=0;
	vector<LLi> a, b;

	cin>> n;
	a.resize(n);
	b.resize(n);

	rep(i, n) cin >> a[i];
	rep(i, n) cin >> b[i];

	for(int i=0;i<n;i++) {
		ma=max(ma, a[i]);
		ans=max(ans, ma*b[i]);

		cout<< ans <<endl;
	}
 
	return 0;
}