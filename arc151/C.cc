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

	ll n, m, past=0, pd;
	vector<ll> x, y, l, d;
	ll lsz, rsz;

	cin>> n >> m;
	if(m==0){
		if(n%2) cout<< "Takahashi" <<endl;
		else cout<< "Aoki" <<endl;
		return 0;
	}
	x.resize(m);
	y.resize(m);
	l.resize(m-1);
	d.resize(m-1);

	rep(i, m){
		cin >> x[i] >> y[i];
		if(i==0){
			lsz=x[i]-past-1;
		}else{
			l[i-1]=x[i]-x[i-1]-1;
			d[i-1]=(y[i]==y[i-1]);
		}
	}
	rsz=n-x[m-1];
	pd=y[0];

	// cout<< lsz <<endl;
	// rep(i, m-1) cout<< l[i] SP << d[i] <<endl;
	// cout<< rsz <<endl;
	int ans=0;
	if(lsz>1) ans++;
	if(rsz>1) ans++;
	rep(i, m-1){
		if(l[i]%2 && d[i]) ans++;
		if(!(l[i]%2) && !(d[i])) ans++;
	}

	if(ans%2) cout<< "Takahashi" << endl;
	else cout<< "Aoki" << endl;
 
	return 0;
}