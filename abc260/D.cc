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

int n, k;
vector<int> p, v, w, t;
set<int> st;

void dfs(int x, int tu, int d){
	if(d==0) return;
	t[x]=tu;
	dfs(v[x], tu, d-1);
}

int main(){

	cin>> n >> k;
	p.resize(n);
	v.resize(n+1);
	w.resize(n+1);
	t.resize(n+1);

	rep(i, n){
		cin >> p[i];
		p[i]=-p[i];
	}

	rep(i, n) {
		if(k==1){
			t[-p[i]]=i+1;
			continue;
		}
		auto lb=st.lower_bound(p[i]);
		//cout<< *lb << endl;
		if(lb==st.begin()){
			//cout<< "begin " << *lb << endl;
			st.insert(p[i]);
			w[-p[i]]=1;
		}else{
			lb--;
			//cout<< *lb << endl;
			v[-p[i]]=-(*lb);
			w[-p[i]]=w[-(*lb)]+1;
			st.erase(lb);
			if(w[-p[i]]==k){
				dfs(-p[i], i+1, k);
			}else{
				st.insert(p[i]);
			}
		}
	}

	//PV(t);

	rep3(i, n+1, 1){
		if(t[i]==0) cout<< -1 << endl;
		else cout<< t[i] << endl;
	}
 
	return 0;
}