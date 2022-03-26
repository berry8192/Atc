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

	int n, tmp;
	vector<int> v(10000);

	cin>> n;

	rep(i, n){
		cin >> tmp;
		v[tmp]=1;
	}

	rep(i, 2010) {
		if (v[i]==0){
			cout<< i <<endl;
			return 0;
		}
	}
 
	return 0;
}