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

//vectorvectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

template <class T> void PS(T ps) {
    // cout<< "{";
	for(auto s : ps) cout<< s SP;
	// cout<< "}";
	cout<<endl;
}

template <class T> void PM(T pm) {
    // cout<< "{";
	for(auto m : pm){
		cout<< "(" << m.first << "->" << m.second << "), ";
	}
	// cout<< "}";
	cout<<endl;
}

struct Compress{
	int sz;
	vector<int> original_v; // 入力されたv
	vector<int> compress_v; // 座標圧縮したv
	map<int, int> compress_map; // <元の値, 圧縮後の値>
	set<int> compress_set; // 圧縮用set

	Compress(){}
	Compress(vector<int> vv){
		sz=vv.size();
		original_v=vv;
		rep(i, sz) compress_set.insert(vv[i]);
		int idx=1;
		for(auto itr=compress_set.begin();itr!=compress_set.end();itr++){
			compress_map[*itr]=idx;
			idx++;
		}
		compress_v.resize(sz);
		rep(i, sz){
			compress_v[i]=compress_map[vv[i]];
		}
	}
};

int main(){

	int n, ans=0;
	vector<int> v;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];
	PV(v);

	Compress(v);

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}