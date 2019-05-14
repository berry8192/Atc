#include <bits/stdc++.h>
#include <vector>
#include <cmath>

using namespace std;

int n;
int cnt=0;
vector< vector<int> > board;

void sol(vector<int> che, int now){
	int flag=0;
	int jud=1;

	for(int i=1;i<n;i++) jud*=che[i];
	if(jud==1){
		cnt++;
		for(int i=2;i<n;i++) che[i]=0;
		che[1]=1;
		flag=1;
	}

	if(flag==0){
		for(int i=1;i<n;i++){
			if(board[now][i]==1 && che[i]==0){
				che[i]=1;
				sol(che, i);
				che[i]=0;
			}
		}
	}
	
}

int main(){

	int m, a, b;
	vector<int> che;

	cin>> n >> m;
	n++;

	che.resize(n);
	for(int i=2;i<n;i++) che[i]=0;
	che[1]=1;
	board.resize(n);
	for(int i=0;i<n;i++) board[i].resize(n);

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			board[i][j]=0;
		}
	}

	for(int i=0;i<m;i++){
		cin>> a >> b;
		board[a][b]=1;
		board[b][a]=1;
	}

	sol(che, 1);

	cout<< cnt << endl;


}
