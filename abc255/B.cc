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

	int n, k;
	double ma=0.0;
	vector<int> v;
	vector<double> x, y;
	cout << fixed << setprecision(12);

	cin>> n >> k;
	v.resize(k);
	x.resize(n);
	y.resize(n);

	rep(i, k) cin >> v[i];
	rep(i, n) cin >> x[i] >> y[i];

	rep(i, n) {
		double tmp=500000000000.0;
		rep(j, k){
			if(v[j]==i+1){
				tmp=-1;
				break;
			}
			tmp=min(tmp, (x[i]-x[v[j]-1])*(x[i]-x[v[j]-1])+(y[i]-y[v[j]-1])*(y[i]-y[v[j]-1]));
		}
		ma=max(ma, tmp);
	}

	cout<< sqrt(ma) << endl;
 
	return 0;
}