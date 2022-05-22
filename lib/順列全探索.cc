//https://atcoder.jp/contests/abc183/tasks/abc183_c
#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//ll型vectorを出力
void PVL(vector<ll> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int n, k, tmp, ans=0;
	vector<int> w;
	vector< vector<int> > v;

	cin>> n >> k;
	v.resize(n);
	for(int i=0;i<n;i++) v[i].resize(n);
	w.resize(n-1);
	rep(i, n-1) w[i]=i+1;

	rep(i, n){
		rep(j, n) cin >> v[i][j];
	}

	do {
		tmp=v[0][w[0]];
		rep(i, n-2){
			tmp+=v[w[i]][w[i+1]];
		}
		tmp+=v[w[n-2]][0];
		//PV(w);
		if(tmp==k) ans++;
	} while (next_permutation(all(w)));

	cout<< ans << endl;
 
	return 0;
}