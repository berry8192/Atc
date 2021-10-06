#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

vector<int> c;
vector< map<int, int> > v;

// ↓サイズ計測あり
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
		if(siz[rx]<siz[ry] || 1){
			for (auto p : v[rx]) {
  				auto key = p.first;
  				auto value = p.second;
  				// key, valueを使う
				v[ry][key]+=value;
			}
        	par[rx] = ry; //xとyの根が同じでない(=同じ木にない)時：xの根rxをyの根ryにつける
		}else{
			for (auto p : v[ry]) {
  				auto key = p.first;
  				auto value = p.second;
  				// key, valueを使う
				v[rx][key]+=value;
			}
        	par[ry] = rx; //xとyの根が同じでない(=同じ木にない)時：xの根rxをyの根ryにつける
		}
		siz[rx]+=siz[ry]; //根で管理
		siz[ry]=siz[rx]; //根で管理
    }
};

int main(){

	int n, q, ai, bi, ci, ans=0;
	cin>> n >> q;

	c.resize(n);
	v.resize(n);
	rep(i, n) cin>> c[i];
	rep(i, n) v[i][c[i]-1]++;

	UnionFind uf(n);
	rep(i, q){
		cin>> ai >> bi >> ci;
		if(ai==1){
			uf.unite(bi-1, ci-1);
		}else{
			cout<< v[uf.root(bi-1)][ci-1] <<endl;
			/*for (auto p : v[uf.root(bi-1)]) {
  				auto key = p.first;
  				auto value = p.second;
  				// key, valueを使う
				cout<< key << " " << value <<endl;
			}*/
		}
	}

	return 0;
}