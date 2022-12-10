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

	int n, m, k;
	ll ans=0;
	vector<ll> v, w;
	multiset<ll> mast, mist;

	cin>> n >> m >> k;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		v[i]*=-1;
		if(i<m) w.push_back(v[i]);
	}
	sort(all(w), greater<ll>());

	rep(i, m) {
		if (i<k){
			mast.insert(w[i]);
			ans+=w[i];
		}else{
			mist.insert(w[i]);
		}
	}
	cout<< -ans SP;

	rep3(i, n, m){
		auto itr=mast.find(v[i-m]);
		if(itr!=mast.end()){
			mast.erase(itr);
			ans-=v[i-m];
			mist.insert(v[i]);
			auto itr3=mist.end();
			itr3--;
			ll tmp=*itr3;
			mast.insert(tmp);
			ans+=tmp;
			mist.erase(itr3);
		}else{
			auto itr2=mist.find(v[i-m]);
			mist.erase(itr2);
			mist.insert(v[i]);
			auto itr3=mist.end();
			itr3--;
			ll tmp=*itr3;
			mast.insert(tmp);
			ans+=tmp;
			mist.erase(itr3);
			auto itr4=mast.begin();
			tmp=*itr4;
			mist.insert(tmp);
			ans-=tmp;
			mast.erase(itr4);
		}
		cout<< -ans SP;
	}
	cout<< endl;
 
	return 0;
}