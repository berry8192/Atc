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
        if (rx>ry) swap(rx, ry);
		par[ry] = rx; //xとyの根が同じでない(=同じ木にない)時：xの根rxをyの根ryにつける
		siz[rx]+=siz[ry]; //根で管理
    }

	void print(){
		rep(i, par.size()) cout<< i SP;
		cout<< endl;
		rep(i, par.size()) cout<< par[i] SP;
		cout<< endl;
		rep(i, siz.size()) cout<< siz[i] SP;
		cout<< endl;
	}
};

int main(){

	int n, m, e, q;
	vector<int> u, v, x, ans;
	set<int> st;

	cin>> n >> m >> e;
	UnionFind uf(n+m+1);
	u.resize(e);
	v.resize(e);
	rep(i, e){
		cin>> u[i] >> v[i];
	}
	cin>> q;
	x.resize(q);
	ans.resize(q);
	rep(i, q){
		cin>> x[i];
		x[i]--;
		st.insert(x[i]);
	}

	for(int i=n+1;i<=n+m;i++){
		uf.unite(0, i);
	}

	rep(i, e) {
		auto itr=st.find(i);
		if(itr==st.end()){
			uf.unite(u[i], v[i]);
		}
	}

	// rep(i, n){
	// 	if(uf.root(i)==0) ans++;
	// }
	reverse(all(x));

	//uf.print();
	rep(i, q){
		ans[i]=uf.siz[0]-m-1;
		uf.unite(u[x[i]], v[x[i]]);
	}
	reverse(all(ans));

	PV(ans);
 
	return 0;
}