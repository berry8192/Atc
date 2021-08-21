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

	LLi n;
	LLi ans=0;
	vector<LLi> v;

	cin>> n;
	v.resize(n);

	for(LLi i=0;i<n;i++){
		cin >> v[i];
		//v[i]+=100000000;
	}
	sort(v.begin(), v.end());

	for(LLi i=0;i<n;i++){
		ans-=(n-1-i)*v[i];
		ans+=i*v[i];
	}
	//ans-=n*100000000/2;

	cout<< ans << endl;
 
	return 0;
}