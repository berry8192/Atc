#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
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

	LLi n, p, q, tmp, ans=0;
	vector<LLi> v;

	cin>> n >> p >> q;
	mod=p;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep(i1, n) {
		rep3(i2, n, i1+1) {
			rep3(i3, n, i2+1) {
				rep3(i4, n, i3+1) {
					rep3(i5, n, i4+1) {
						tmp=v[i1]*v[i2];
						tmp%=mod;
						tmp*=v[i3];
						tmp%=mod;
						tmp*=v[i4];
						tmp%=mod;
						tmp*=v[i5];
						//cout<< (tmp%mod) <<endl;
						if(tmp%mod==q) ans++;
					}
				}
			}
		}
	}

	cout<< ans << endl;
 
	return 0;
}