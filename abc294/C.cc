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

	int n, m, ans=0;
	cin>> n >> m;
	vector<int> a(n), b(m), v, aaa, bbb;

	rep(i, n) cin >> a[i];
	rep(i, m) cin >> b[i];
	a.push_back(imax);
	b.push_back(imax);

	int aa=0, bb=0, cnt=1;
	rep(i, n+m){
		if(a[aa]<b[bb]){
			aaa.push_back(cnt);
			aa++;
		}else{
			bbb.push_back(cnt);
			bb++;
		}
		cnt++;
	}
	PV(aaa);
	PV(bbb);
 
	return 0;
}