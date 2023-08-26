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

template <class T> void PS(T ps) {
    // cout<< "{";
	for(auto s : ps) cout<< s SP;
	// cout<< "}";
	cout<<endl;
}

int main(){

	int n, tmp;
	vector<int> inv, v, v2;
	set<int> st, st2;

	cin>> n;
	inv.resize(n-1);

	rep(i, n-1) cin>> inv[i];
	sort(all(inv));

	rep(i, n-1){
		tmp=inv[i];
		if(i<n/3) v.push_back(tmp);
		else v2.push_back(tmp);
	}
	if(n==2){
		cout<< v[0] <<endl;
		return 0;
	}

	st.insert(v[0]);
	rep3(i, v.size(), 1) {
		set<int> nst;
		for(auto s : st){
			if(abs(s+v[i])<20000) nst.insert(s+v[i]);
			if(abs(s-v[i])<20000) nst.insert(s-v[i]);
		}
		st=nst;
	}
	// PS(st);

	st2.insert(v2[0]);
	rep3(i, v2.size(), 1) {
		set<int> nst;
		for(auto s : st2){
			if(abs(s+v2[i])<20000) nst.insert(s+v2[i]);
			if(abs(s+v2[i])<20000) nst.insert(s-v2[i]);
		}
		st2=nst;
	}
	// PS(st2);

	vector<int> han;
	for(auto s : st2) han.push_back(abs(s));
	sort(all(han));

	int ans=imax;
	for(auto s : st){
		s=abs(s);
		// cout<< "s: " << s <<endl;
		auto lb=lower_bound(all(han), s);
		int lb1=*lb;
		// cout<< "lb1: " << lb1 <<endl;
		if(lb!=han.begin()) lb--;
		int lb2=*lb;
		// cout<< "lb2: " << lb1 <<endl;
		int tmp=min(abs(s-lb1), abs(s-lb2));
		ans=min(ans, tmp);
	}

	cout<< ans << endl;
 
	return 0;
}