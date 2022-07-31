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

	int n, m, ans=0;
	vector<int> u, v;
	int bo[101][101];

	cin>> n >> m;
	u.resize(m);
	v.resize(m);

	rep(i, 101){
		rep(j, 101){
			bo[i][j]=0;
		}
	}

	rep(i, m){
		cin >> u[i] >> v[i];
		bo[u[i]][v[i]]=1;
		bo[v[i]][u[i]]=1;
	}

	rep(i, n+1){
		rep3(j, n+1, i+1){
			rep3(k, n+1, j+1){
				if(bo[i][j]==1 && bo[i][k]==1 && bo[j][k]==1){
					ans++;
				}
			}
		}
	}

	cout<< ans << endl;
 
	return 0;
}