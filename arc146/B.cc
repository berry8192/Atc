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

struct xxx{
	ll x;
	int idx=0;

	bool operator<(const xxx &in) const{
		return x!=in.x ? x>in.x : idx<in.idx;
	};
};

int main(){

	ll n, m, k, nn;
	ll ans=0;
	vector<ll> v, al;
	vector<xxx> b;

	cin>> n >> m >> k;
	nn=n;
	v.resize(n);
	al.resize(n);
	b.resize(n);

	rep(i, n){
		cin >> v[i];
	}
	// sort(all(v));
	// PV(v);

	for(ll i=31;i>=0;i--){
		//b.clear();
		// int cnt=0;
		cout<< "m=" << m <<endl;
		rep(j, n){
			if(al[b[j].idx]==1){
				b[j].x=-imax;
				continue;
			}
			b[j].idx=j;
			b[j].x=v[j]-(1LL<<i);
			//cout<< "ff b["<<j<<"].x" << b[j].x <<endl;
		}
		rep(j, n){
			cout<< "ff b["<<j<<"].x" << b[j].x <<endl;
		}
		sort(all(b));
		ll su=0;
		rep(j, k){
			//cout<< "su+ " << min(0LL, b[j].x) <<endl;
			su-=min(0LL, b[j].x);
		}
		cout<< "su:" << su <<endl;
		int cnt=0;
		if(su<=m){
			// iのbitを立てることが確定
			cout<< "i:" << i <<endl;
			rep(j, n){
				if(al[b[j].idx]==1) continue;
				cout<< "look j:" << j <<endl;
				if(-b[j].x>m){
					al[b[j].idx]=1;
				}else{
					if(b[j].x>=0 || cnt<k){
						cnt++;
						cout<< "b[j].x:" << b[j].x <<endl;
						v[b[j].idx]=min(0LL, b[j].x);
						m+=v[b[j].idx];
						v[b[j].idx]=max(0LL, b[j].x);
						cout<< "v[" <<b[j].idx<< "]=" << v[b[j].idx] <<endl;
					}else{
						al[b[j].idx]=1;
					}
				}
			}
			ans+=(1LL<<i);
		}
		cout<< ans << endl;
	}

	cout<< ans << endl;
 
	return 0;
}