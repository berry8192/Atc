#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;
using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;
using mint = modint1000000007;
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

	long double a, b, c;

	cin>> a >> b >> c;
	
	long double ri, le, mi;
	ri=2.0;
	le=1.0;
	while(ri-le>0.0000000001){
		mi=(ri+le)/2.0;
		//cout<< mi SP << a*mi*mi*mi*mi*mi+b*mi+c <<endl;
		if(a*mi*mi*mi*mi*mi+b*mi+c>0.0) ri=mi;
		else le=mi;
	}

	cout << fixed << setprecision(12);
	cout<< (ri+le)/2.0 << endl;
 
	return 0;
}