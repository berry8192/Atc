#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

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

struct fd{
	int n;
	int a;

	bool operator<(const fd &in) const{
		return a!=in.a ? a>in.a : n<in.n;
	};
};

int main(){

	int n, k, ans=0;
	vector<int> a, b;
	vector<fd> v;

	cin>> n >> k;
	a.resize(n);
	b.resize(k);
	v.resize(n);

	rep(i, n) cin >> a[i];
	rep(i, k) cin >> b[i];
	rep(i, n){
		fd tmp;
		tmp.n=i+1;
		tmp.a=a[i];
		v[i]=tmp;
	}
	sort(all(v));

	rep(i, n) {
		//cout<< v[i].n SP << v[i].a <<endl;
		rep(j, k){
			if(v[i].n==b[j]){
				cout<< "Yes" <<endl;
				return 0;
			}
		}
		if(i==n-1 || v[i].a!=v[i+1].a) break;
	}

	cout<< "No" << endl;
 
	return 0;
}