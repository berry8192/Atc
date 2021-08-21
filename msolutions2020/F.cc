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

	int n, ans=0, mi=imax;
	vector<int> x, y;
	vector<char> u;
	vector< vector<int> > ud, ul, ur, du, dl, dr, lu, ld, lr, ru, rd, rl;

	cin>> n;
	x.resize(n);
	y.resize(n);
	u.resize(n);

	ud.resize(200001);
	ul.resize(400001);
	ur.resize(400001);
	du.resize(200001);
	dl.resize(400001);
	dr.resize(400001);
	lu.resize(400001);
	ld.resize(400001);
	lr.resize(200001);
	ru.resize(400001);
	rd.resize(400001);
	rl.resize(200001);

	rep(i, n) cin >> x[i] >> y[i] >> u[i];

	rep(i, n) {
		if(u[i]=='U'){
  }

		if(u[i]=='U'){
			ud[x[i]].insert(y[i]);
			ul[x[i]+y[i]].insert(y[i]);
			ur[x[i]-y[i]].insert(y[i]);
		} 
		if(u[i]=='D'){
			du[x[i]].insert(y[i]);
			dl[x[i]-y[i]].insert(y[i]);
			dr[x[i]+y[i]].insert(y[i]);
		} 
		if(u[i]=='L'){
			lu[x[i]-y[i]].insert(x[i]);
			ld[x[i]+y[i]].insert(x[i]);
			lr[y[i]].insert(x[i]);
		} 
		if(u[i]=='R'){
			ru[x[i]+y[i]].insert(x[i]);
			rd[x[i]-y[i]].insert(x[i]);
			rl[y[i]].insert(x[i]);
		} 
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}