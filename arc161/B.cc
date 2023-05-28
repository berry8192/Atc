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

ll popc(ll x){
	ll rtn=0;
	while(x){
		rtn+=(x&1);
		x/=2;
	}
	return rtn;
}

int main(){

	int n, ans=0;
	vector<ll> v;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, n) {
		ll N=v[i];
		while(popc(N)<3){
			N--;
			if(N==0) break;
		}
		
		if(N==0){
			cout<< -1 <<endl;
			continue;
		}
		vector<ll> tmp;
		while(N){
			tmp.push_back(N&1);
			N/=2;
		}
		int cnt=0;
		repr(i, tmp.size()){
			if(tmp[i]==1 && cnt>=3) tmp[i]=0;
			if(tmp[i]==1) cnt++;
		}
		ll d=1, ans=0;
		rep(i, tmp.size()){
			if(tmp[i]) ans+=d;
			d*=2;
		}
		// PV(tmp);
		cout<< ans <<endl;
	}
 
	return 0;
}