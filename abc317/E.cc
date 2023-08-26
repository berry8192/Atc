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
	int n, m;
	vector<vector<edge>> g;
	vector<s_edge> edges;

	void init(int nn, int mm, bool weight=false, bool directed=false){
		n=nn;
		m=mm;
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
			edges.push_back({uu, vv, ww}); // edges
			if(!directed){
				g[vv].push_back({uu, ww});
				edges.push_back({vv, uu, ww}); // edges
			}
		}
	}
	void board_init(vector<string> &bb){
		// #.形式のboardを想定
		// 頂点番号は2重forの順に0から
		int hei=bb.size();
		int wid=bb[0].size();
		n=hei*wid;
		g.resize(hei*wid);

		for(int i=0;i<hei;i++){
			for(int j=0;j<wid;j++){
				int ww=1;
				if(i<hei-1 && bb[i][j]=='.' && bb[i+1][j]=='.'){
					g[i*wid+j].push_back({(i+1)*wid+j, ww});
					g[(i+1)*wid+j].push_back({i*wid+j, ww});
					// edges.push_back({i*wid+j, (i+1)*wid+j, 1}); // edges
					// edges.push_back({(i+1)*wid+j, i*wid+j, 1}); // edges
				}
				if(j<wid-1 && bb[i][j]=='.' && bb[i][j+1]=='.'){
					g[i*wid+j].push_back({i*wid+j+1, ww});
					g[i*wid+j+1].push_back({i*wid+j, ww});
					// edges.push_back({i*wid+j, (i+1)*wid+j, 1}); // edges
					// edges.push_back({(i+1)*wid+j, i*wid+j, 1}); // edges
				}
			}
		}
	}

	vector<int> bfs(int x){
		// cout<< "bfs" <<endl;
		vector<int> rtn(n, imax);
		rtn[x]=0;
		queue<int> que;
		que.push(x);
		while(!que.empty()){
			int y=que.front();
			int d=rtn[y];
			que.pop();
			for(int i=0;i<g[y].size();i++){
				int to_x=g[y][i].to;
				if(d+g[y][i].co<rtn[to_x]){
					rtn[to_x]=d+g[y][i].co;
					que.push(to_x);
				}
			}
		}
		return rtn;
	}
};

int main(){
	string dir=">v<^";
	int dh[]={0, 1, 0, -1};
	int dw[]={1, 0, -1, 0};

	int h, w, sid, gid;
	cin>> h >> w;
	vector<string> v(h);
	rep(i, h) cin>> v[i];

	rep(i, h){
		rep(j, w){
			if(v[i][j]=='S'){
				sid=i*w+j;
				v[i][j]='.';
			}
			if(v[i][j]=='G'){
				gid=i*w+j;
				v[i][j]='.';
			}
		}
	}

	rep(i, h){
		rep(j, w){
			rep(k, 4){
				if(v[i][j]==dir[k]){
					v[i][j]='#';
					int lp=1;
					while(1){
						int nh=lp*dh[k]+i;
						int nw=lp*dw[k]+j;
						if(nh<0 || h<=nh || nw<0 || w<=nw) break;
						if(v[nh][nw]=='.' || v[nh][nw]=='x') v[nh][nw]='x';
						else break;
						lp++;
					}
				}
			}
		}
	}
	// rep(i, h) cout<< v[i] <<endl;

	Graph graph;
	graph.board_init(v);
	vector<int> ans=graph.bfs(sid);
	// rep(i, h){
	// 	rep(j, w){
	// 		if(ans[i*w+j]!=imax) cout<< ans[i*w+j] SP;
	// 		else cout<< -1 SP;
	// 	}
	// 	cout<< endl;
	// }
	if(ans[gid]!=imax) cout<< ans[gid] <<endl;
	else cout<< -1 <<endl;
}