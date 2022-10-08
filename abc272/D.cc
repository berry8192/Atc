#include <bits/stdc++.h>
using namespace std;

int a, b, ans=0;
vector< vector<bool> > board;
//vector< vector<int> > seen;
vector< vector<int> > dis;
queue<int> qh, qw;
vector<int> dh, dw;

void bfs(int h, int w){
	//移動してきた時の処理
	/*if(seen[h][w]) return;
	seen[h][w]=1;*///一度踏んだらもう踏めなくする（いる？）

	//移動する処理
	for(int i=0;i<dh.size();i++){
		if(-1<h+dh[i] && h+dh[i]<a && -1<w+dw[i] && w+dw[i]<a){
			if(dis[h+dh[i]][w+dw[i]]!=9999999) continue;
			qh.push(h+dh[i]);
			qw.push(w+dw[i]);
			dis[h+dh[i]][w+dw[i]]=dis[h][w]+1;
		}
	}
}

int main(){

	cin>> a >> b;
	board.resize(a);
	dis.resize(a);
	//seen.resize(a);
	for(int i=0;i<a;i++) board[i].resize(a);
	for(int i=0;i<a;i++) dis[i].resize(a, 9999999);
	//for(int i=0;i<a;i++) seen[i].resize(b, 0);
	dis[0][0]=0;

	for(int i=0;i<a;i++){
		for(int j=0;j<=i;j++){
			if(i*i+j*j==b){
				dh.push_back(i);
				dw.push_back(j);
				dh.push_back(j);
				dw.push_back(i);

				dh.push_back(-i);
				dw.push_back(j);
				dh.push_back(j);
				dw.push_back(-i);

				dh.push_back(i);
				dw.push_back(-j);
				dh.push_back(-j);
				dw.push_back(i);

				dh.push_back(-i);
				dw.push_back(-j);
				dh.push_back(-j);
				dw.push_back(-i);
			}
		}
	}

	qh.push(0);
	qw.push(0);
	dis[0][0]=0;
  	while (!qh.empty()) {
    	bfs(qh.front(), qw.front());
    	qh.pop();
    	qw.pop();
  	}

	//dis表示
	for(int i=0;i<a;i++){
		for(int j=0;j<a;j++){
			if(dis[i][j]==9999999) cout<< "-1 ";
			else cout<< dis[i][j] << " ";
		}
		cout<< endl;
	}


	return 0;
}