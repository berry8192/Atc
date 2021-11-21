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
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int n, k, p;
	vector<int> v, w, ans;

	cin>> n >> k;
	v.resize(n);
	w.resize(1210);
	ans.resize(n);

	rep(i, n) {
		rep(j, 3){
			cin>> p;
			v[i]+=p;
		}
	}

	rep(i, n) w[v[i]]++;
	for(int i=1000;i>=0;i--) w[i]+=w[i+1];

	rep(i, n){
		if(w[v[i]+301]<k) cout<< "Yes" << endl;
		else cout<< "No" << endl;
	}
 
	return 0;
}