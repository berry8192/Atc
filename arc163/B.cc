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

	int n, m, l, r;
	vector<int> v, lv, rv;

	cin>> n >> m;
	cin>> l >> r;
	v.resize(n-2);

	rep(i, n-2) cin >> v[i];
	sort(all(v));
	// PV(v);
	lv.push_back(0);
	rv.push_back(0);

	rep(i, n-2){
		if(v[i]<l){
			lv.push_back(l-v[i]);
			// cout<< v[i] <<endl;
		}
		if(v[i]>r){
			rv.push_back(v[i]-r);
		}
	}
	// reverse(all(lv));
	// PV(lv);
	// PV(rv);

	if(n-lv.size()-rv.size()>=m){
		cout<< 0 <<endl;
		return 0;
	}
	int ans=n-lv.size()-rv.size();
	int remain=m-ans;
	// cout<< "remain" << remain << endl;

	int lpos=min(remain, int(lv.size()-1));
	int rpos=0;
	// cout<< "lpos" << lpos <<endl;

	if(lpos<remain){
		rpos=remain-lpos;
	}
	// cout<< lpos SP << rpos <<endl;
	int micos=imax;
	while(lpos>=0 && rpos<rv.size()){
		int tmp=0;
		tmp+=lv[lpos];
		tmp+=rv[rpos];
		if(r<l){
			l-r-rv[rpos]
		}
		// cout<< "tmp:" << tmp <<endl;
		micos=min(micos, tmp);
		lpos--;
		rpos++;
	}

	cout<< micos << endl;
 
	return 0;
}