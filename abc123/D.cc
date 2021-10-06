#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int lop, flag=0, count=0;
	long long int x, y, z, k, mi;
	vector<long long int> a, b, c, d;

	cin>> x >> y >> z >> k;

	a.resize(x);
	b.resize(y);
	c.resize(z);

	for(int i=0;i<x;i++) cin>> a[i];
	for(int i=0;i<y;i++) cin>> b[i];
	for(int i=0;i<z;i++) cin>> c[i];

	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	sort(c.begin(), c.end());

	lop=min(3000, x*y*z);

	mi=min(min(a[x], b[y]), c[z]);

	for(int i=0;i<lop;i++){
	if(x=0) x=1;
	if(y=0) y=1;
	if(z=0) z=1;
		if(a[x-1]<b[y-1]){
			if(a[x-1]<c[z-1]){
				x--;
			}else{
				z--;
			}

			if(b[x-1]<c[z-1]){
				y--;
			}else{
				z--;
			}
		}
	}

	for(int i=a.end();x<=i;i--){
		for(int j=b.end();y<=j;j--){
			for(int k=c.end();z<=k;k--){
				d.emplace_back(a[i]+b[j]+c[k], count);
				count++;
				
				if(count==lop-1) flag=1; 
			}
			if(flag==1) break;
		}
		if(flag==1) break;
	}

	sort(d.begin(), d.end());

	for(int i=lop-1;i>=0;i--) cout<< d[i] << endl;


}
