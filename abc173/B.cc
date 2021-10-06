#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int n, a=0, b=0, c=0, d=0;
	string s;

	cin>> n;

	rep(i, n) {
		cin>> s;
		if(s=="AC") a++;
		if(s=="WA") b++;
		if(s=="TLE") c++;
		if(s=="RE") d++;
		
	}

	cout<< "AC x " << a << endl;
	cout<< "WA x " << b << endl;
	cout<< "TLE x " << c << endl;
	cout<< "RE x " << d << endl;
 
	return 0;
}