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

	int x, y, r, n;
	cin>> x >> y >> r >> n;
	x+=n;
	y+=n;
	vector<vector<char>> v(n*2+1, vector<char> (n*2+1, '.'));

	for(int i=0;i<=2*n+1;i++){
		for(int j=0;j<=2*n+1;j++){
			int d=(i-x)*(i-x)+(j-y)*(j-y);
			if(d<=r*r) v[i][j]='#';
		}
	}

	rep(i, n*2+1) PV(v[i]);
 
	return 0;
}