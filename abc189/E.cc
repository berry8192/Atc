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

	LLi n, m, q, op, opt, a, b, ax, ay;
	vector<LLi> x, y, xs, xa, ys, ya, sw;

	cin>> n;
	x.resize(n);
	y.resize(n);
	rep(i, n) cin >> x[i] >> y[i];

	cin>> m;
	
	xs.push_back(1);
	xa.push_back(0);
	ys.push_back(1);
	ya.push_back(0);
	sw.push_back(0);

	rep(i, m){
		cin>> op;
		if(op==1){
			sw.push_back(1-sw[i]);
			if(sw[i]==1){
				xs.push_back(xs[i]);
				xa.push_back(ya[i]);
				ys.push_back(ys[i]*-1);
				ya.push_back(xa[i]);
			}else{
				xs.push_back(ys[i]);
				xa.push_back(xa[i]);
				ys.push_back(xs[i]*-1);
				ya.push_back(ya[i]);
			}
		}else if(op==2){
			sw.push_back(1-sw[i]);
			if(sw[i]==1){
				xs.push_back(xs[i]*-1);
				xa.push_back(ya[i]);
				ys.push_back(ys[i]);
				ya.push_back(xa[i]);
			}else{
				xs.push_back(ys[i]*-1);
				xa.push_back(xa[i]);
				ys.push_back(xs[i]);
				ya.push_back(ya[i]);
			}
		}else if(op==3){
			cin>> opt;
			sw.push_back(sw[i]);
			if(sw[i+1]){
				xs.push_back(ys[i]*-1);
				xa.push_back(ya[i]+2*opt);
				ys.push_back(xs[i]);
				ya.push_back(xa[i]);
			}else{
				xs.push_back(xs[i]*-1);
				xa.push_back(xa[i]+2*opt);
				ys.push_back(ys[i]);
				ya.push_back(ya[i]);
			}
		}else{
			cin>> opt;
			sw.push_back(sw[i]);
			if(sw[i+1]){
				xs.push_back(ys[i]);
				xa.push_back(ya[i]);
				ys.push_back(xs[i]*-1);
				ya.push_back(xa[i]+2*opt);
			}else{
				xs.push_back(xs[i]);
				xa.push_back(xa[i]);
				ys.push_back(ys[i]*-1);
				ya.push_back(ya[i]+2*opt);
			}
		}
	}

	cin>> q;
	rep(i, q){
		cin>> a >> b;
		b--;
		if(sw[a]==0){
			ax=x[b]*xs[a]+xa[a];
			ay=y[b]*ys[a]+ya[a];
		}else{
			ax=y[b]*ys[a]+ya[a];
			ay=x[b]*xs[a]+xa[a];
		}
		cout<< ax SP << ay <<endl;
	}
 
	return 0;
}