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

vector<int> v, seen;
set<int> st;

void gdfs(int x, int sta){
	seen[x]=1;
	x=v[x];
	if(x==sta) return;
	gdfs(x, sta);
}

void dfs(int x){
	// cout<< x <<endl;
	if(seen[x]!=0){
		for(auto itr=st.begin();itr!=st.end();itr++){
			seen[*itr]=-1;
		}
		return;
	}
	if(st.find(x)!=st.end()){
		gdfs(x, x);
		for(auto itr=st.begin();itr!=st.end();itr++){
			if(seen[*itr]<=0) seen[*itr]=-1;
		}
		return;
	}
	st.insert(x);
	dfs(v[x]);
}

int main(){

	int n, ans=0;

	cin>> n;
	v.resize(n);
	seen.resize(n);

	rep(i, n){
		cin >> v[i];
		v[i]--;
	}

	rep(i, n) {
		st.clear();
		if(seen[i]!=1) dfs(i);
	}

	rep(i, n){
		// cout<< "i: " << seen[i] <<endl;
		if(seen[i]==1) ans++;
	}

	cout<< ans << endl;
 
	return 0;
}