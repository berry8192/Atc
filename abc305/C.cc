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

	int h, w, u=10000, d=0, l=10000, r=0;

	cin>> h >> w;
	vector<string> s(h);

	rep(i, h){
		cin>> s[i];
		rep(j, w){
			if(s[i][j]=='#'){
				u=min(u, i);
				l=min(l, j);
				d=max(d, i);
				r=max(r, j);
			}
		}
	}

	rep3(i, d+1, u){
		rep3(j, r+1, l){
			if(s[i][j]=='.'){
				cout<< i+1 SP << j+1 << endl;
			}
		}
	}
 
	return 0;
}