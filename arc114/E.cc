#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
LLi mod=998244353;
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

	LLi h, w, h1, w1, h2, w2;
	vector<int> v;

	cin>> h >> w >> h1 >> w1 >> h2 >> w2;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, n) {
		if (v[i]) ans++;
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}