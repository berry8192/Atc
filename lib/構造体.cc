#include <bits/stdc++.h>
using namespace std;

//by num sort
struct xxxx{
	int value;
	int num;

	bool operator<(const xxxx &in) const{
		return num<in.num;
	};
};

//2 factor sort
struct xxxx{
	int x1;
	int x2;

	bool operator<(const xxxx &in) const{
		return x1!=in.x1 ? x1<in.x1 : x2<in.x2;
	};
};

//3 factor sort
struct xxxx{
	int x1;
	int x2;
	int x3;

	bool operator<(const xxxx &in) const{
		return x1!=in.x1 ? x1<in.x1 : x2!=in.x2 ? x2<in.x2 : x3<in.x3;
	};
};

// 区間型
struct itv{
	int le, ri;

	// 区間スケジュール的な、終わるのが早い順で始まるのが遅い順のソート用
	bool operator<(const itv &in) const{
		return ri!=in.ri ? ri<in.ri : le>in.le;
	};

	// 区間が重なっているかどうか（端点を含ませたい場合は<=を使う）
	bool cover(itv x, itv y){
		return max(x.le, y.le)<min(x.ri, y.ri);
	}
};

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