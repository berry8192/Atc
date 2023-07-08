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

struct xxxx{
	int x1;
	int x2;

	bool operator<(const xxxx &in) const{
		return x1!=in.x1 ? x1<in.x1 : x2<in.x2;
	};
};

int main(){

	int n, k;
	ll ans=0;
	cin>> n >> k;
	vector<int> a(n), b(n);
	vector<xxxx> v(n);
	rep(i, n){
		cin >> a[i] >> b[i];
		ans+=b[i];
	}
	if(ans<=k){
		cout<< 1 <<endl;
		return 0;
	}
	rep(i, n) v[i]={a[i], b[i]};
	sort(all(v));

	rep(i, n) {
		ans-=v[i].x2;
		// cout<< ans <<endl;
		if (ans<=k){
			cout<< v[i].x1+1 <<endl;
			return 0;
		}
	}
 
	return 0;
}