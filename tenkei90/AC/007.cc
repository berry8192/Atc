#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9123372036854775807;

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

	int n, q, b, l, r;
	vector<LLi> v, ans;

	cin>> n;
	v.resize(n);
	rep(i, n) cin >> v[i];
	v.push_back(-llimax);
	sort(all(v));
	v.push_back(llimax);
	//PVL(v);
	
	cin>> q;
	ans.resize(q);

	rep(i, q) {
		cin>> b;
		auto lb = lower_bound(all(v), b);
		l=v[lb-v.begin()-1];
		r=v[lb-v.begin()];
		//cout<< l SP << r <<endl;
		ans[i]=min(abs(b-l), abs(b-r));
	}

	//PV(ans);
	rep(i, q) cout<< ans[i] <<endl;
 
	return 0;
}