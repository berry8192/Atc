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

	LLi n, m, t, nw=0, bt;
	vector<LLi> a, b;

	cin>> n >> m >> t;
	a.resize(m);
	b.resize(m);

	rep(i, m) cin >> a[i] >> b[i];
	bt=n;

	rep(i, m) {
		bt-=a[i]-nw;
		if(bt<=0){
			cout<< "No" <<endl;
			return 0;
		}
		nw=b[i];
		bt+=b[i]-a[i];
		bt=min(bt, n);
	}

	if(t-nw<bt) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}