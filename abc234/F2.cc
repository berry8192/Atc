#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
ll mod=998244353;

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

	int n;
	string s;
	ll ans=0;
	vector<int> d(26), r;
	vector<vector<int>> v, bo;

	cin>> s;
	n=s.size();
	r.resize(n+1);
	v.resize(n+1);
	bo.resize(26);
	rep(i, n+1) v[i].resize(26);

	rep(i, n){
		d[int(s[i]-'a')]++;
	}
	rep(i, 26) bo[i].resize(d[i]);

	int su=0;
	rep(i, 26){
		if(d[i]){
			v[1][i]=1;
			bo[i][1]=1;
			su++;
		}
	}
	rep(i, 26) bo[i][0]=su-bo[i][1];

	rep3(i, n+1, 2) {
		rep(j, 26){
			ll tmp=0;
			repr(k, d[j]-1){
				tmp+=bo[j][k+1];
				bo[j][k+1]=bo[j][k];
			}
		}
		rep(j, 26) r[i]+=v[i][j];
		r[i]%=mod;
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}