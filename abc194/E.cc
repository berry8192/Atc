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

	int n, m, mi;
	vector<int> v, bo;

	cin>> n >> m;
	v.resize(n);
	bo.resize(n);
	mi=n;

	rep(i, n) cin >> v[i];

	/*rep(i, m) {
		bo[v[i]]=i+1;
	}*/

	for(int i=0;i<n;i++){
		if(bo[v[i]]+m<i+1){
			mi=min(mi, v[i]);
			//cout<< "#" << i <<endl;
		}
		bo[v[i]]=i+1;
	}

	for(int i=0;i<n;i++){
		if(bo[i]+m<n+1){
			mi=min(mi, i);
			//cout<< "$" << i <<endl;
		}
	}

	cout<< mi << endl;
 
	return 0;
}