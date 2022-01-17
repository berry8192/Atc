#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

//vecotr<LLi>の総和
LLi SML(vector<LLi> smv) {
	LLi tmp=0;
	rep(i, smv.size()) tmp+=smv[i];

	return tmp;
}

// ↓サイズ計測機能（自作）なし
/*struct UnionFind {
    vector<int> par; // par[i]:iの親の番号　(例) par[3] = 2 : 3の親が2

    UnionFind(int N) : par(N) { //最初は全てが根であるとして初期化
        for(int i = 0; i < N; i++) par[i] = i;
    }

    int root(int x) { // データxが属する木の根を再帰で得る：root(x) = {xの木の根}
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

    void unite(int x, int y) { // xとyの木を併合
        int rx = root(x); //xの根をrx
        int ry = root(y); //yの根をry
        if (rx == ry) return; //xとyの根が同じ(=同じ木にある)時はそのまま
        par[rx] = ry; //xとyの根が同じでない(=同じ木にない)時：xの根rxをyの根ryにつける
    }

    bool same(int x, int y) { // 2つのデータx, yが属する木が同じならtrueを返す
        int rx = root(x);
        int ry = root(y);
        return rx == ry;
    }
};*/
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
        par[rx] = ry; //xとyの根が同じでない(=同じ木にない)時：xの根rxをyの根ryにつける
		siz[rx]+=siz[ry]; //根で管理
		siz[ry]=siz[rx]; //根で管理
    }
};

int main(){

	int n, m, q, a, b, c;
	cin>> n >> m >> q;

	vector<bool> ans(q);
	vector< tuple<int, int, int, bool, int> > e(m+q);
	//重さ（軽い順）、辺始点、辺終点、元の木の辺かどうか、元のindex
	UnionFind uf(n);
	rep(i, m+q){
		cin>> a >> b >> c;
		e[i] = make_tuple(c, a-1, b-1, i<m, i-m);
	}
	sort(all(e));

	rep(i, m+q){
		if(get<3>(e[i])){
			//元の木のとき
			a=get<1>(e[i]);
			b=get<2>(e[i]);
			if(uf.root(a)!=uf.root(b)) uf.unite(a, b);
		}else{
			//クエリの辺のとき
			a=get<1>(e[i]);
			b=get<2>(e[i]);
			c=get<4>(e[i]);
			if(uf.root(a)!=uf.root(b)) ans[c]=true;
			else ans[c]=false;
		}
	}

	rep(i, q){
		if(ans[i]) cout<< "Yes" <<endl;
		else cout<< "No" <<endl;
	}

	return 0;
}