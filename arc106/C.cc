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

	LLi n, m, sig=1, swp;
	vector<LLi> l, r;

	cin>> n >> m;

	if(m==0){
		rep(i, n) {
			cout<< i*2+1 << " " << i*2+2 <<endl;
		}
		return 0;
	}

	if(n<abs(m)+2){
		cout<< "-1" <<endl;
		return 0;
	}

	if(m<0){
		sig=-1;
		m=-m;
	}

	l.resize(n);
	r.resize(n);
	l[0]=1;
	r[0]=3;

	for(int i=1;i<n;i++) {
		if (i==1){
			l[i]=2;
			r[i]=1000000;
		}else if(i<m+2){
			l[i]=i*2+2;
			r[i]=i*2+3;
		}else{
			l[i]=10000000+i*2;
			r[i]=10000000+i*2+1;
		}
	}

	if(sig==1){
		rep(i, n){
			swp=l[i];
			l[i]=1000000000-r[i];
			r[i]=1000000000-swp;
		}
	}

	rep(i, n){
		cout<< l[i] << " " << r[i] <<endl;
	}
 
	return 0;
}