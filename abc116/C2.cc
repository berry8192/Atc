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

	int n, ans=0, ma;
	vector<int> v;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];
	v.push_back(-1);

	rep(i, 110) {
		ma=0;
		rep(j, n){
			ma=max(ma, v[j]);
		}
		if(ma==0){
			cout<< ans <<endl;
			return 0;
		}
		rep(j, n){
			if(v[j]==ma){
				if(v[j]!=v[j+1]) ans++;
				v[j]--;
			}
		}
	}

	return 0;
}