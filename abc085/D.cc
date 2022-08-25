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

struct ktn{
	ll a;
	ll b;

	bool operator<(const ktn &in) const{
		return b!=in.b ? b>in.b : a>in.a;
	};
};

template <class T> vector<ll> ruiseki(T vv){
	vector<ll> xx;
  	xx.resize(vv.size()+1);
	xx[0]=0;
	for(int i=0;i<(int)vv.size();i++){
		xx[i+1]=xx[i]+vv[i];
		// xx[i+1]=xx[i+1]%mod;
	}
	return xx;
}

int main(){

	ll n, h, su=0, pos=0, ans=imax;
	vector<ktn> v;
	vector<ll> w, y;

	cin>> n >> h;
	v.resize(n);
	w.resize(n);

	rep(i, n){
		cin >> v[i].a >> v[i].b;
		w[i]=v[i].b;
	}
	sort(all(v));
	sort(all(w));
	y=ruiseki(w);

	su=0;
	repr(i, n){
		su+=w[i];
		if(h<=su){
			ans=n-1-i+1;
			break;
		}
	}

	rep(i, n) {
		auto lb=lower_bound(all(w), v[i].a);
		pos=w.end()-lb;
		//cout<< "pos:" << pos <<endl;
		su=y[n]-y[n-pos];
		//cout<< "su:" << su <<endl;
		ans=min(ans, pos+(h-su+v[i].a-1)/v[i].a);
	}

	cout<< ans << endl;
 
	return 0;
}