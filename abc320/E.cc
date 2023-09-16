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

	ll n, m;
	cin>> n >> m;
	vector<ll> t(m), w(m), s(m), sou(n);
	set<ll> ready;
	map<ll, ll> comeback;
	rep(i, n) ready.insert(i);
	rep(i, m) cin >> t[i] >> w[i] >> s[i];

	rep(i, m) {
		// cout<< "rap:: " << i <<endl;
		set<ll> erase_key;
		if(comeback.size()){
			for(auto mp: comeback){
				if(mp.first<=t[i]){
					ready.insert(mp.second);
					erase_key.insert(mp.first);
				}else{
					break;
				}
			}
		}
		if(erase_key.size()){
			for(auto st: erase_key) comeback.erase(st);
		}
		// cout<< i SP << ready.size() <<endl;
		if(ready.empty()) continue;
		ll eat=*ready.begin();
		// cout<< "eat: " << eat <<endl;
		ready.erase(ready.begin());
		// cout<< "#" <<endl;
		sou[eat]+=w[i];
		// cout<< "#" <<endl;
		comeback[t[i]+s[i]]=eat;
		// cout<< "#" <<endl;
	}

	rep(i, n) cout<< sou[i] << endl;
 
	return 0;
}