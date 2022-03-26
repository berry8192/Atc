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

	int n, k;
	vector<int> a, b;
	vector<vector<int>> x;

	cin>> n >> k;
	a.resize(n);
	b.resize(n);
	x.resize(n);

	rep(i, n) cin >> a[i];
	rep(i, n) cin >> b[i];

	x[0].push_back(a[0]);
	x[0].push_back(b[0]);
	for(int i=1;i<n;i++){
		int flag=0;
		rep(j, x[i-1].size()){
			if(abs(a[i]-x[i-1][j])<=k) flag=1;
		}
		if(flag) x[i].push_back(a[i]);
		flag=0;
		rep(j, x[i-1].size()){
			if(abs(b[i]-x[i-1][j])<=k) flag=1;
		}
		if(flag) x[i].push_back(b[i]);
	}

	if(x[n-1].size()>0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}