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

	int h, w, n;
	vector<vector<int>> v;
	vector<int> c;

	cin>> h >> w >> n;
	v.resize(h);
	c.resize(n);

	rep(i, h) v[i].resize(w);

	rep(i, h){
		rep(j, w){
			cin>> v[i][j];
			v[i][j]--;
		}
	}
	rep(i, n){
		cin>> c[i];
		c[i]--;
	}

	rep(i, h) {
		rep(j, w){
			if(i!=h-1 && v[i][j]!=v[i+1][j] && c[v[i][j]]==c[v[i+1][j]]){
				cout<< "No" <<endl;
				return 0;
			}
			if(j!=w-1 && v[i][j]!=v[i][j+1] && c[v[i][j]]==c[v[i][j+1]]){
				cout<< "No" <<endl;
				return 0;
			}
		}
	}

	cout<< "Yes" << endl;
 
	return 0;
}