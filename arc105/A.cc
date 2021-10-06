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

	int a, b, c, d;
	cin>> a >> b >> c >> d;

	if(a==b+c+d || a+b==c+d || a+c==b+d || a+d==b+c || a+b+c==d || a+b+d==c || a+c+d==b) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}