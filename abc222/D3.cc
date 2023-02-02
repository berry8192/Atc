#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main(){

	int n;
	mint inpt;
	vector<int> a, b;
	vector<vector<mint>> c;

	cin>> n;
	a.resize(n);
	b.resize(n);
	c.resize(n, vector<mint>(3010));

	rep(i, n) cin >> a[i];
	rep(i, n) cin >> b[i];

	rep(i, 3010) {
		if (a[0]<=i && i<=b[0]) c[0][i]=1;
	}

	rep3(i, n, 1){
		mint tmp=0;
		rep(j, 3010){
			tmp+=c[i-1][j];
			if (a[i]<=j && j<=b[i]){
				c[i][j]=tmp;
			}
		}
	}

	mint ans=0;
	rep(i, 3010) ans+=c[n-1][i];

	cout<< ans.val() << endl;
 
	return 0;
}