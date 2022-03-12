#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int n, q, ans=0;
	vector<int> t, x, y, v;
	vector<LLi> su;

	cin>> n >> q;
	t.resize(n);
	x.resize(n);
	y.resize(n);
	v.resize(n);
	su.resize(n+2, -1);

	rep(i, q) cin >> t[i] >> x[i] >> y[i] >> v[i];

	rep(i, q) {
		if (t[i]==0){
			su[x[i]]=v[i];
		}
	}

	rep(i, n+1){
		if(su[i]!=-1){

		}
	}

	rep(i, q) {
		if (t[i]==1){
			su[x[i]]=v[i];
		}
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}