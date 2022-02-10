#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

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

struct itm{
	int c;
	int l;
	int r;

	bool operator<(const itm &in) const{
		return c!=in.c ? c<in.c : l!=in.l ? l<in.l : r<in.r;
	};
};

int main(){

	int n, m, c, l, r;
	LLi ans=0;
	itm tmp;
	vector<itm> v;

	cin>> n >> m;
	v.resize(m);

	rep(i, m){
		cin >> c >> l >> r;
		tmp.c=c;
		tmp.l=l-1;
		tmp.r=r;
		v[i]=tmp;
	}
	sort(all(v));
	
	UnionFind uf(n+1);

	rep(i, m){
		if(uf.root(v[i].l)!=uf.root(v[i].r)){
			uf.unite(v[i].l, v[i].r);
			ans+=v[i].c;
		}
	}

	rep(i, n){
		if(uf.root(i)!=uf.root(i+1)){
			cout<< -1 <<endl;
			return 0;
		}
	}
	cout<< ans << endl;
 
	return 0;
}
