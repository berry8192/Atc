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

	ll t, d, k, x;

	cin>> t;

	rep(lp, t){
		cin>> d >> k >> x;
		vector<ll> dd={1}, su={1};
		rep(i, d){
			dd.push_back(dd[i]*k);
			su.push_back(dd[i+1]+su[i]);
		}
		// PV(dd);
		// PV(su);
		if(2*x>su[d]) x=su[d]-x;
		// cout<< su[d] <<endl;
		x=su[d]-x;
		int ans=0;
		while(x){
			rep(i, d+1){
				if(x-su[i]<0){
					if(i==1){
						ans+=x;
						break;
					}
					x-=su[i-1];
					ans++;
					break;
				}
			}
		}
		cout<< ans <<endl;
	}
 
	return 0;
}