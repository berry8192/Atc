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

	LLi n, x, y, ma=-1;
	vector<LLi> v1, v2, v3, v4;

	cin>> n;
	v1.resize(n);
	v2.resize(n);
	v3.resize(n);
	v4.resize(n);

	rep(i, n){
		cin >> x >> y;
		v1[i]=x;
		v2[i]=y;
		v3[i]=x+y;
		v4[i]=x-y;
	}
	
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	sort(v3.begin(), v3.end());
	sort(v4.begin(), v4.end());

	ma=max(ma, v1[n-1]-v1[0]);
	ma=max(ma, v2[n-1]-v2[0]);
	ma=max(ma, v3[n-1]-v3[0]);
	ma=max(ma, v4[n-1]-v4[0]);

	cout<< ma << endl;
 
	return 0;
}