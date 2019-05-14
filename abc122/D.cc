#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int n, a, b;
	string s, sdash;
	vector<int> x;
	vector< vector<int> > board;

	sdash=s.substr(0, 3);
	int y=atoi(sdash.c_str());

	cin>> n;
	x.resize(n);

	cin>> a >> b;
	board.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cout<< board[a][b] << endl;
		cout<< endl;
		}
	}

	sort(s.begin(), s.end());

	for(int i=0;i<n;i++) cin>> x[i];

	cout<< n << endl;
	cout<< x[0] << " " << x[1] << endl;


}
