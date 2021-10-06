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

	int a, b, c, d, e;
	cin>> a >> b >> c >> d >> e;

	if(a==0) cout<< "1" << endl;
	if(b==0) cout<< "2" << endl;
	if(c==0) cout<< "3" << endl;
	if(d==0) cout<< "4" << endl;
	if(e==0) cout<< "5" << endl;
 
	return 0;
}