#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int main(){

	LLi n;
	cin>> n;

	LLi ri, le, mi, su;
	ri=2000000050;
	le=1;
	while(ri-le>1){
		mi=(ri+le)/2;
		su=mi*(mi+1)/2;
		//cout<< mi SP << su <<endl;
		if(n+1<su) ri=mi;
		else le=mi;
	}
	cout<< n+1-le <<endl;
	//cout<< n SP << n+1 <<endl;

	return 0;
}