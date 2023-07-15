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

vector<ll> RollingHash(string str){
	ll mod=1000000007;
	ll mod2=998244353;
	ll tmp=0;
	ll tmp2=0;
	ll d=1;
	ll d2=1;
	vector<ll> rtn(2);
	for(int i=0;i<str.size();i++){
		tmp+=int(str[i]-'a'+1)*d;
		tmp%=mod;
		d*=27;
		d%=mod;
		tmp2+=int(str[i]-'a'+1)*d2;
		tmp2%=mod2;
		d2*=27;
		d2%=mod;
		// v[j][tmp]++;
		// w[i].push_back(tmp);
		// v2[j][tmp2]++;
		// w2[i].push_back(tmp2);
	}
	rtn[0]=tmp;
	rtn[1]=tmp2;
	return rtn;
}

int main(){

	int n, ans=0;
	vector<string> v;
	set<ll> st;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, n) {
		string t=v[i];
		reverse(all(t));
		if(v[i]<t) v[i]=t;
		ll hsh=RollingHash(v[i])[0]*1000000000+RollingHash(v[i])[1];
		if(st.find(hsh)==st.end()) ans++;
		st.insert(hsh);
	}

	cout<< ans << endl;
 
	return 0;
}