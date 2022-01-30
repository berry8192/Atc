#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=922337203685477587;
LLi mod=1000000007;
//LLi mod=998244353;

int n, m, u, v;
LLi ans=0;
vector<LLi> h, seen, pl;
vector< vector<LLi> > bo, val;
queue<LLi> qh, qw, qq;

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

void bfs(int x, LLi sco, int frm){
	//移動してきた時の処理
	//cout<< x SP << sco <<endl;
	ans=max(ans, sco);
	if(seen[x]>=sco){
	//if(seen[x]!=-llimax){
		//pl[x]=max(pl[x], sco-seen[x]);
		return;
	}
	seen[x]=sco;

	//移動する処理
	for(int i=0;i<bo[x].size();i++){
		// move from x to bo[x][i]
		if(frm!=bo[x][i]){
			qh.push(bo[x][i]);
			qw.push(sco+val[x][i]);
			qq.push(x);
			//bfs(bo[x][i], sco+val[x][i], x);
		}
	}
}

int main(){

	cin>> n >> m;
	h.resize(n);
	bo.resize(n+1);
	val.resize(n+1);
	seen.resize(n+1, -llimax);
	pl.resize(n+1, -llimax);

	rep(i, n) cin >> h[i];
	rep(i, m){
		cin >> u >> v;

		bo[u].push_back(v);
		if(h[u-1]>=h[v-1]) val[u].push_back(h[u-1]-h[v-1]);
		else val[u].push_back((h[u-1]-h[v-1])*2);

		bo[v].push_back(u);
		if(h[v-1]>=h[u-1]) val[v].push_back(h[v-1]-h[u-1]);
		else val[v].push_back((h[v-1]-h[u-1])*2);
	}

	// PVV(bo);
	// PVV(val);

	qh.push(1);
	qw.push(0);
	qq.push(0);
  	while (!qh.empty()) {
    	bfs(qh.front(), qw.front(), qq.front());
    	qh.pop();
    	qw.pop();
    	qq.pop();
  	}

	for(int i=1;i<=n;i++){
		ans=max(ans, seen[i]+pl[i]);
	}

	cout<< ans << endl;
 
	return 0;
}