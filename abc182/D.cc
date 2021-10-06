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

	LLi n, tmp, ma=-llimax;
	vector<LLi> v;
	vector<LLi> h, w, mw;

	cin>> n;
	v.resize(n+1);
	h.resize(n+1);
	w.resize(n+1);
	mw.resize(n+1);

	for(int i=1;i<=n;i++) cin >> v[i];

	for(int i=1;i<=n;i++){
		w[i]=w[i-1]+v[i];
		mw[i]=max(mw[i-1], w[i]);
	}

	for(int i=1;i<=n;i++) h[i]=h[i-1]+w[i];

	//PVL(w);
	//PVL(h);
	//PVL(mw);

	for(int i=0;i<n;i++){
		ma=max(ma, h[i]+mw[i+1]);
		//cout<< h[i]+mw[i+1] <<endl;
	}

	cout<< ma << endl;
 
	return 0;
}