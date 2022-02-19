#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
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

struct vv{
	int c;
	int idx;

	bool operator<(const vv &in) const{
		return c!=in.c ? c<in.c : idx<in.idx;
	};
};

int main(){

	int n, m, mi, k=0;
	LLi C=0;
	vv tmp;
	vector<vv> v;
	vector<int> a, b, c, p, cv;
	vector< vector<int> > cn;
	UnionFind uf(n);

	cin>> n >> m;
	v.resize(n);
	a.resize(m);
	b.resize(m);
	c.resize(n);
	cn.resize(n);
	cv.resize(n);

	rep(i, m){
		cin >> a[i] >> b[i];
		a[i]--;
		b[i]--;
		cn[a[i]].push_back(b[i]);
		cn[b[i]].push_back(a[i]);
	}
	rep(i, n){
		cin>> c[i];
		tmp.c=c[i];
		tmp.idx=i;
		v[i]=tmp;
	}
	sort(all(v));

	rep(i, m) {
		cv[v[i].idx]=1;
		UnionFind buf=uf;
		rep(j, cn[v[i].idx].size()){
			if(cv[cn[v[i].idx][j]]) uf.unite(v[i].idx, cn[v[i].idx][j]);
		}
		if(uf.root(1)==uf.root(n-1)){
			uf=buf;
		}else{
			C+=v[i].c;
			p.push_back(v[i].idx);
			k++;
		}
	}

	cout<< C << endl;
	cout<< k << endl;
	PV(p);
 
	return 0;
}