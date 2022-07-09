#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

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

	int n, tmp=0;
	vector<vector<int>> p, e;
	vector<int> m;
	map<int, int> ma, du;

	cin>> n;
	if(n==1){
		cout<< 1 <<endl;
		return 0;
	}

	m.resize(n);
	p.resize(n);
	e.resize(n);

	rep(i, n){
		cin>> m[i];
		p[i].resize(m[i]);
		e[i].resize(m[i]);
		rep(j, m[i]){
			cin>> p[i][j] >> e[i][j];
			if(ma[p[i][j]]<e[i][j]){
				ma[p[i][j]]=e[i][j];
				du[p[i][j]]=1;
			}else if(ma[p[i][j]]==e[i][j]){
				du[p[i][j]]++;
			}
		}
	}

	rep(i, n) {
		rep(j, m[i]){
			if(du[p[i][j]]==1 && ma[p[i][j]]==e[i][j]){
				tmp++;
				break;
			}
		}
	}

	cout<< min(n, tmp+1) << endl;
 
	return 0;
}