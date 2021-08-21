#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

int main(){

	LLi a, r, n;

	cin>> a >> r >> n;
	
	if(r==1){
		cout<< a << endl;
		return 0;
	}

	rep(i, n-1){
		a*=r;
		if(1000000000<a){
			cout<< "large" <<endl;
			return 0;
		}
	}

	cout<< a <<endl;
 
	return 0;
}