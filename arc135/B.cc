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

int main(){

	LLi n;
	vector<LLi> s, a, tmp(3), mi(3);

	cin>> n;
	s.resize(n);
	a.resize(n+2);

	rep(i, n) cin >> s[i];

	for(int i=1;i<n;i+=3) {
		tmp[0]+=s[i]-s[i-1];
		mi[0]=min(mi[0], tmp[0]);
	}
	for(int i=2;i<n;i+=3) {
		tmp[1]+=s[i]-s[i-1];
		mi[1]=min(mi[1], tmp[1]);
	}
	for(int i=3;i<n;i+=3) {
		tmp[2]+=s[i]-s[i-1];
		mi[2]=min(mi[2], tmp[2]);
	}
	rep(i, 3) mi[i]=-mi[i];

	a[0]=max(0LL, mi[0]);
	a[1]=max(0LL, mi[1]);
	rep(i, n){
		a[i+2]=s[i]-(a[i+1]+a[i]);
		if(a[i+2]<0){
			cout<< "No" <<endl;
			return 0;
		}
	}

	cout<< "Yes" <<endl;
	PV(a);
 
	return 0;
}