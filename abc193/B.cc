#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int n, ans=imax;
	vector<int> a, p, x;

	cin>> n;
	a.resize(n);
	p.resize(n);
	x.resize(n);

	rep(i, n) cin >> a[i] >> p[i] >> x[i];

	rep(i, n) {
		if (a[i]<x[i]) ans=min(ans, p[i]);
	}

	if(ans==imax) cout<< -1 << endl;
	else cout<< ans << endl;
 
	return 0;
}