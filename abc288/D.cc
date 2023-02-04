#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
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

	int n, k, q;
	cin>> n >> k;
	vector<int> a(n), zero(n);
	vector<vector<int>> tmp(k, vector<int>(k));
	rep(i, n) cin >> a[i];
	int leadz=0;
	repr(i, n){
		if(a[i]==0){
			zero[i]=leadz+1;
			leadz++;
		}else{
			leadz=0;
		}
	}
	cin>> q;
	vector<int> l(q), r(q);
	rep(i, n){
		cin >> l[i] >> r[i];

	}


	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}