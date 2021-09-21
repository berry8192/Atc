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

	LLi n, k, ans=0;
	vector<int> v, w;

	cin>> n >> k;
	v.resize(n);
	w.resize(300001);

	rep(i, n){
		cin >> v[i];
		w[v[i]]++;
	}

	LLi ri, le, mi, tmpk, tmp;
	ri=1000000000000000001;
	le=0;
	while(ri-le>1){
		mi=(ri+le)/2;
		//GCDをmiにする
		tmpk=k;
		//cout<< mi <<endl;

		rep(i, n){
			tmp=v[i]%mi;
			if(tmp==0) continue;
			tmpk-=mi-tmp;
			if(tmpk<0) break;
		}

		if(tmpk<0) ri=mi;
		else le=mi;
	}

	// for(int i=1;i<300001;i++){
	// 	tmpk=k;
	// 	for(int j=i;j<300001;j+=i){

	// 	}
	// }

	cout<< le << endl;
 
	return 0;
}