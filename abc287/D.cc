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

	int ans=0, ng=0, ms=0;
	string s, t;

	cin>> s;
	cin>> t;
	int sz=t.size();
	vector<int> mis(sz);

	rep(i, sz){
		if(t[i]!='?' && s[s.size()-sz+i]!='?' && t[i]!=s[s.size()-sz+i]){
			mis[i]=1;
			ms++;
		}
	}
	// PV(mis);
	if(ms==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;

	rep(i, sz){
		if(ng){
			cout<< "No" <<endl;
			continue;
		}
		if(t[i]=='?' || s[i]=='?' || s[i]==t[i]){
			if(mis[i]) ms--;
		}else{
			ng=1;
			cout<< "No" <<endl;
			continue;
		}
		if(ms==0) cout<< "Yes" << endl;
		else cout<< "No" << endl;
	}

	return 0;
}