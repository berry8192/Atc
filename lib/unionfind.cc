#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;

//vecotr<ll>の総和
ll SML(vector<ll> smv) {
	ll tmp=0;
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
    // map<ll,vector<ll>> group;

    UnionFind(int N) : par(N) { //最初は全てが根であるとして初期化
        for(int i = 0; i < N; i++) par[i] = i;
		siz.resize(par.size(), 1); //最初は全てサイズ1
    }

    int root(int x) { // データxが属する木の根を再帰で得る：root(x) = {xの木の根}
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

	int tsize(int x){ // siz[x]の木の根を見に行き、サイズを返す
		return siz[root(x)];
	}

    void unite(int x, int y) { // xとyの木を併合
        int rx = root(x); //xの根をrx
        int ry = root(y); //yの根をry
        if (rx == ry) return; //xとyの根が同じ(=同じ木にある)時はそのまま
        if(siz[rx]<siz[ry]) swap(rx,ry);
        par[ry] = rx; //xとyの根が同じでない(=同じ木にない)時：xの根rxをyの根ryにつける
		siz[rx]+=siz[ry]; //根で管理
    }

    bool same(int x, int y){
        return root(x)==root(y);
    }

    // //素集合をそれぞれグループ化
    // void grouping(){
    //     //経路圧縮を先に行う
    //     REP(i,n)root(i);
    //     //mapで管理する(デフォルト構築を利用)
    //     REP(i,n)group[parent[i]].PB(i);
    // }
};

int main(){

	int n, m, a, b, ans=0;
	cin>> n >> m;

	UnionFind uf(n);
	rep(i, m){
		cin>> a >> b;
		uf.unite(a-1, b-1);
	}

	rep(i, n){
		if(uf.root(i)==i){
			cout<< i <<endl;
			ans++;
		}
	}

	cout<< ans <<endl;

	return 0;
}