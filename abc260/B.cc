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

struct pe{
	int x1;
	int x2;

	bool operator<(const pe &in) const{
		return x1!=in.x1 ? x1>in.x1 : x2<in.x2;
	};
};

int main(){

	int n, x, y, z;
	vector<int> v;
	vector<pe> a, b, c;

	cin>> n >> x >> y >> z;
	v.resize(n);
	a.resize(n);
	b.resize(n);
	c.resize(n);

	rep(i, n) cin >> a[i].x1;
	rep(i, n) cin >> b[i].x1;
	rep(i, n) c[i].x1=a[i].x1+b[i].x1;
	rep(i, n){
		a[i].x2=i;
		b[i].x2=i;
		c[i].x2=i;
	}

	sort(all(a));
	sort(all(b));
	sort(all(c));

	//rep(i, n) cout<< a[i].x1 SP << a[i].x2 <<endl;

	rep(i, x){
		v[a[i].x2]=1;
	}
	//PV(v);
	int cnt=0;
	rep(i, n){
		if(cnt==y) break;
		if(v[b[i].x2]!=1){
			v[b[i].x2]=1;
			cnt++;
		}
	}
	//PV(v);
	cnt=0;
	rep(i, n){
		if(cnt==z) break;
		if(v[c[i].x2]!=1){
			v[c[i].x2]=1;
			cnt++;
		}
	}
	//PV(v);

	rep(i, n){
		if(v[i]) cout<< i+1 <<endl;
	}
 
	return 0;
}