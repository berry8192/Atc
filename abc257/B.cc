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
	vector<int> a, l;

	cin>> n >> k >> q;
	a.resize(k);
	l.resize(q);

	rep(i, k) cin >> a[i];
	rep(i, q){
		cin >> l[i];
		l[i]--;
	}

	rep(i, q) {
		if(a[l[i]]==n) continue;
		if(l[i]!=k-1 && a[l[i]+1]-a[l[i]]==1) continue;
		a[l[i]]++;
	}

	rep(i, k) cout<< a[i] SP;

	cout<< endl;
 
	return 0;
}