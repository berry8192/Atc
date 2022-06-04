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

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

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

int main(){

	ll n, ans=0;

	cin>> n;
	mplist(n+100);

	//PV(pri);
	rep3(i, n+1, 1){
		ll tmp=i;
		ll avo=1;
		for(int j=1;j<pri.size();j++){
			if(tmp<pri[j]*pri[j]) break;
			while(tmp%(pri[j]*pri[j])==0){
				tmp/=pri[j]*pri[j];
				avo*=pri[j]*pri[j];
			}
		};
		//cout<< tmp <<endl;
		// rep3(j, 1000, 2){
		// 	if(tmp*j*j>n){
		// 		ans+=j;
		// 		break;
		// 	}
		// }
		//cout<< i SP << tmp <<endl;
		rep3(j, 1000, 2){
			if(tmp*j*j>n){
				ans+=j-1;
				break;
			}
		}
	}

	cout<< ans << endl;
 
	return 0;
}