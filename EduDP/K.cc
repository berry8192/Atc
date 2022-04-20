#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;
using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;
using mint = modint1000000007;
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
	vector<int> v, ans;
	vector<string> s={"Second", "First"};

	cin>> n >> k;
	v.resize(n);
	ans.resize(k+1);
	rep(i, v[0]) ans[i]=0;

	rep(i, n) cin >> v[i];

	rep3(i, k+1, v[0]){
		int tmp=1;
		rep(j, n){
			if(i-v[j]<0) break;
			tmp*=ans[i-v[j]];
		}
		ans[i]=1-tmp;
	}
	//PV(ans);

	cout<< s[ans[k]] << endl;
 
	return 0;
}