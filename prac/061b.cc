#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main(){

	int n, m, a, b;
	vector<int> x;

	cin>> n >> m;

	x.resize(n);
	for(int i=0;i<n;i++) x[i]=0;

	for(int i=0;i<m;i++){
		cin>> a >> b;
		x[a-1]++;
		x[b-1]++;
	}

	for(int i=0;i<n;i++) cout<< x[i] << endl;


}
