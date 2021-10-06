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

	int n, k, ta, ti, flag;
	vector<int> v, w1, w2;

	cin>> n >> k;
	v.resize(n);
	w1.resize(n+1);
	w2.resize(n+1);

	rep(i, n) cin >> v[i];

	//PV(v);
	rep(i, k) {
		rep(j, n){
			w1[j]=0;
			w2[j]=0;
		}
		rep(j, n){
			ta=max(0, j-v[j]);
			ti=min(n-1, j+v[j]);
			//if(ta!=j) w1[ta]++;
			//if(ti!=j) w2[ti]++;
			w1[ta]++;
			w2[ti]++;
		}
		
		//PV(w1);
		//PV(w2);
		flag=1;
		v[0]=w1[0];
		if(v[0]!=n) flag=0;
		for(int j=1;j<n;j++){
			v[j]=v[j-1]+w1[j]-w2[j-1];
			if(v[j]!=n) flag=0;
		}
		//PV(v);
		if(flag){
			PV(v);
			return 0;
		}
	}
 
	PV(v);
	return 0;
}

/*
	PV(v);
	rep(i, k) {
		rep(j, n){
			w[j]=0;
			rep(l, n){
				if(abs(l-j)<=v[l]) w[j]++;
			}
		}
		rep(j, n) v[j]=w[j];
		PV(v);
	}
*/