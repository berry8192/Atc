#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=998244353;

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

LLi frc(LLi x){
	LLi a=1;
	for(LLi i=2;i<=x;i++){
		a*=i;
		a=a%mod;
	}
	return a;
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

int main(){

	LLi n, k, flag;
	LLi ans=1, h=1, w=1;
	vector< vector<int> > board;

	cin>> n >> k;
	
	UnionFind ufh(n);
	UnionFind ufw(n);
	
	board.resize(n);
	for(int i=0;i<n;i++) board[i].resize(n);

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>> board[i][j];
		}
	}

	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			flag=1;
			for(int l=0;l<n;l++){
				if(board[i][l]+board[j][l]>k){
					flag=0;
					break;
				}
			}
			if(flag){
				//h++;
				ufh.unite(i, j);
			}
		}
	}

	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			flag=1;
			for(int l=0;l<n;l++){
				if(board[l][i]+board[l][j]>k){
					flag=0;
					break;
				}
			}
			if(flag){
				//w++;
				ufw.unite(i, j);
			}
		}
	}

	for(int i=0;i<n;i++){
		if(ufh.root(i)==i){
			h*=frc((LLi)ufh.tsize(i));
			h=h%mod;
		}
	}

	for(int i=0;i<n;i++){
		if(ufw.root(i)==i){
			h*=frc((LLi)ufw.tsize(i));
			w=w%mod;
		}
	}

	/*h=min(n, h+1);
	w=min(n, w+1);*/

	ans=h*w;
	ans=ans%mod;

	cout<< ans << endl;
 
	return 0;
}