#include <bits/stdc++.h>
using namespace std;

int a, b, k, ans=0, imax=99999999;
vector< vector<char> > board;
vector< vector<int> > seen;
vector< vector<int> > dis;
queue<int> qh, qw, dh, dw, dk;

void bfs(int h, int w, int hh, int ww, int kk){
	//移動してきた時の処理
	if(seen[h][w]) return;
	seen[h][w]=1;//一度踏んだらもう踏めなくする（いる？）
//cout<< h << " "  << w <<endl;
	//移動する処理
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if(i==0 && j==0) continue;
			if(i*j!=0) continue;//8方向にする場合はコメントアウト
			if(i*hh==-1 || j*ww==-1) continue;
			if(kk!=k && (i*hh==1 || j*ww==1)) continue;
			for(int l=1;l<=k;l++){
				if(-1<h+i*l && h+i*l<a && -1<w+j*l && w+j*l<b){
					if(board[h+i*l][w+j*l]=='@') break;
					if(dis[h+i*l][w+j*l]<=dis[h][w]+1 || seen[h+i*l][w+j*l]==1) continue;
					qh.push(h+i*l);
					qw.push(w+j*l);
					dh.push(i);
					dw.push(j);
					dk.push(l);
					dis[h+i*l][w+j*l]=dis[h][w]+1;
				}else{
					break;
				}
			}
		}
	}
}

int main(){

	cin>> a >> b >> k;
	int x1, y1, x2, y2;
	char tmp;
	cin>> x1 >> y1 >> x2 >> y2;
	x1--;
	y1--;
	x2--;
	y2--;
	board.resize(a);
	dis.resize(a);
	seen.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);
	for(int i=0;i<a;i++) dis[i].resize(b, imax);
	for(int i=0;i<a;i++) seen[i].resize(b, 0);

	//1字ずつ入力する場合
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cin>> tmp;
			board[i][j]=tmp;
		}
	}

	qh.push(x1);
	qw.push(y1);
	dh.push(0);
	dw.push(0);
	dk.push(k);
	//cout<< qh.front() << " " <<qw.front() <<endl;
	dis[x1][y1]=0;
  	while (!qh.empty()) {
    	bfs(qh.front(), qw.front(), dh.front(), dw.front(), dk.front());
    	qh.pop();
    	qw.pop();
    	dh.pop();
    	dw.pop();
    	dk.pop();
  	}

	//dis表示
	/*for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			if(dis[i][j]==imax) cout<< "x ";
			else cout<< dis[i][j] << " ";
		}
		cout<< endl;
	}*/
	
	if(dis[x2][y2]==imax) cout<< "-1" <<endl;
	else cout<< dis[x2][y2] <<endl;

	return 0;
}