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

	int t, ans;
	vector<int> l, r;

	cin>> t;
	l.resize(t);
	r.resize(t);

	rep(i, t) cin >> l[i] >> r[i];

	rep(i, t) {
		int tmp=to_string(r[i]).size();
		int ten=1;
		rep(j, tmp-1) ten*=10;
		//cout<< ten <<endl;
		if(l[i]>=ten){
			cout<< r[i]-l[i]+1 <<endl;
			continue;
		}
		ans=r[i]-ten;
		if(to_string(r[i])[0]!='1'){
			cout<< ans+1 <<endl;
			continue;
		}
		//cout<< ans <<endl;
		ans+=ten-max(max(l[i]-1, r[i]/10), r[i]%ten);
		// if(r[i]%(ten/10)==0 && r[i]/10>=l[i] && r[i]%(ten)>=l[i]){
		// 	ans++;
		// 	// return 1;
		// }
		cout<< ans <<endl;
	}
 
	return 0;
}