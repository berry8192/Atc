#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
using namespace atcoder;

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

int op(int a, int b){ return min(a, b); }

int e() { return imax; }

int target;

bool f(int v) { return v > target; }

struct box{
	int x1;
	int x2;
	int x3;

	bool operator<(const box &in) const{
		return x1!=in.x1 ? x1<in.x1 : x2!=in.x2 ? x2>in.x2 : x3<in.x3;
	};
};

struct Compress{
	int sz;
	vector<int> original_v; // 入力されたv
	set<int> compress_set; // 圧縮用set
	map<int, int> compress_map; // <元の値, 圧縮後の値>
	vector<int> compress_v; // 座標圧縮したv

	Compress(vector<int> vv, int indexd=1){
		sz=vv.size();
		original_v=vv;
		rep(i, sz) compress_set.insert(vv[i]);
		int idx=indexd; // indexdスタートで圧縮
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

	int n;
	cin>> n;
	vector<int> w(3*n);
	vector<box> bo;

	rep(i, 3*n) cin>> w[i];
	Compress comp(w);

	vector<int> v(3);
	rep(i, n){
		v[0]=comp.compress_v[3*i];
		v[1]=comp.compress_v[3*i+1];
		v[2]=comp.compress_v[3*i+2];
		sort(all(v));
		bo.push_back({v[0], v[1]-1, v[2]});
	}
	sort(all(bo));
	// rep(i, n){
	// 	cout<< bo[i].x1 SP << bo[i].x2 SP << bo[i].x3 <<endl;
	// }

	segtree<int, op, e> seg(3*n+10);

	rep(i, n) {
		if(bo[i].x3<seg.get(bo[i].x2)) seg.set(bo[i].x2, bo[i].x3);
		if(seg.prod(0, bo[i].x2)<bo[i].x3){
			cout<< "Yes" <<endl;
			return 0;
		}
	}

	cout<< "No" << endl;
 
	return 0;
}