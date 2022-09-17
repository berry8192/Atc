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

	int n, t, x, y;
	vector<int> v;

	cin>> n;

	ll le=0, ri=n+1, mi;
	while(ri-le>1){
		mi=(le+ri)/2;
		cout<< "? " << 1 SP << n SP << 1 SP << mi <<endl;
		cin>> t;
		if(t!=mi) ri=mi;
		else le=mi;
	}
	x=ri;

	le=0;
	ri=n+1;
	while(ri-le>1){
		mi=(le+ri)/2;
		cout<< "? " << 1 SP << mi SP << 1 SP << n <<endl;
		cin>> t;
		if(t==-1) return 0;
		if(t!=mi) ri=mi;
		else le=mi;
	}
	y=ri;

	cout<< "! " << y SP << x << endl;
 
	return 0;
}