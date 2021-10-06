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

	int n, ans=0, mi=0, ma=10000;
	vector<int> v, w;

	cin>> n;
	v.resize(n);
	w.resize(n);

	rep(i, n) cin >> v[i];
	rep(i, n) cin >> w[i];

	rep(i, n) {
		mi=max(mi, v[i]);
		ma=min(ma, w[i]);
	}

	if(mi<=ma) cout<< ma-mi+1 << endl;
	else cout<< 0 << endl;
 
	return 0;
}