#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int x, y, z, lop, dlop;
	long long int k;
	vector<long long int> a, b, c, d, e;

	cin>> x >> y >> z;
	cin>> k;

	a.resize(x);
	b.resize(y);
	c.resize(z);

	for(int i=0;i<x;i++) cin>> a[i];
	for(int i=0;i<y;i++) cin>> b[i];
	for(int i=0;i<z;i++) cin>> c[i];

	sort(a.begin(), a.end(), greater<long long int>());
	sort(b.begin(), b.end(), greater<long long int>());
	sort(c.begin(), c.end(), greater<long long int>());

	lop=min(3000, x*y*z);

	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			d.emplace_back(a[i]+b[j]); 
		}
	}
	sort(d.begin(), d.end(), greater<long long int>());
	//for(int i=0;i<d.size();i++) cout<< "d " << d[i] << endl;

	dlop=min(lop, (int)d.size());
	for(int i=0;i<dlop;i++){
		for(int j=0;j<z;j++){
			e.emplace_back(d[i]+c[j]); 
		}
	}
	sort(e.begin(), e.end(), greater<long long int>());

	for(int i=0;i<k;i++) cout<< e[i] << endl;


}
