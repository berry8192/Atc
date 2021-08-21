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

	LLi x, k, d, kai, d1, d2;

	cin>> x >> k >> d;

	x=abs(x);
	kai=x/d;

	if(k<=kai){
		cout<< abs(x-k*d) <<endl;
		return 0;
	}

	k-=kai;

	d1=abs(x-kai*d);
	d2=d-d1;

	if(k%2==0) cout<< d1 << endl;
	else cout<< d2 << endl;
 
	return 0;
}