#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int n;
	int count=1;
	vector<int> d;

	cin>> n;
	d.resize(n);

	for(int i=0;i<n;i++) cin>> d[i];

	sort(d.begin(), d.end());

	for(int i=1;i<n;i++) if(d[i]!=d[i-1]) count++;

	cout<< count << endl;


}
