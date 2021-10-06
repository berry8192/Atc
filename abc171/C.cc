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

	LLi n, ans=26, tmp, flag=1;
	vector<LLi> v;

	cin>> n;
	n--;

	rep(i, 11){
		v.push_back(n%26);
		n/=26;

		if(n==0) break;
	}
	reverse(v.begin(), v.end());

	rep(i, v.size()-1){
		cout<< char(96+v[i]);
	}
	cout<< char(97+v[v.size()-1]) << endl;
 
	return 0;
}
