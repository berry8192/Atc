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

	int n, q;
	vector<int> c, p, p1, p2, l, r, ans;

	cin>> n;
	c.resize(n);
	p.resize(n);
	p1.resize(n+1);
	p2.resize(n+1);
	rep(i, n) cin >> c[i] >> p[i];

	cin>> q;
	l.resize(q);
	r.resize(q);
	rep(i, q) cin >> l[i] >> r[i];

	rep(i, n) {
		if (c[i]==1) p1[i]=p[i];
		else p2[i]=p[i];
	}

	rep(i, n){
		p1[i+1]+=p1[i];
		p2[i+1]+=p2[i];
	}

	PV(p1);
	PV(p2);

	rep(i, q) cout<< p1[r[i]-1]-p1[l[i]-2] SP << p2[r[i]-1]-p2[l[i]-2] <<endl;
 
	return 0;
}