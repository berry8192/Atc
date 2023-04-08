#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;
ll mod=1000000007;

template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

vector<ll> ff(ll x){
	int fsz;
	vector<ll> f;
	for(ll i=1;i*i<x;i++){
		if(x%i==0) f.push_back(i);
	}
	fsz=f.size();
	if((int)sqrt(x)*(int)sqrt(x)==x) f.push_back((int)sqrt(x));//平方根が約数の場合
	rep(i, fsz) f.push_back(x/f[fsz-1-i]);
	return f;
}

int main(){

	ll a, b, ans=0;
	cin>> a >> b;
	while(a && b){
		ll c=__gcd(a, b);
		a-=c;
		b-=c;
		ans++;
		cout<< a SP << b <<endl;
	}

	cout<< ans << endl;
 
	return 0;
}