#include <bits/stdc++.h>
using namespace std;

int a, b, ga, gb;
vector< vector<int> > board;

void dfs(int h, int w){
	//移動してきた時の処理
	//if(seen[h][w]) return;
	board[h][w]=1;
	cout<< h+1 << " " << w+1 <<endl;
	if(h==ga && w==gb) return;

	//移動する処理
	vector< tuple<int, double, int, int> > dis;
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if(i==0 && j==0) continue;
			if(-1<h+i && h+i<a && -1<w+j && w+j<b){
				if(board[h+i][w+j]) continue;
				//int tmp=abs(h+i-ga)*(h+i-ga)*(h+i-ga)+abs(w+j-gb)*(w+j-gb)*(w+j-gb);
				int tmp=(h+i-ga)*(h+i-ga)+(w+j-gb)*(w+j-gb);
				double tmp2=(h+i-(a-0)/2.0)*(h+i-(a-0)/2.0)+(w+j-(b-0)/2.0)*(w+j-(b-0)/2.0);
				//cout<< tmp2 <<endl;
				//int tmp=abs(h+i-ga)+abs(w+j-gb);
				dis.push_back({-tmp, -tmp2, h+i, w+j});
			}
		}
	}
	sort(dis.begin(), dis.end());
	dfs(get<2>(dis[0]), get<3>(dis[0]));
}

int main(){

	cin>> a >> b >> ga >> gb;
	ga--;
	gb--;
	board.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);

	dfs(0, 0);

	return 0;
}