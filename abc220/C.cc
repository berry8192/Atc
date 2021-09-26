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

	LLi n, x, ans, su=0, lp;
	vector<LLi> v;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		su+=v[i];
	}
	cin>> x;

	lp=x/su;
	ans=lp*n;
	x-=su*lp;

	rep(j, 2){
		rep(i, n){
			ans++;
			x-=v[i];
			if(x<0){
				cout<< ans <<endl;
				return 0;
			}
		}
	}
 
	return 0;
}