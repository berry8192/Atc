#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int h, w, h1, w1, h2, w2, flag=1;
	LLi sc, de, ans=0;
	vector< vector<LLi> > bo, v, mi;

	cin>> h >> w >> h1 >> w1 >> h2 >> w2;
	if(h1<=h2 && w1<=w2){
		cout<< 0 <<endl;
		return 0;
	}
	bo.resize(h+1);
	v.resize(h+1);
	mi.resize(h+1);
	rep(i, h+1) bo[i].resize(w+1);
	rep(i, h+1) v[i].resize(w+1);
	rep(i, h+1) mi[i].resize(w+1);

	rep(i, h){
		rep(j, w){
			cin>> bo[i][j];
		}
	}
	rep(i, h){
		rep(j, w){
			v[i+1][j+1]=v[i][j+1]+bo[i][j];
		}
	}
	PVV(v);

	rep(i, h){
		if(i+h2>h) break;
		rep(j, w){
			if(j+w2>w) break;
			cout<< i+h2 SP << i+w2 SP << i+1 SP <<j+1 <<endl;
			de=v[i+h2][j+w2]-v[i+1][j+1];
			cout<< de <<endl;
		}
	}

	// rep(i, h){
	// 	if(i+h1>h) break;
	// 	rep(j, w){
	// 		if(j+w1>w) break;
	// 		sc=v[i+h1+1][j+w1+1]-v[i+1][j+1];

 
	return 0;
}