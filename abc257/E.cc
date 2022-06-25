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

struct nu{
	ll i;
	ll c;

	bool operator<(const nu &in) const{
		return c!=in.c ? c<in.c : i>in.i;
	};
};

int main(){

	int n, md, d, r, mi=imax;
	vector<nu> c(9);
	nu tmp;
	string ans;

	cin>> n;

	rep(i, 9){
		cin >> tmp.c;
		tmp.i=i+1;
		c[i]=tmp;
	}
	sort(all(c));

	d=n/c[0].c;
	r=n%c[0].c;
	rep(i, d) ans+=char('0'+c[0].i);

	rep(i, d){
		int ma=0, mac;
		rep(j, 9){
			if(c[j].c<=r+c[0].c && ma<c[j].i){
				ma=c[j].i;
				mac=c[j].c;
			}
		}
		ans[i]=char('0'+ma);
		r-=mac-c[0].c;
	}

	cout<< ans << endl;
 
	return 0;
}