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
ll mod=1000000007;
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
	ll ans;
	string s;
	vector<int> v;

	cin>> n;
	cin>> s;
	cin>> s;
	s.push_back('1');

	rep(i, n){
		if(s[i]==s[i+1]){
			v.push_back(2);
			i++;
		}else{
			v.push_back(1);
		}
	}

	// PV(v);
	if(v[0]==1) ans=3;
	else ans=6;

	rep3(i, v.size(), 1){
		if(v[i-1]==1){
			if(v[i]==1){
				ans*=2;
			}else{
				ans*=2;
			}
		}else{
			if(v[i]==1){
			}else{
				ans*=3;
			}
		}
		ans%=mod;
	}

	cout<< ans << endl;
 
	return 0;
}