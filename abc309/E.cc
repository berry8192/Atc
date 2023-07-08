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

struct ins{
	int pos;
	int pw;

	bool operator<(const ins &in) const{
		return pw!=in.pw ? pw>in.pw : pos<in.pos;
	};
};

vector<vector<int>> g;

int main(){

	int n, m, x, y;
	cin>> n >> m;
	vector<int> p(n), max_potential(n), reac(n);
	set<ins> st;
	g.resize(n);

	rep3(i, n, 1){
		cin>> p[i];
		p[i]--;
		g[p[i]].push_back(i);
	}

	rep(i, m){
		cin>> x >> y;
		x--;
		st.insert({x, y});
		max_potential[x]=max(y, max_potential[x]);
	}

	while(!st.empty()){
		ins tmp=*st.begin();
		st.erase(st.begin());
		// cout<< "#" << tmp.pos SP << tmp.pw <<endl;
		if(tmp.pw<max_potential[tmp.pos]) continue;
		if(tmp.pw==0){
			continue;
		}
		rep(i, g[tmp.pos].size()){
			int npos=g[tmp.pos][i];
			reac[npos]=1;
			if(tmp.pw-1<=max_potential[npos]) continue;
			max_potential[npos]=tmp.pw-1;
			st.insert({npos, tmp.pw-1});
		}
	}

	int ans=0;
	rep(i, n){
		if(max_potential[i] || reac[i]) ans++;
	}
	cout<< ans << endl;
	// PV(max_potential);
 
	return 0;
}