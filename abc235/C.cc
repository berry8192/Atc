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
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int n, q, ans=0;
	map<int, vector<int>> mp;
	cin>> n >> q;

	vector<int> v(n), x(q), k(q);

	rep(i, n){
		cin >> v[i];
		mp[v[i]].push_back(i+1);
	}
	rep(i, q) cin >> x[i] >> k[i];

	rep(i, q){
		if(mp[x[i]].size()<k[i]) cout<< -1 <<endl;
		else cout<< mp[x[i]][k[i]-1] <<endl;
	}
 
	return 0;
}