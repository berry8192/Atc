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

	int n, m, a, tmp;
	vector<int> v;

	cin>> n >> m;
	v.resize(n+1);

	rep(i, m){
		cin >> a;
		auto b = upper_bound(all(v), a);
		tmp=(int)(b-v.begin())-1;
		//cout<< tmp << " ";
		if(tmp==0) cout<< "-1" <<endl;
		else cout<< n-tmp+1 <<endl;
		v[tmp]=a;
		PV(v);
	}
 
	return 0;
}