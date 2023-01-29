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

ll imax=2147483647;
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

	ll q, aa, bb;
	cin>> q >> aa >> bb;
	vector<ll> t(q), a(q), b(q);
	set<ll> st;
	st.insert(aa+bb);
	st.insert(aa-bb);
	st.insert(imax);
	st.insert(-imax);

	rep(i, q) cin >> t[i] >> a[i] >> b[i];

	rep(i, q) {
		if (t[i]==1){
			st.insert(a[i]+b[i]);
			st.insert(a[i]-b[i]);
		}else{
			auto li=st.lower_bound(a[i]);
			auto ri=st.lower_bound(b[i]);
			if(li!=ri){
				cout<< 0 <<endl;
			}else{
				ll mi=imax;
				if(*li!=imax){
					mi=min(*li-b[i], *li-a[i]);
				}
				// cout<< *li SP;
				li--;
				// cout<< *li <<endl;
				if(*li!=-1){
					mi=min(mi, a[i]-*li);
					mi=min(mi, b[i]-*li);
				}
				cout<< mi <<endl;
			}
		}
	}
 
	return 0;
}