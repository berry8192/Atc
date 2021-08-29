#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

int main(){

	LLi n;
	string s;

	cin>> n;

	while(0<n){
		if(n%2==0){
			n/=2;
			s+="B";
		}else{
			n--;
			s+="A";
		}
	}

	reverse(s.begin(), s.end());
	cout<< s <<endl;
 
	return 0;
}