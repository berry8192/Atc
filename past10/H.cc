#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;
using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;
using mint = modint1000000007;
//using mint = modint=998244353;

vector<set<int>> e;
set<int> p;

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

void dfs(int x){
	//cout<< "in " << x <<endl;
	for(auto itr = e[x].begin(); itr != e[x].end(); ++itr) {
		//cout<< "  e " << *itr <<endl;
		if(p.find(*itr)!=p.end()) continue;
		p.insert(*itr);
		dfs(*itr);
	}
}

int main(){

	int n, q, t, u, v;

	cin>> n >> q;
	e.resize(n);

	rep(i, q){
		cin >> t;
		if(t==1){
			cin>> u >> v;
			u--;
			v--;
			e[u].insert(v);
			e[v].insert(u);
		}else{
			cin>> u;
			u--;
			p.clear();
			p.insert(u);
			dfs(u);
			for(auto itr = p.begin(); itr != p.end(); ++itr) {
				std::cout << *itr+1 << " ";
			}
			cout<< endl;
		}
	}
 
	return 0;
}