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

int main(){

	ll w, lp=3;
	vector<int> v(3), x;

	cin>> w;

	v[0]=1;
	v[1]=2;
	v[2]=4;

	while(1){
		int tmp=v[lp-2]+v[lp-1];
		if(tmp>w){
			v.push_back(w);
			break;
		}
		v.push_back(tmp);
		lp++;
	}
	rep(i, v.size()){
		rep3(j, 12, 2){
			if(v[i]/j) x.push_back(v[i]/j);
		}
	}
	rep(i, x.size()) v.push_back(x[i]);

	cout<< v.size() << endl;
	PV(v);
 
	return 0;
}