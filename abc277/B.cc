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

	int n, ans=0;
	vector<string> v;
	set<string> st;
	string d2="A23456789TJQK";

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		if(v[i][0]!='H' && v[i][0]!='D' && v[i][0]!='C' && v[i][0]!='S'){
			cout<< "No" <<endl;
			return 0;
		}
		int flag=1;
		rep(j, 13){
			if(v[i][1]==d2[j]){
				flag=0;
			}
		}
		if(flag){
			cout<< "No" <<endl;
			return 0;
		}
		if(st.find(v[i])!=st.end()){
			cout<< "No" <<endl;
			return 0;
		}
		st.insert(v[i]);
	}

	cout<< "Yes" << endl;
 
	return 0;
}