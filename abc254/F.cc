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

	int n, q;
	vector<int> a, b, h1, h2, w1, w2;
	vector<vector<int>> aa(3), bb(3);

	cin>> n >> q;
	a.resize(n);
	b.resize(n);
	rep(i, 3) aa[i].resize(n);
	rep(i, 3) bb[i].resize(n);
	h1.resize(q);
	h2.resize(q);
	w1.resize(q);
	w2.resize(q);

	rep(i, n) cin >> a[i];
	rep(i, n) cin >> b[i];

	aa[0][0]=a[0];
	aa[1][0]=a[0];
	aa[2][0]=0;
	rep3(i, n, 1){
		aa[0][i]=abs(a[i-1]-a[i]);
		aa[1][i]=a[i]%aa[0][i];
		//aa[2][i]=
	}

	rep(i, q){
		cin >> h1[i] >> h2[i] >> w1[i] >> w2[i];
		h1[i]--;
		h2[i]--;
		w1[i]--;
		w2[i]--;
	}

	rep(i, q) {
		if(abs(h1[i]-h2[i])<2 && abs(w1[i]-w2[i])<2){
			int tmp=0;
			rep3(j, h2[i]+1, h1[i]){
				rep3(k, w2[i]+1, w1[i]){
					if(tmp) tmp=__gcd(tmp, a[j]+b[k]);
					else tmp=a[j]+b[k];
				}
			}
			cout<< tmp <<endl;
		}

	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}