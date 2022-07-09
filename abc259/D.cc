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

struct UnionFind {
    vector<int> par; // par[i]:iの親の番号　(例) par[3] = 2 : 3の親が2
	vector<int> siz; // siz[i]:iの属する木に含まれる点の数

    UnionFind(int N) : par(N) { //最初は全てが根であるとして初期化
        for(int i = 0; i < N; i++) par[i] = i;
		siz.resize(par.size(), 1); //最初は全てサイズ1
    }

    int root(int x) { // データxが属する木の根を再帰で得る：root(x) = {xの木の根}
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

	int tsize(int x){ // siz[x]の木の根を見に行き、サイズを返す
		if (par[x] == x) return siz[x];
		return tsize(par[x]);
	}

    void unite(int x, int y) { // xとyの木を併合
        int rx = root(x); //xの根をrx
        int ry = root(y); //yの根をry
        if (rx == ry) return; //xとyの根が同じ(=同じ木にある)時はそのまま
        par[rx] = ry; //xとyの根が同じでない(=同じ木にない)時：xの根rxをyの根ryにつける
		siz[rx]+=siz[ry]; //根で管理
		siz[ry]=siz[rx]; //根で管理
    }
};

int main(){

	ll n, sx, sy, tx, ty;
	vector<ll> x, y, r, si, ti;

	cin>> n;
	cin>> sx >> sy >> tx >> ty;
	x.resize(n);
	y.resize(n);
	r.resize(n);
	UnionFind uf(n);

	rep(i, n){
		cin >> x[i] >> y[i] >> r[i];
		// ある点がある円の周上にあるかどうかの判定
		// ==の部分を不等号にすれば内外判定もできる
		if((x[i]-sx)*(x[i]-sx)+(y[i]-sy)*(y[i]-sy)==r[i]*r[i]){
			si.push_back(i);
		}
		if((x[i]-tx)*(x[i]-tx)+(y[i]-ty)*(y[i]-ty)==r[i]*r[i]){
			ti.push_back(i);
		}
	}

	rep(i, n){
		rep3(j, n, i+1){
			// 2つの円が共有点を一つ以上持つかどうかの判定
			// 円の接触判定は接しない2通り、交差する1通り、内接外接で2通り、合計5通りある
			// https://examist.jp/mathematics/figure-circle/two-circle/
			if((r[i]+r[j])*(r[i]+r[j])>=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]) && (r[i]-r[j])*(r[i]-r[j])<=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])){
				uf.unite(i, j);
			}
		}
	}

	int flag=0;

	rep(i, si.size()){
		rep(j, ti.size()){
			if(uf.root(si[i])==uf.root(ti[j])){
				flag=1;
				break;
			}
		}
	}

	if(flag) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}