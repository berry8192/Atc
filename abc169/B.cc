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

	LLi n, ans=1;
	double d=0.0;
	vector<LLi> v;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, n) {
		ans*=v[i];
		if(v[i]==0){
			cout<< "0" <<endl;
			return 0;
		}
		d+=log10(v[i]);
	}


	if(ans>1000000000000000000 || d>18.0) cout<< "-1" << endl;
	else cout<< ans << endl;
 
	return 0;
}