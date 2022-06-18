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

struct pp{
	int i;
	int x;
	int c;

	bool operator<(const pp &in) const{
		return c!=in.c ? c>in.c : i<in.i;
	};
};

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

	int n;
	ll ans=0;
	vector<pp> v;
	vector<int> x, c;

	cin>> n;
	UnionFind uf(n);
	v.resize(n);
	x.resize(n);
	c.resize(n);

	rep(i, n) cin >> x[i];
	rep(i, n) cin >> c[i];

	rep(i, n) {
		pp tmp;
		tmp.i=i;
		tmp.x=x[i]-1;
		tmp.c=c[i];
		v[i]=tmp;
	}
	sort(all(v));
	rep(i, n){
		//cout<< v[i].i SP << v[i].x SP << v[i].c <<endl;
		if(uf.root(v[i].i)==uf.root(v[i].x)){
			ans+=v[i].c;
		}else{
			uf.unite(v[i].i, v[i].x);
		}
	}

	cout<< ans << endl;
 
	return 0;
}