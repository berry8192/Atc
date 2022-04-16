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

	int n, q, ans=0, l, r, x;
	vector<int> a;
	vector<vector<int>> st(200010);

	cin>> n;
	a.resize(n);
	rep(i, n){
		cin >> a[i];
		st[a[i]].push_back(i+1);
	}

	cin>> q;

	rep(i, q) {
		cin>> l >> r >> x;
		auto lb=lower_bound(all(st[x]), l);
		auto rb=lower_bound(all(st[x]), r+1);
		cout<< rb-lb <<endl;
	}

	return 0;
}