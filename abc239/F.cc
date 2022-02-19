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

struct tw{
	int d;
	int idx;

	bool operator<(const tw &in) const{
		return d!=in.d ? d<in.d : idx<in.idx;
	};
};

int main(){

	int n, m, td, pos;
	tw tmp;
	vector<tw> v;
	priority_queue<tw> pq;
	priority_queue<tw, vector<tw>, greater<tw>> pqr;
	vector<int> a, b, aa, ab;
	cin>> n >> m;
	UnionFind uf(n);

	v.resize(n);
	a.resize(m);
	b.resize(m);

	rep(i, n){
		cin >> td;
		tmp.d=td;
		tmp.idx=i;
	}
	rep(i, m){
		cin >> a[i] >> b[i];
		a[i]--;
		b[i]--;
		uf.unite(a[i], b[i]]);
		tmp[i].d[a[i]]--;
		tmp[i].d[b[i]]--;
	}
	sort(all(v));
	rep(i, n){
		if(v[i].d){
			pq.push(v[i]);
			pqr.push(v[i]);
		}
	}

	while(!pq.empty()){
		tmp=pq.top();
		pq.pop();
		tmpr=pqr.top();
		pqr.pop();
		
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}