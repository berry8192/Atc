#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
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

int dpx[510][20010], dpy[510][20010];

int main(){

	int n, x, y, cx=0, cy=0;
	vector<int> v, xx, yy;

	cin>> n >> x >> y;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		if(i>0){
			if(i%2==0) xx.push_back(v[i]);
			else yy.push_back(v[i]);
		}else{
			x-=v[0];
		}
	}
	dpx[0][10000]=1;
	dpy[0][10000]=1;
	// cout<< xx[0] <<endl;
	// cout<< x SP << y <<endl;

	rep(i, xx.size()){
		rep(j, 20001){
			if(dpx[i][j]){
				if(j-xx[i]>=0 && j-xx[i]<=20000) dpx[i+1][j-xx[i]]=1;
				if(j+xx[i]>=0 && j+xx[i]<=20000) dpx[i+1][j+xx[i]]=1;
				// cout<< j-xx[i] SP << j+xx[i] SP;
			}
		}
		// cout<< endl;
	}
	if(dpx[xx.size()][10000+x]==0){
		cout<< "No" << endl;
		return 0;
	}
	// cout<< "####" <<endl;

	rep(i, yy.size()){
		rep(j, 20001){
			if(dpy[i][j]){
				if(j-yy[i]>=0) dpy[i+1][j-yy[i]]=1;
				if(j+yy[i]<=20000) dpy[i+1][j+yy[i]]=1;
				// cout<< j SP;
			}
		}
		// cout<< endl;
	}
	if(dpy[yy.size()][10000+y]==0){
		cout<< "No" << endl;
		return 0;
	}

	cout<< "Yes" << endl;
 
	return 0;
}