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

	int n;
	string s;
	set<ll> st;
	ll pos=0;

	cin>> n;
	cin>> s;

	st.insert(0);
	rep(i, n){
		if(s[i]=='R'){
			pos++;
		}else if(s[i]=='L'){
			pos--;
		}else if(s[i]=='U'){
			pos-=10000000;
		}else{
			pos+=10000000;
		}
		if(st.find(pos)!=st.end()){
			cout<< "Yes" <<endl;
			return 0;
		}
		st.insert(pos);
	}

	cout<< "No" << endl;
 
	return 0;
}