#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

LLi mod=1000000007;
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
};

int main(){

	LLi n, bs=0, ans=0;
	vector<int> v, vm, vq;
	UnionFind tree((int)n);
	map<int, la> m;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, n) {
		if (v[i]!=-1){
			if(same(i+1, v[i])) bs++;
			else unite(i+1, v[i]);
		}
	}

	rep(i, n) {
		if (v[i]==-1){
			if(same(i+1, v[i])) bs++;
			else unite(i+1, v[i]);
		}
	}

	rep(i, n) {
		m[root(i+1)]++;
		mp[root(i+1)]+=0;
		if(v[i]==-1) mq[root(i+1)]++;
	}

	for (auto p : m) {
  		auto key = p.first;
  		auto value = p.second;
		vm.push_back(key);
		vq.push_back(value);
	}

	for(int i=0;i<vm.size();i++){
		for(int j=0;j<vm.size();j++){

		}
	}
 
	return 0;
}