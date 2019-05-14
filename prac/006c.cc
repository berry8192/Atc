#include <bits/stdc++.h>

using namespace std;

int main(){

	int n, m;

	cin>> n >> m;

	if(m<2*n || 4*n<m){
		printf("-1 -1 -1\n");
		return 0;
	}

	for(int b=n;0<=b;b--){
		if((n-b)*2+b*3==m){
			cout<< n-b << " " << b << " " << "0" << endl;
			return 0;
		}
		if((n-b)*4+b*3==m){
			cout<< "0" << " " << b << " " << n-b << endl;
			return 0;
		}
		
	}
	printf("-1 -1 -1\n");

}
