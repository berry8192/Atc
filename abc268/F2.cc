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

//2 factor sort
struct xxxx{
	double x1;
	int x2;

	bool operator<(const xxxx &in) const{
		return x1!=in.x1 ? x1<in.x1 : x2<in.x2;
	};
};

int main(){

	int n;
	ll su=0, psu;
	string s;
	vector<string> v;
	vector<int> d(10), pd(10);
	vector<int> w;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
	}
	//PV(d);

	rep(i, n) w.push_back(i);

	do {
		s="";
		rep(i, n) s+=v[w[i]];
		ll x=0, ans=0;
		rep(i, s.size()){
			if(s[i]=='X') x++;
			else ans+=x*(int(s[i]-'0'));
		}
		if(ans>=3010) cout<< s <<endl;
	} while (next_permutation(all(w)));

	return 0;
}