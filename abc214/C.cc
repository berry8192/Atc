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

	LLi n, mi=imax;
	vector<LLi> s, t, ans;

	cin>> n;
	s.resize(n);
	t.resize(n);
	ans.resize(n, imax);

	rep(i, n) cin >> s[i];
	rep(i, n) cin >> t[i];

	rep(i, 2*n) {
		mi=min(mi, t[i%n]);
		ans[i%n]=min(ans[i%n], mi);
		mi+=s[i%n];
	}

	rep(i, n) cout<< ans[i] << endl;
 
	return 0;
}