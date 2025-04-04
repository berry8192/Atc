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

	ll n, l, ans=0, z, su=0;
	vector<int> v;
	multiset<ll> st;

	cin>> n >> l;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		st.insert(v[i]);
		su+=v[i];
	}
	z=l-su;
	if(z){
		st.insert(z);
		n++;
	}

	rep(i, n-1) {
		auto itr=st.begin();
		ll tmp=*itr;
		st.erase(itr);
		auto itr2=st.begin();
		tmp+=*itr2;
		st.erase(itr2);
		ans+=tmp;
		st.insert(tmp);
		//cout<< ans <<endl;
	}

	cout<< ans << endl;
 
	return 0;
}