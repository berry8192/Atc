#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

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

	int n, ans=1;
	vector<string> s, t;
	map<string, int> st;

	cin>> n;
	s.resize(n);
	t.resize(n);

	rep(i, n){
		cin >> s[i] >> t[i];
		//cout<< s[i] <<endl;
		if(s[i]==t[i]){
			st[s[i]]++;
		}else{
			st[s[i]]++;
			st[t[i]]++;
		}
	}

	rep(i, n) {
		if(st[s[i]]!=1 && st[t[i]]!=1){
			cout<< "No" <<endl;
			return 0;
		}
	}

	cout<< "Yes" << endl;
 
	return 0;
}