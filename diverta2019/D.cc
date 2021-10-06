#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	long long int n, lmt, ans=0;
	cin>> n;

	if(n==2){
		cout<< "0" << endl;
		return 0;
	}

	lmt=(long long int)sqrt(n)+1;

	for(long long int i=1;i<lmt;i++){
		if(n%i==0 && 0<n/i && n/i-1>i){
			ans+=n/i-1;
			//cout<< i << " " << n/i-1 << endl;
		}
	}

	cout<< ans << endl;


}
