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

	ll n, ans=0;
	ll base=0;
	vector<ll> a;
	vector<vector<ll>> v(200010);

	cin>> n;
	a.resize(n);

	rep(i, n){
		cin >> a[i];
		v[a[i]].push_back(i);
	}

	rep3(i, n+1, 1){
		base+=(i/2)*(n+1-i);
	}

	rep(i, 200010) {
		vector<ll> buff(v[i].size());
		rep(j, v[i].size()){
			// cout<< "i: " << i <<endl;
			ll lbuff=v[i][j]+1;
			ll rbuff=n-v[i][j];
			// cout<< lbuff SP << rbuff <<endl;
			if(lbuff<=rbuff){
				if(j!=0){
					ans+=buff[j-1];
				}
			}else{
				if(j!=0){
					int pos=n-v[i][j]-1;
					auto lb=lower_bound(all(v[i]), pos);
					int idx=lb-v[i].begin();
					// cout<< "idx: " << idx <<endl;
					ans+=(j-idx)*rbuff;
					if(idx>0) ans+=buff[idx-1];
				}
			}
			if(j==0) buff[j]=lbuff;
			else buff[j]=buff[j-1]+lbuff;
			// cout<< ans <<endl;
		}
	}

	cout<< base-ans << endl;
 
	return 0;
}