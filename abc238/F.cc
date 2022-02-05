#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		cout<< "#" << i << " ";
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	LLi n, k, ans=0;
	vector<LLi> p, q;
	vector< vector<LLi> > bo;
	// bo[i][j]=1 iを選べばでjを選んでOK

	cin>> n >> k;
	p.resize(n);
	q.resize(n);
	bo.resize(n);

	rep(i, n) cin >> p[i];
	rep(i, n) cin >> q[i];

	rep(i, n){
		rep(j, n){
			if(p[i]<p[j] && q[i]<q[j]) bo[i].push_back(j);
		}
	}
	PVV(bo);

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}