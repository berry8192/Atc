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

	int w, h, n, A, B, m, M;
	cin>> w >> h >> n;
	vector<int> p(n), q(n);
	rep(i, n) cin >> p[i] >> q[i];
	cin>> A;
	vector<int> a(A+2);
	a[0]=0;
	a[A+1]=1000000010;
	rep(i, A) cin >> a[i+1];
	cin>> B;
	vector<int> b(B+2);
	b[0]=0;
	b[B+1]=1000000010;
	rep(i, B) cin >> b[i+1];

	if(n<1LL*(A+1)*(B+1)){
		// min=0
		// cout<< "min0" <<endl;
		m=0;
		map<ll, int> mp;
		M=0;
		rep(i, n){
			auto alb=lower_bound(all(a), p[i]);
			auto blb=lower_bound(all(b), q[i]);
			ll aa=alb-a.begin();
			ll bb=blb-b.begin();
			mp[aa*1000000010+bb]++;
			M=max(M, mp[aa*1000000010+bb]);
		}
	}else{
		m=imax;
		map<ll, int> mp;
		M=0;
		vector<vector<int>> v(A+2, vector<int>(B+2));
		rep(i, n){
			auto alb=lower_bound(all(a), p[i]);
			auto blb=lower_bound(all(b), q[i]);
			ll aa=alb-a.begin();
			ll bb=blb-b.begin();
			v[aa][bb]++;
		}
		rep3(i, A+2, 1){
			rep3(j, B+2, 1){
				m=min(m, v[i][j]);
				M=max(M, v[i][j]);
			}
		}
		// PVV(v);
	}
	

	cout<< m SP << M << endl;
 
	return 0;
}