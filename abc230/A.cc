#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
LLi llimax=9223372036854775807;
LLi mod=1000000007;

int main(){

	int a;
	cin>> a;
    if (a>=42) a++;
	string s;
	if (a<100){
		s += "0";
	}	
	if (a<10){
		s += "0";
	}	
	
	to_string(a);

	cout<< "AGC";
	cout<< s;
	cout<< a;
}