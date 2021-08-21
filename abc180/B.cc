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

	cout << fixed << setprecision(12);
	int n;
	double tmp, dm=0, de=0, dc=0;

	cin>> n;

	rep(i, n){
		cin >> tmp;
		dm+=abs(tmp);
		de+=tmp*tmp;
		dc=max(dc, abs(tmp));
	}

	de=sqrt(de);

	cout<< dm << endl;
	cout<< de << endl;
	cout<< dc << endl;
 
	return 0;
}