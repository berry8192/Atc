#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int a, b, dep=0, mrk;
int up;
vector< vector<int> > board;
vector<int> h;
vector<int> w;

void pas(int x, int y){
	if(0<x){
		if(board[x][y]+1<board[x-1][y]){
			h.emplace_back(x-1);
			w.emplace_back(y);
			up++;
		}
		board[x-1][y]=min(board[x-1][y], board[x][y]+1);
	}

	if(x+1<a){
		if(board[x][y]+1<board[x+1][y]){
			h.emplace_back(x+1);
			w.emplace_back(y);
			up++;
		}
		board[x+1][y]=min(board[x+1][y], board[x][y]+1);
	}

	if(0<y){
		if(board[x][y]+1<board[x][y-1]){
			h.emplace_back(x);
			w.emplace_back(y-1);
			up++;
		}
		board[x][y-1]=min(board[x][y-1], board[x][y]+1);
	}

	if(y+1<b){
		if(board[x][y]+1<board[x][y+1]){
			h.emplace_back(x);
			w.emplace_back(y+1);
			up++;
		}
		board[x][y+1]=min(board[x][y+1], board[x][y]+1);
	}
}

	/*board[h-1][w]=min(board[h-2][w], board[h][w], board[h-1][w-1], board[h-1][w+1]);
	board[h+1][w]=min(board[h][w], board[h+2][w], board[h+1][w-1], board[h+1][w+1]);
	board[h][w-1]=min(board[h-1][w-1], board[h+1][w-1], board[h][w-2], board[h][w]);
	board[h][w+1]=min(board[h-1][w+1], board[h+1][w+1], board[h][w], board[h][w+2]);*/

int main(){

	char s;

	cin>> a >> b;
	board.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);

	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cin>> s;
			if(s=='#'){
				board[i][j]=0;
				h.emplace_back(i);
				w.emplace_back(j);
			}else{
				board[i][j]=5000;
			}
		}
	}

	while(1){
		mrk=h.size();
		up=0;
		for(int i=0;i<mrk;i++) pas(h[i], w[i]);
		h.erase(h.begin(), h.begin() + mrk-1);
		w.erase(w.begin(), w.begin() + mrk-1);

	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cout<< board[i][j] << " ";
		}
		cout<< endl;
	}
	cout<< endl;

		if(up==0) break;
		dep++;
	}

	cout<< dep << endl;

}
