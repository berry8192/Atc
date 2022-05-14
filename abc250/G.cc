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

	int n;
	ll ans=0;
	vector<int> v;
	multiset<int> l, r, m;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, n) {
		m.insert(v[i]);
		//cout<< *l.begin() <<endl;
		if((!r.size() || *m.begin()<=*r.begin()) && *m.begin()<v[i]){
			ans+=v[i]-*m.begin();
			//cout<< *m.begin() SP << v[i] <<endl;
			m.erase(m.begin());
			m.erase(m.find(v[i]));
			r.insert(v[i]);
		}
		if((r.size() && *m.begin()>*r.begin()) && *r.begin()<v[i]){
			ans+=v[i]-*r.begin();
			//cout<< *r.begin() SP << v[i] <<endl;
			m.insert(*r.begin());
			r.erase(r.begin());
			r.insert(v[i]);
		}
	}

	cout<< ans << endl;
 
	return 0;
}