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
	rep3(i, pvv.size()-1, 1) cout << pvv[i] SP;
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

vector<int> imos(vector<int> vv){
	rep3(i, vv.size(), 1) vv[i]+=vv[i-1];
	return vv;
}

struct se{
	int l;
	int r;

	bool operator<(const se &in) const{
		return l!=in.l ? l<in.l : r<in.r;
	};
};

int main(){

	int n, m, idx=0, flag=0, mi=imax;
	ll ans=0;
	vector<se> v;
	vector<int> imo;
	map<int, vector<int>> mp;
	set<int> st;

	cin>> n >> m;
	v.resize(n);
	imo.resize(m+1);

	rep(i, n){
		cin >> v[i].l >> v[i].r;
		mi=min(mi, v[i].r);
		mp[v[i].l].push_back(v[i].r);
		st.insert(v[i].l);
	}
	sort(all(v));

	rep3(i, mi+1, 1) {
		int tmp=*st.rbegin();
		imo[tmp-i+1]++;
		imo[-i+2+m]--;
		st.erase(i);
		rep(j, mp[i].size()){
			st.insert(mp[i][j]);
		}
	}

	PV(imos(imo));
 
	return 0;
}