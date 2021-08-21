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

	int n, k, ans=0;
	vector<int> v;

	cin>> n >> k;
	v.resize(n);

	rep(i, n) cin >> v[i];

	int l=0, r=1000000001, mi, tmp;
	while(r-l>1){
		mi=(l+r)/2;
		tmp=0;
		rep(i, n){
			tmp+=(v[i]-1)/mi;
		}
		if(tmp<=k) r=mi;
		else l=mi;
	}

	cout<< r << endl;
 
	return 0;
}
