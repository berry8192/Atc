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

	int n, k;
	vector<int> x, y, z;

	cin>> n >> k;
	x.resize(n);
	y.resize(n);
	z.resize(n);

	rep(i, n) cin >> x[i] >> y[i];

	LLi ri, le, mi;
	ri=2000000000000000001;
	le=-1;
	while(ri-le>1){
		mi=(ri+le)/2;
		//cout<< mi <<endl;
		LLi grp=0;
		rep(i, n) z[i]=0;
		rep(i, n){
			if(z[i]==0){
				grp++;
				z[i]=grp;
			}
			rep(j, n){
				if(i==j) continue;
				int flag=1;
				rep(l, n){
					if(z[l]!=grp) continue;
					if((x[l]-x[j])*(x[l]-x[j])+(y[l]-y[j])*(y[l]-y[j])>mi){
						flag=0;
						break;
					}
				}
				if(flag) z[j]=grp;
			}
		}
		if(grp<=k) ri=mi;
		else le=mi;
	}

	cout<< ri << endl;
 
	return 0;
}