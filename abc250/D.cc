#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

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

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

int main(){

	ll n, ans=0;
	vector<ll> v;

	cin>> n;

	mplist(1001000);
	rep(i, pri.size()){
		if(pri[i]*pri[i]*pri[i]>n) break;
		v.push_back(pri[i]*pri[i]*pri[i]);
	}

	for(int i=1;i<v.size();i++){
		ll tmp=n/pri[i];
		auto lb = lower_bound(all(v), tmp+1);
		//cout<< i SP << tmp SP << v[lb-v.begin()] <<endl;
		if(lb-v.begin()-i-1<=0) break;
		ans+=lb-v.begin()-i-1;
		//cout<< ans << endl;
	}

	cout<< ans << endl;
 
	return 0;
}