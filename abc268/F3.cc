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
	string s;
	ll x;
	ll su;

	bool operator<(const xxxx &in) const{
		return x*in.su!=in.x*su ? x*in.su>in.x*su : s<in.s;
	};
};

int main(){

	int n;
	string tmp, s;
	ll ans=0;
	vector<xxxx> v;
	set<xxxx> st;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> tmp;
		int xx=0, sx=0;
		rep(j, tmp.size()){
			if(tmp[j]=='X') xx++;
			else{
				//d[int(v[i][j]-'0')]++;
				sx+=int(tmp[j]-'0');
			}
		}
		v[i].s=tmp;
		v[i].x=xx;
		v[i].su=sx;
	}
	//PV(d);

	sort(all(v));
	//PV(w);
	rep(i, n) s+=v[i].s;
	//cout<< s <<endl;

	ll x=0;
	rep(i, s.size()){
		if(s[i]=='X') x++;
		else ans+=x*(int(s[i]-'0'));
	}
	
	cout<< ans << endl;
 
	return 0;
}