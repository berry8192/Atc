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

	int n, ans=0;
	vector<string> v;
	v.resize(9);

	rep(i, 9) cin >> v[i];

	rep(i, 9){
		rep(j, 9){
			rep(k, 9){
				rep(l, 9){
					// cout<< "$" <<endl;
					if(v[i][j]=='.') continue;
					if(v[k][l]=='.') continue;
					if(i==k && j==l) continue;
					int rr=k-i;
					int cc=l-j;
					int r2=k-cc;
					int c2=l+rr;
					int r3=i-cc;
					int c3=j+rr;
					if(r2<0 || 8<r2) continue;
					if(c2<0 || 8<c2) continue;
					if(r3<0 || 8<r3) continue;
					if(c3<0 || 8<c3) continue;
					if(v[r2][c2]=='#' && v[r3][c3]=='#') ans++;
				}
			}
		}
	}

	cout<< ans/4 << endl;
 
	return 0;
}