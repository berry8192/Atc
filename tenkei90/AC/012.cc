#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

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

	int h, w, q, t, sh, sw, gh, gw;
	vector< vector<int> > v;

	cin>> h >> w;
	cin>> q;
	v.resize(h);
	rep(i, h) v[i].resize(w);

	UnionFind uf(h*w);

	rep(i, q){
		cin>> t;
		cin>> sh >> sw;
		sh=sh-1;
		sw=sw-1;
		//cout<< "tmp=" << t SP << sh SP << sw <<endl;
		//cout<< "index=" << sh*w+sw <<endl;
		if(t==1){
			//cout<< "v";
			v[sh][sw]=1;
			//cout<< "#1";
			if(sw<w-1 && v[sh][sw+1]) uf.unite(sh*w+sw, sh*w+sw+1);
			//cout<< "#2";
			if(sw>0 && v[sh][sw-1]) uf.unite(sh*w+sw, sh*w+sw-1);
			//cout<< "#3";
			if(sh<h-1 && v[sh+1][sw]) uf.unite(sh*w+sw, (sh+1)*w+sw);
			//cout<< "#4";
			if(sh>0 && v[sh-1][sw]) uf.unite(sh*w+sw, (sh-1)*w+sw);
			//cout<< "#" <<endl;
		}else{
			cin>> gh >> gw;
			gh=gh-1;
			gw=gw-1;
			//cout<< gh SP << gw <<endl;
			if(v[gh][gw] && uf.root(sh*w+sw)==uf.root(gh*w+gw)){
				cout<< "Yes" << endl;
			}else{
				cout<< "No" << endl;
			}
		}
	}
 
	return 0;
}