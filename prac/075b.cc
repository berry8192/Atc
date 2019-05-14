#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){

	int h, w;
	vector<string> s;
	vector< vector<int> > board;

	cin>> h >> w;

	s.resize(h);
	board.resize(h);
	for(int i=0;i<h;i++) board[i].resize(w);

	for(int i=0;i<h;i++) cin>> s[i];

	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			board[i][j]=0;
		}
	}

	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(s[i].substr(j, 1)=="#"){
				for(int k=i-1;k<=i+1;k++){
					for(int l=j-1;l<=j+1;l++){
						if(0<=k && 0<=l && k<h && l<w){
							board[k][l]++;
						}
					}
				}
			}
		}
	}

	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(s[i].substr(j, 1)=="#") board[i][j]=-1;
		}
	}

	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(0<=board[i][j]){
				cout<< board[i][j];
			}else{
				cout<< "#";
			}
		}
		cout<< endl;
	}

}
