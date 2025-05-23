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

	int n, x, y, m;
	cin>> n;
	m=n-1;
	vector<int> v(n+1), ans;

	rep(i, n-1){
		cin>> x >> y;
		v[x-1]++;
		v[y-1]++;
	}
	sort(all(v), greater<int>());

	rep(i, n+1){
		int tmp=max(v[i], 2);
		m-=tmp+1;
		ans.push_back(tmp);
		if(m<=0) break;
	}
	sort(all(ans));
	PV(ans);
 
	return 0;
}