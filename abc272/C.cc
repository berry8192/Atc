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

	int n, ans=0, a, va=-1, wa=-1;
	vector<int> v, w;

	cin>> n;

	rep(i, n){
		cin >> a;
		if(a%2) v.push_back(a);
		else w.push_back(a);
	}
	sort(all(v), greater<int>());
	sort(all(w), greater<int>());

	if(v.size()<2 && w.size()<2){
		cout<< -1 <<endl;
		return 0;
	}

	if(v.size()>=2) va=v[0]+v[1];
	if(w.size()>=2) wa=w[0]+w[1];

	cout<< max(va, wa) << endl;
 
	return 0;
}