#include <bits/stdc++.h>

using namespace std;

int main(){

	int n, x, y;
  	cin>> n >> x >> y;
	x--;
	y--;
  	vector<int> ans(n);

	for(int i=0;i<n;i++){
      	for(int j=i+1;j<n;j++){
          	int tp=j-i;
          	tp=min(tp, min(abs(i-x), abs(i-y))+min(abs(j-x), abs(j-y))+1);
            ans[tp]++;
			// cout<< i << " " << j << " " << tp <<endl;
		}
	}

	for(int i=1;i<n;i++) cout<< ans[i] <<endl;

	return 0;
}
