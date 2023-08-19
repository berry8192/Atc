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

struct ice{
	int x1;
	int x2;

	bool operator<(const ice &in) const{
		return x2!=in.x2 ? x2>in.x2 : x1<in.x1;
	};
};

int main(){

	int n, ans=0, fir, usef;
	vector<int> f, s;
	vector<ice> v;

	cin>> n;
	f.resize(n);
	s.resize(n);
	v.resize(n);

	rep(i, n){
		cin >> f[i] >> s[i];
		v[i]={f[i], s[i]};
	}
	sort(all(v));
	fir=v[0].x2;
	usef=v[0].x1;
	// rep(i, n) cout<< "#" << v[i].x1 SP << v[i].x2 <<endl;
	// cout<< fir SP << usef <<endl;

	rep3(i, n, 1){
		if(v[i].x1==usef) ans=max(ans, fir+v[i].x2/2);
		else ans=max(ans, fir+v[i].x2);
	}

	cout<< ans << endl;
 
	return 0;
}