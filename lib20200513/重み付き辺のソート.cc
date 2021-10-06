#include <bits/stdc++.h>
using namespace std;

struct Edge {
	int fr;
    int to;     // 辺の行き先
    int wei; // 辺の重み
	
	bool operator<(const Edge &in) const{
		return wei<in.wei;
	};
};

int main(){

	vector<Edge> v;
	int n, m, ans=0; //n頂点　m辺
	cin>> n >> m;

	for(int i=0;i<m;i++){
		int a, b, c;//aからbへcの重さ
		Edge tmp, rtmp;
		cin>> a >> b >> c;

		tmp.fr=a;
		tmp.to=b;
		tmp.wei=c;
		rtmp.fr=b;
		rtmp.to=a;
		rtmp.wei=c;
		v.push_back(tmp);
		v.push_back(rtmp);//有向グラフの場合はコメントアウト
	}
	
	sort(v.begin(), v.end());
	
	for(int i=0;i<m;i++){
		ans++;
	}

	cout<< ans <<endl;

	return 0;
}