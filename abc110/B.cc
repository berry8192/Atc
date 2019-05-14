#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int n, m, x, y, xma=-110, ymi=110, inn;

	cin>> n >> m >> x >> y;

	for(int i=0;i<n;i++){
		cin>> inn;
		xma=max(xma, inn);
	}
	for(int i=0;i<m;i++){
		cin>> inn;
		ymi=min(ymi, inn);
	}

	for(int i=x+1;i<=y;i++){
		if(xma<i && i<=ymi){
			cout<< "No War" << endl;
			return 0;
		}
	}

	cout<< "War" << endl;


}
