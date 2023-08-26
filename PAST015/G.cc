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

struct Sat{
	int k;
	vector<int> a;
	vector<int> b;

	bool sat(vector<int> x){
		rep(i, k){
			if(x[a[i]-1]==b[i]) return true;
		}
		return false;
	}
};

int main(){

	int n, m, k;
	vector<Sat> v;
	vector<int> a, b;

	cin>> n >> m;
	v.resize(m);

	rep(i, m){
		cin>> k;
		a.resize(k);
		b.resize(k);
		rep(j, k) cin>> a[j] >> b[j];
		v[i]={k, a, b};
	}

	for (int bit = 0; bit < (1<<n); ++bit) {
        vector<int> S(n);
		//全ての桁に対する処理
        for (int i = 0; i < n; ++i) {
			//探索対象となっているbitかどうかを判定
            if(bit & (1<<i)) S[i]=1;
			else S[i]=0;
        }
		// PV(S);
		int flg=1;
		rep(i, m){
			if(v[i].sat(S)==false) flg=0;
		}
		if(flg){
			cout<< "Yes" <<endl;
			return 0;
		}
	}

	cout<< "No" << endl;
 
	return 0;
}