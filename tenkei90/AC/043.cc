#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int a, b, ans=0;
int x[4]={0, 1, 0, -1};
int y[4]={1, 0, -1, 0};
vector< vector<char> > board;
//vector< vector<int> > seen;
vector< vector<int> > dis;
queue<int> qh, qw, qd, qds;

void bfs(int h, int w, int d){
	//移動してきた時の処理
	/*if(seen[h][w]) return;
	seen[h][w]=1;*///一度踏んだらもう踏めなくする（いる？）
	// if(dis[h][w]>=ds) dis[h][w]=ds;
	// else return;

	//移動する処理
	int lp=1;
	while(1){
		int ii=x[d]*lp;
		int jj=y[d]*lp;
		if(-1<h+ii && h+ii<a && -1<w+jj && w+jj<b){
			if(board[h+ii][w+jj]=='#' || dis[h+ii][w+jj]<=dis[h][w]) break;
			rep(i, 2) qh.push(h+ii);
			rep(i, 2) qw.push(w+jj);
			//rep3(i, 4, 1) qd.push((d+i*i*i)%4);
			rep(i, 2) qd.push((d+1+i*2)%4);
			//rep(i, 2) qds.push(dis[h][w]+1);
			dis[h+ii][w+jj]=dis[h][w]+1;
		}else{
			break;
		}
		lp++;
	}
}

int main(){

	int rs, cs, rt, ct;
	cin>> a >> b >> rs >> cs >> rt >> ct;
	rs--;
	cs--;
	rt--;
	ct--;
	board.resize(a);
	dis.resize(a);
	//seen.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);
	for(int i=0;i<a;i++) dis[i].resize(b, 9999999);
	//for(int i=0;i<a;i++) seen[i].resize(b, 0);

	//1行ずつ入力する場合
	for(int i=0;i<a;i++){
		string tmp;
		cin>> tmp;
		for(int j=0;j<b;j++){
			board[i][j]=tmp[j];
		}
	}

	rep(i, 4) qh.push(rs);
	rep(i, 4) qw.push(cs);
	rep(i, 4) qd.push(i);
	//rep(i, 4) qds.push(-1);
	dis[rs][cs]=0;
  	while (!qh.empty()) {
    	bfs(qh.front(), qw.front(), qd.front());
    	qh.pop();
    	qw.pop();
    	qd.pop();
    	//qds.pop();
  	}

	//dis表示
	// for(int i=0;i<a;i++){
	// 	for(int j=0;j<b;j++){
	// 		if(dis[i][j]==9999999) cout<< "x ";
	// 		else cout<< dis[i][j] << " ";
	// 	}
	// 	cout<< endl;
	// }

	cout<< dis[rt][ct]-1 <<endl;

	return 0;
}