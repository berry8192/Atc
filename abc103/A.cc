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

	int a, b, c, d1, d2, d3;
	cin>> a >> b >> c;

	d1=abs(a-b);
	d2=abs(a-c);
	d3=abs(b-c);

	cout<< min(min(d1+d2, d1+d3), d2+d3) << endl;
 
	return 0;
}