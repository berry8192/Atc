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

	int abc=0, arc=0, agc=0, ahc=0;
	vector<string> a(3);
	cin>> a[0] >> a[1] >> a[2];

	rep(i, 3){
		if(a[i]=="ABC") abc=1;
		if(a[i]=="ARC") arc=1;
		if(a[i]=="AGC") agc=1;
		if(a[i]=="AHC") ahc=1;
	}
	if(abc==0) cout<< "ABC" << endl;
	if(arc==0) cout<< "ARC" << endl;
	if(agc==0) cout<< "AGC" << endl;
	if(ahc==0) cout<< "AHC" << endl;
 
	return 0;
}