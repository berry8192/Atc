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

vector<ll> pri={1, 2, 3};
void mplist(ll x){
	int flag;

	for(int i=5;i<=x;i+=2){
		flag=0;
		for(int j=1;j<(int)pri.size();j++){
			if(i%pri[j]==0){
				flag=1;
				break;
			}
			if(x<pri[j]*pri[j]) break;
		}
		if(flag==0) pri.emplace_back(i);
	}
}

ll sqrtl(ll x){
	ll l=0, r=3030000000, mi;
	while(r-l>1){
		mi=(l+r)/2;
		if(mi*mi<x){
			l=mi;
		}else{
			r=mi;
		}
	}
	return r;
}

int main(){
	mplist(3001000);

	int t;
	ll n;

	cin>> t;

	rep(lp, t){
		cin>> n;
		// cout<< sqrtl(n) <<endl;
		// return 0;
		int flag=0;
		for(ll j=1;j<pri.size();j++){
			ll i=pri[j];
			if(n%(i*i)==0){
				cout<< i SP << n/(i*i) <<endl;
				flag=1;
				break;
			}
		}
		if(flag) continue;
		for(ll j=1;j<pri.size();j++){
			ll i=pri[j];
			if(n%i==0){
				cout<< sqrtl(n/i) SP << i <<endl;
				break;
			}
		}
	}
 
	return 0;
}