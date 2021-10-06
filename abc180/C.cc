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

	LLi m;
	cin>> m;

	int fsz;
	vector<LLi> f;
	for(LLi i=1;i*i<m;i++){
		if(m%i==0) f.push_back(i);
	}
	fsz=f.size();
	if((LLi)sqrt(m)*(LLi)sqrt(m)==m) f.push_back((int)sqrt(m));//平方根が約数の場合
	rep(i, fsz) f.push_back(m/f[fsz-1-i]);

	rep(i, f.size()) cout<< f[i] <<endl;
 
	return 0;
}