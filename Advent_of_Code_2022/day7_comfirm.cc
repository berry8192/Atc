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

	int ans=0;
	string s;
	set<string> st;

	cin>> s;

	int tmpi=0;
	while(1){
		cin>> s;
		if(st.find(s)!=st.end()) continue;
		st.insert(s);
		if(s=="end") break;
		if('1'<=s[0] && s[0]<='9'){
			string tmp;
			int lp=0;
			while(s[lp]!=' '){
				tmp+=s[lp];
				lp++;
			}
			int fig=stoi(tmp);
			tmpi+=fig;
		}else{
			if(tmpi<=100000) ans+=tmpi;
			tmpi=0;
		}
	}

	cout<< ans << endl;
 
	return 0;
}