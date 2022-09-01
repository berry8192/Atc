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

	vector<int> v(8);
	rep(i, 8) cin >> v[i];

	rep(i, 4) {
		double l1=atan2(v[((i+1)*2+1)%8]-v[((i)*2+1)%8], v[((i+1)*2)%8]-v[((i)*2)%8]);
		double l2=atan2(v[((i+2)*2+1)%8]-v[((i+1)*2+1)%8], v[((i+2)*2)%8]-v[((i+1)*2)%8]);
		if(l2-l1<0) l2+=3.14159265358979*2;
		//cout<< l1 SP << l2 SP << l2-l1 <<endl;
		if(l2-l1>3.14159265358979){
			cout<< "No" <<endl;
			return 0;
		}
	}

	cout<< "Yes" << endl;
 
	return 0;
}