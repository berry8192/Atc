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

	int n;
	vector<double> ans(3); 
	vector<int> v;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, n) {
		ans[0]+=abs(v[i]);
		ans[1]+=1.0*v[i]*v[i];
		ans[2]=max(ans[2], abs(1.0*v[i]));
	}
	ans[1]=sqrt(ans[1]);

	rep(i, 3) printf("%.12lf\n", ans[i]);
 
	return 0;
}