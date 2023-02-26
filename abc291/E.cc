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

vector<vector<int>> g, rg;
vector<int> seen;

int madep=0, mapos;
void dfs(int pos, int dep){
	if(dep<seen[pos]) return;
	seen[pos]=dep;
	if(g[pos].size()==0){
		if(madep<dep){
			madep=dep;
			mapos=pos;
		}
		return;
	}
	rep(i, g[pos].size()){
		dfs(g[pos][i], dep+1);
	}
}

int rmadep=0, rmapos;
void rdfs(int pos, int dep){
	if(dep<seen[pos]) return;
	seen[pos]=dep;
	if(rg[pos].size()==0){
		if(rmadep<dep){
			rmadep=dep;
			rmapos=pos;
		}
		return;
	}
	rep(i, rg[pos].size()){
		rdfs(rg[pos][i], dep+1);
	}
}

vector<int> recpath;
bool rec(int pos, int dep, int goal){
	if(dep<seen[pos]) return false;
	seen[pos]=dep;
	if(pos==goal) return true;
	rep(i, g[pos].size()){
		if(rec(g[pos][i], dep, goal)){
			recpath.push_back(g[pos][i]);
			return true;
		}
	}
	return false;
}

int main(){

	int n, m;
	cin>> n >> m;
	g.resize(n);
	rg.resize(n);
	seen.resize(n);
	vector<int> x(m), y(m), ans(n);
	if(m<n-1){
		cout<< "No" <<endl;
		return 0;
	}

	rep(i, m){
		cin >> x[i] >> y[i];
		x[i]--;
		y[i]--;
		g[x[i]].push_back(y[i]);
		rg[y[i]].push_back(x[i]);
	}

	dfs(0, 0);
	rep(i, n) seen[i]=0;
	// cout<< "mapos " << mapos <<endl;
	rdfs(mapos, 0);
	rep(i, n) seen[i]=0;
	// cout<< "rmapos " << rmapos <<endl;
	rec(rmapos, 0, mapos);
	// PV(recpath);

	if(rmadep==n-1) recpath.push_back(rmapos);

	if(recpath.size()==n){
		cout<< "Yes" <<endl;
		rep(i, recpath.size()){
			ans[recpath[i]]=n-i;
		}
		PV(ans);
	}else{
		cout<< "No" << endl;
	}
 
	return 0;
}