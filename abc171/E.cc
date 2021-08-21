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

	int n, ma=0;
	vector<int> v;
	int su, ev, xo;


	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		ma=max(v[i], ma);
	}

	int tmp=1;
	while(1){
		tmp*=2;
		if(ma<tmp) break;
	}
	ev=tmp-1;
	//cout<< ev <<endl;

	su=v[0];
	for(int i=1;i<n;i++) {
		//su=(su&v[i])&(su|v[i]);
		su=su^v[i];
	}

	if(n%2==1) su=su^ev;

	rep(i, n){
		xo=su^v[i];
		cout<< xo <<endl;
	}
 
	return 0;
}