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

	int n, m, h, k;
	string s;
	cin>> n >> m >> h >> k;
	cin>> s;
	set<ll> st;
	int x, y, cx=0, cy=0;

	rep(i, m){
		cin >> x >> y;
		st.insert(1000000LL*x+y);
	}

	rep(i, n) {
		if (s[i]=='R') cx++;
		if (s[i]=='L') cx--;
		if (s[i]=='U') cy++;
		if (s[i]=='D') cy--;
		h--;
		if(h<0){
			cout<< "No" <<endl;
			return 0;
		}
		if(h<k && st.find(1000000LL*cx+cy)!=st.end()){
			h=k;
			st.erase(1000000LL*cx+cy);
		}
	}

	cout<< "Yes" << endl;
 
	return 0;
}