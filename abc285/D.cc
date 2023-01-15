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

map<string, int> st;
map<string, string> mp;

void dfs(string x, int d){
	// cout<< "call" SP << x <<endl;
	if(st[x]==d){
		cout<< "No" <<endl;
		exit(0);
	}
	if(st[x]>0) return;
	st[x]=d;
	if(mp[x]!=""){
		dfs(mp[x], d);
	}
}

int main(){

	int n, ans=0;
	string s, t;
	vector<string> ss;
	set<string> tt;

	cin>> n;

	rep(i, n){
		cin >> s >> t;
		ss.push_back(s);
		tt.insert(t);
		mp[s]=t;
	}

	rep(i, n) {
		dfs(ss[i], i+1);
	}

	cout<< "Yes" << endl;
 
	return 0;
}