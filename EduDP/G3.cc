#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;
//using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;
vector<vector<int>> e;
vector<int> seen;
int ans=1;

void PV(vector<int> pvv) {
	rep(i, (int)pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[(int)pvv.size()-1] <<endl;
}

//メモ化再帰
int dfs(int x){
	if(seen[x]) return seen[x];
	//cout<< "in " << x SP << dep <<endl;
	int tmp=0;
	rep(i, e[x].size()){
		//cout<< x << " to " << e[x][i] << " = " << rtn <<endl;
		tmp=max(tmp, dfs(e[x][i])+1);
	}
	seen[x]=tmp;
	return seen[x];
}

int main(){
	int n, m;
	vector<int> a, b;
    // グラフを入力する
    cin>> n >> m;
	a.resize(m);
	b.resize(m);
	e.resize(n);
	seen.resize(n);

    for (int i = 0; i < m; i++) {
		cin>> a[i] >> b[i];
		a[i]--;
		b[i]--;
        e[a[i]].push_back(b[i]);
	}

	// rep(i, n){
	// 	rep(j, e[i].size()){
	// 		cout<< e[i][j] SP;
	// 	}
	// 	cout<< endl;
	// }

	rep(i, n) {
		//cout<< i <<endl;
		dfs(i);
		ans=max(ans, seen[i]);
	}
	//PV(seen);

	cout<< ans << endl;
 
	return 0;
}