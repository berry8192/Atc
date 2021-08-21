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

	LLi n, q, t=0, q1, q2, q3;
	vector<LLi> x, y;

	cin>> n >> q;
	x.resize(n+1);
	y.resize(n+1);

	rep(i, n+1){
		x[i]=i;
		y[i]=i;
	}

	for(int i=0;i<q;i++){
		cin >> q1;
		if(q1!=3) cin>> q2 >> q3;

		if(q1==3){
			t=1-t;
		}else if(q1==1){
			if(t==0) swap(x[q2], x[q3]);
			else swap(y[q2], y[q3]);
		}else if(q1==2){
			if(t==0) swap(y[q2], y[q3]);
			else swap(x[q2], x[q3]);
		}else{
			if(t==0) cout<< n*(x[q2]-1)+y[q3]-1 <<endl;
			else cout<< n*(x[q3]-1)+y[q2]-1 <<endl;
		}
	}
 
	return 0;
}