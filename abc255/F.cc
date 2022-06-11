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

vector<int> p, q, l, r;

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

void dfs(int x){
	auto lb = lower_bound(all(q), x);
	
}

int main(){

	int n;

	cin>> n;
	p.resize(n+1);
	q.resize(n+1);
	l.resize(n+1);
	r.resize(n+1);

	rep(i, n){
		cin >> p[i+1];
		//p[i]--;
	}
	rep(i, n){
		cin >> q[i+1];
		//q[i]--;
	}

	if(p[0]!=1){
		cout<< -1 <<endl;
		return 0;
	}

	dfs(1);

	rep(i, n) cout<< l[i+1] SP << r[i+1] << endl;
 
	return 0;
}