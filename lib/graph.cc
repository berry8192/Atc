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
struct Graph{
	vector<vector<edge>> g;
	vector<s_edge> edges;

	void init(int nn, int mm, bool weight=false, bool directed=false){
		// n頂点、m辺、重み有無、有向無向
		int uu, vv, ww;
		g.resize(nn);

		for(int i=0;i<mm;i++){
			cin>> uu >> vv;
			uu--;
			vv--;
			if(weight) cin>> ww;
			else ww=1;

			g[uu].push_back({vv, ww});
			edges.push_back({uu, vv, ww});
			if(!directed){
				g[vv].push_back({uu, ww});
				edges.push_back({vv, uu, ww});
			}
		}
	}
};

int main(){
	int n, m;
	cin>> n >> m;
	Graph graph;
	graph.init(n, m, false, true);
}