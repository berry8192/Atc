#include <bits/stdc++.h>
using namespace std;

int a, b, ch, cw, dh, dw, ans=0, numb=0;
vector< vector<int> > board;
char inc;
//vector< vector<int> > seen;
queue<int> qh, qw;

int imax=2147483647;
int dist[1000009];
vector<pair<int, int>> G[1000009];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;

map<int, int> m;

void bfs(int h, int w){
	//移動してきた時の処理
	if(board[h][w]!=0) return;
	board[h][w]=numb;
	/*if(seen[h][w]) return;
	seen[h][w]=1;*///一度踏んだらもう踏めなくする（いる？）

	//移動する処理
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if(i==0 && j==0) continue;
			if(i*j!=0) continue;//8方向にする場合はコメントアウト
			if(-1<h+i && h+i<a && -1<w+j && w+j<b){
				if(board[h+i][w+j]!=0) continue;
				qh.push(h+i);
				qw.push(w+j);
			}
		}
	}
}

int main(){

	cin>> a >> b >> ch >> cw >> dh >> dw;
	ch--;
	cw--;
	dh--;
	dw--;
	board.resize(a);
	//seen.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);
	//for(int i=0;i<a;i++) seen[i].resize(b, 0);

	//1字ずつ入力する場合
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cin>> inc;
			if(inc=='.') board[i][j]=0;
			else board[i][j]=-1;
		}
	}
	/*for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cout<< board[i][j];
		}
		cout<< endl;
	}*/

	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			if(board[i][j]==0){
				numb++;
				qh.push(i);
				qw.push(j);
  				while (!qh.empty()) {
    				bfs(qh.front(), qw.front());
    				qh.pop();
    				qw.pop();
  				}
			}
		}
	}
	/*for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cout<< board[i][j];
		}
		cout<< endl;
	}*/

	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			if(board[i][j]>0){
				m.clear();
				for(int k=max(0, i-2);k<min(a, i+3);k++){
					for(int l=max(0, j-2);l<min(b, j+3);l++){
						if(board[k][l]==-1) continue;
						if(board[i][j]!=board[k][l] && m[board[k][l]]==0){
							m[board[k][l]]=1;
        					G[board[i][j]].push_back(make_pair(board[k][l], 1));
        					G[board[k][l]].push_back(make_pair(board[i][j], 1));
						}
					}
				}
			}
		}
	}

    for (int i = 1; i <= numb; i++) dist[i] = imax;

    Q.push(make_pair(0, board[ch][cw]));
    dist[board[ch][cw]] = 0;
    while (!Q.empty()) {
        int pos = Q.top().second; Q.pop();
        for (int i = 0; i < G[pos].size(); i++) {
            int to = G[pos][i].first, cost = G[pos][i].second;
            if (dist[to] > dist[pos] + cost) {
                dist[to] = dist[pos] + cost;
                Q.push(make_pair(dist[to], to));
            }
        }
    }
//cout<< "#";
    // 距離を出力する
    /*for (int i = 1; i <= numb; i++){
		if(dist[i]==imax) cout<< "-1" <<endl;
		else cout<< dist[i] <<endl;
    }*/
	if(dist[board[dh][dw]]==imax) cout<< "-1" <<endl;
	else cout<< dist[board[dh][dw]] <<endl;

	return 0;
}