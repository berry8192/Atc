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

	int n;
	LLi ans=0;
	vector<int> v;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];

	sort(v.begin(), v.end(), greater<int>());

	rep(i, n/2) ans+=v[i];
	ans*=2;
	ans-=v[0];
	if(n%2==1) ans+=v[n/2];

	cout<< ans << endl;
 
	return 0;
}