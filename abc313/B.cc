#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;
ll mod=1000000007;

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
	int nnn, mmm;

	void init(int nn, int mm, bool weight=false, bool directed=false){
		// n頂点、m辺、重み有無、有向無向
		nnn=nn;
		mmm=mm;
		int uu, vv, ww;
		g.resize(nn);

		for(int i=0;i<mm;i++){
			cin>> uu >> vv;
			uu--;
			vv--;
			if(weight) cin>> ww;
			else ww=1;

			g[uu].push_back({vv, ww});
			edges.push_back({uu, vv, ww}); // edges
			if(!directed){
				g[vv].push_back({uu, ww});
				edges.push_back({vv, uu, ww}); // edges
			}
		}
	}
	void board_init(vector<string> bb){
		// #.形式のboardを想定
		// 頂点番号は2重forの順に0から
		int hei=bb.size();
		int wid=bb[0].size();
		g.resize(hei*wid);

		for(int i=0;i<hei-1;i++){
			for(int j=0;j<wid-1;j++){
				if(bb[i][j]=='.' && bb[i+1][j]=='.'){
					int ww=1;
					g[i*wid+j].push_back({(i+1)*wid+j, ww});
					g[(i+1)*wid+j].push_back({i*wid+j, ww});
					// edges.push_back({i*wid+j, (i+1)*wid+j, 1}); // edges
					// edges.push_back({(i+1)*wid+j, i*wid+j, 1}); // edges
				}
			}
		}
	}
	bool saikyo(int x){
		vector<int> seen(nnn);
		seen[x]=1;
		queue<int> q;
		q.push(x);
		while(!q.empty()){
			int xx=q.front();
			q.pop();
			rep(i, g[xx].size()){
				int yy=g[xx][i].to;
				if(seen[yy]) continue;
				q.push(yy);
				seen[yy]=1;
			}
		}
		int flg=1;
		rep(i, nnn){
			if(!seen[i]) flg=0;
		}
		return flg;
	}
};

int main(){
	int n, m;
	cin>> n >> m;
	Graph graph;
	graph.init(n, m, false, true);

	int ans=-1;
	rep(i, n){
		if(graph.saikyo(i)){
			if(ans!=-1){
				cout<< -1 <<endl;
				return 0;
			}
			ans=i+1;
		}
	}
	cout<< ans <<endl;
}