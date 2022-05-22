#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;
// 任意長整数型
#include<boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
using Bint = mp::cpp_int;

int imax=2147483647;
long long int llimax=9223372036854775807;
ll mod=1000000007;
//ll mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//ll型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

    int n;
	Bint a=1;

	cin>> n;

	rep(i, n){
        a*=2;
        cout<< a <<endl;
	}
 
	return 0;
}