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

struct kei{
	int h;
	int p;

	bool operator<(const kei &in) const{
		return h!=in.h ? h>in.h : p<in.p;
	};
};

vector<vector<int>> g;
vector<int> seen, power;
set<kei> st;

void bfs(){
	kei tmp=(*st.begin());
	st.erase(st.begin());
	int h=tmp.h;
	int p=tmp.p;
	// cout<< "dfs " << h SP << p <<endl;
	seen[p]=1;
	if(h<=power[p]) return;
	power[p]=h;
	if(h<=0) return;
	rep(i, g[p].size()){
		st.insert({h-1, g[p][i]});
	}
}

int main(){

	int n, m, k;
	cin>> n >> m >> k;
	g.resize(n);
	seen.resize(n);
	power.resize(n);
	vector<int> a(m), b(m), p(k), h(k);

	rep(i, m){
		cin >> a[i] >> b[i];
		a[i]--;
		b[i]--;
		g[a[i]].push_back(b[i]);
		g[b[i]].push_back(a[i]);
	}
	rep(i, k){
		cin >> p[i] >> h[i];
		p[i]--;
	}

	rep(i, k) {
		st.insert({h[i], p[i]});
	}

	while(!st.empty()){
		bfs();
	}

	int ans=0;
	rep(i, n){
		if(seen[i]==1){
			ans++;
		}
	}
	
	cout<< ans <<endl;
	rep(i, n){
		if(seen[i]==1){
			cout<< i+1 SP;
		}
	}
	cout<< endl;
 
	return 0;
}