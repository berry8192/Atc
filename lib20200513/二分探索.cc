#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int main(){

	int n;
	cin>> n;

	LLi ri, le, mi;
	ri=1000000000000000001;
	le=-1;
	while(ri-le>1){
		mi=(ri+le)/2;
		cout<< mi <<endl;
		if(n<mi) ri=mi;
		else le=mi;
	}
	cout<< le SP << ri <<endl;
	//cout<< n SP << n+1 <<endl;

	return 0;
}