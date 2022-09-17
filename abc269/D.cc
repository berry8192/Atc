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

	int n;
	vector<int> x, y;
	vector<int> dirx={0, 1, -1, 1, -1, 0}, diry={1, 1, 0, 0, -1, -1};

	cin>> n;
	x.resize(n);
	y.resize(n);
	UnionFind uf(n);

	rep(i, n) cin >> x[i] >> y[i];

	rep(i, n) {
		rep3(j, n, i+1){
			int flag=0;
			rep(k, 6){
				if(x[i]+dirx[k]==x[j] && y[i]+diry[k]==y[j]){
					flag=1;
					break;
				}
			}
			if(flag){
				uf.unite(i, j);
			}
		}
	}

	set<int> st;
	rep(i, n) st.insert(uf.root(i));

	cout<< st.size() << endl;
 
	return 0;
}