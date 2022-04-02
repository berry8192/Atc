#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;

int a, b, ans=0, lp, imax=99999999;
vector< vector<char> > board;
vector< vector<int> > seen;
vector< vector<int> > dis;
vector<int> flag(4);
queue<int> qh, qw, d;
int dix[]={1, -1, -1, 1};
int diy[]={1, 1, -1, -1};

void bfs(int h, int w, int di){
	//移動してきた時の処理
	if(seen[h][w]) return;
	seen[h][w]=1;//一度踏んだらもう踏めなくする（いる？）
//cout<< h << " "  << w <<endl;
	//移動する処理
	lp=1;
	flag={1, 1, 1, 1};
	flag[di]=0;
	if(di!=-1) flag[(di+2)%4]=0;
	while(1){
		rep(i, 4){
			if(flag[i]==0) continue;
			if(-1<h+dix[i]*lp && h+dix[i]*lp<a && -1<w+diy[i]*lp && w+diy[i]*lp<b){
				if(board[h+dix[i]*lp][w+diy[i]*lp]=='#'){
					flag[i]=0;
					continue;
				}
				if(dis[h+dix[i]*lp][w+diy[i]*lp]<=dis[h][w]+1){
					if(dis[h+dix[i]*lp][w+diy[i]*lp]<dis[h][w]+1){
						flag[i]=0;
					}
					continue;
				}
				qh.push(h+dix[i]*lp);
				qw.push(w+diy[i]*lp);
				d.push(i);
				dis[h+dix[i]*lp][w+diy[i]*lp]=dis[h][w]+1;
			}else{
				flag[i]=0;
			}
		}
		if(flag[0]+flag[1]+flag[2]+flag[3]==0) break;
		lp++;
	}
}

int main(){

	cin>> a;
	b=a;
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
	d.push(-1);
	//cout<< qh.front() << " " <<qw.front() <<endl;
	dis[x1][y1]=0;
  	while (!qh.empty()) {
    	bfs(qh.front(), qw.front(), d.front());
    	qh.pop();
    	qw.pop();
    	d.pop();
  	}

	//dis表示
	// for(int i=0;i<a;i++){
	// 	for(int j=0;j<b;j++){
	// 		if(dis[i][j]==imax) cout<< "x ";
	// 		else cout<< dis[i][j] << " ";
	// 	}
	// 	cout<< endl;
	// }
	
	if(dis[x2][y2]==imax) cout<< "-1" <<endl;
	else cout<< dis[x2][y2] <<endl;

	return 0;
}