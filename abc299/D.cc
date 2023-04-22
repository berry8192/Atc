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

int query(int x){
	cout<< "? " << x+1 <<endl;
	int si;
	cin>> si;
	return si;
}

int main(){

	int n;
	cin>> n;
	vector<int> v(n);

	int l=0, r=n-1;
	v[l]=query(l);
	v[r]=query(r);
	rep(i, 20){
		if(r-l<=1) break;
		int mi=(l+r)/2;
		v[mi]=query(mi);
		if(v[l]!=v[mi]){
			r=mi;
		}else{
			l=mi;
		}
	}

	cout<< "! " << l+1 << endl;
 
	return 0;
}