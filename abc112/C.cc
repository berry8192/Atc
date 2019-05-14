#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int n, cx, cy, ch, flag, hi;
	vector<int> x, y, h;

	cin>> n;
	x.resize(n);
	y.resize(n);
	h.resize(n);

	for(int i=0;i<n;i++){
		cin>> x[i] >> y[i] >> h[i];
		if(h[i]!=0) hi=i;
	}

	for(int cx=0;cx<=100;cx++){
	for(int cy=0;cy<=100;cy++){
		ch=h[hi]+abs(x[hi]-cx)+abs(y[hi]-cy);

		//if(ch<1) continue;
			//cout<< cx << " " << cy << " " << ch << endl;
		flag=0;

		for(int i=0;i<n;i++){
			if(ch!=h[i]+abs(x[i]-cx)+abs(y[i]-cy) && h[i]!=0){
				flag=1;
				break;
			}
			if(h[i]==0 && abs(x[i]-cx)+abs(y[i]-cy)<ch){
				flag=1;
				break;
			}
		}

		if(flag==0){
			cout<< cx << " " << cy << " " << ch << endl;
			return 0;
		}
	}
	}
			
}
