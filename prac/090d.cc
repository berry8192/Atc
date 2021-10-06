#include <bits/stdc++.h>
#include <cmath>

using namespace std;

int main(){

	int n, k, a, b, cnt=0;

	cin>> n >> k;

	if(k==0){
		cout<< n*n << endl;
		return 0;
	}

	for(b=k+1;b<=n;b++){
		cnt+=(b-k)*int((n-1)/b)+min(b-k, n-int((n-1)/b)*b-1);
		//cout<< b << " ";
		/*for(a=max(1, k);a<=n;a++){
			if(a%b>=k){
				cnt++;
				cout<< "1";
			}else{
				cout<< "0";
			}
		}
		cout<< endl;*/

		//cout<< (b-k)*int((n-1)/b)+min(b-k, n-int((n-1)/b)*b-1) << " " << int((n-1)/b) << " " << b-k << " " << n-int((n-1)/b)*b-1 <<endl;
		
	}

	cout<< cnt << endl;

}
