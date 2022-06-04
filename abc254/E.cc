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
vector<vector<int>> e;
vector<int> seen;
ll ans;

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

void dfs(int x, int k, int type){
	//cout<< x <<endl;
	if(seen[x]!=type){
		ans+=x+1;
	}
	seen[x]=type;
	if(k==0) return;
	rep(i, e[x].size()){
		dfs(e[x][i], k-1, type);
	}
}

int main(){

	int n, m, q;
	vector<int> a, b, x, k;

	cin>> n >> m;
	a.resize(m);
	b.resize(m);
	e.resize(n);
	seen.resize(n);
	rep(i, m){
		cin >> a[i] >> b[i];
		a[i]--;
		b[i]--;
		e[a[i]].push_back(b[i]);
		e[b[i]].push_back(a[i]);
	}
	cin>> q;
	x.resize(q);
	k.resize(q);
	rep(i, q){
		cin >> x[i] >> k[i];
		x[i]--;
	}

	rep(i, q) {
		ans=0;
		//cout<< "start " << x[i] <<endl;
		dfs(x[i], k[i], i+1);
		cout<< ans <<endl;
	}

	return 0;
}