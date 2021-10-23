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

	cout << fixed << setprecision(12);

	int q, ans=0;
	double t, l, x, y, h, dx, dy, d;
	// height, distance_x, distance_y
	vector<int> e;

	cin>> t;
	cin>> l >> x >> y;
	cin>> q;
	e.resize(q);

	rep(i, q) cin >> e[i];

	rep(i, q) {
		h=sin(2.0*M_PI*(0.75*t+e[i])/t)*l*0.5+l*0.5;
		dy=y+sin(2.0*M_PI*e[i]/t)*l*0.5;
		dx=x;
		d=sqrt(dx*dx+dy*dy);
		//cout<< "h=" << h SP "d=" << d <<endl;
		cout<< atan2(h, d)*180.0/M_PI <<endl;
	}
 
	return 0;
}