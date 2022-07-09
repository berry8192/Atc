#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll lmax=9223372036854775807;
ll mod=998244353;
// ll mod=1000000007;

struct edge{
	int to;
	int co;

	bool operator<(const edge &in) const{
		return co!=in.co ? co<in.co : to<in.to;
	};
};

// クラスカル法とかやりたいときに使う
struct s_edge{
	int to;
	int from;
	int co;

	bool operator<(const s_edge &in) const{
		return co!=in.co ? co<in.co : to<in.to ? to<in.to : from<in.from;
	};
};

// 1-indexにします
vector<vector<edge>> g;
vector<ll> dis;
vector<int> seen;
// vector<s_edge> g;
// map<int, vector<edge>> g; //配列だとMLEする場合はこっち
queue<int> que;
ll ans=0;

ll dfs(int cur){
	if(seen[cur]){
		return 0;
	}
	seen[cur]=1;
	ll tmp=0;
	rep(i, g[cur].size()){
		tmp+=dfs(g[cur][i]);
	}
	return tmp;
}

void bfs(int cur){
	if(seen[cur]){
		return 0;
	}
	seen[cur]=1;
	ans+=cur;
	rep(i, g[cur].size()){
		que.push(g[cur][i]);
	}
}

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//ll型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int n, m, a, b, c;

	cin>> n >> m;
    g.resize(n+1);
    dis.resize(n+1, lmax);
    seen.resize(n+1);

	rep(i, m){
        cin >> a >> b;
	    // cin >> a >> b >> c;

        edge tmp;
        tmp.to=b;
        tmp.co=1;
        // tmp.co=c;
        gra[a].push_back(tmp);

        edge tmpr;
        tmpr.to=a;
        tmpr.co=1;
        // tmp.co=c;
        gra[b].push_back(tmpr); // be disable directed graph

        // s_edge tmps;
        // tmps.from=a;
        // tmps.to=b;
        // tmps.co=c;
        // eg.push_back(tmps);
    }

    // sort(all(eg));
    // rep(i, n) sort(all(gra[i+1]));

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}