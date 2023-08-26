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

	int n, k;
	vector<int> a, v;

	cin>> n >> k;
	a.resize(n);

	rep(i, n) cin >> a[i];
	
	set<int> st;
	rep(bit, (1<<n)){
		int cnt=0;
		int tmp=0;
		rep(j, n){
			if(bit & (1<<j)){
				cnt++;
				tmp+=a[j];
			}
		}
		if(cnt==k) v.push_back(tmp);
	}

	int ans=0;
	rep(i, v.size()) ans+=v[i];

	cout<< ans << endl;
 
	return 0;
}