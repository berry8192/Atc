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

	int n;
	string t, ans;

	cin>> n;
	cin>> t;

	// rep(i, 2*n){

	// }

	rep(i, n+1) {
		int flag=1;
		// cout<< "$" << i <<endl;
		rep(j, n){
			// cout<< "$$" <<endl;
			int tmp=(i<=j);
			// cout<< "#" << t[j] <<endl;
			// cout<< "#" << t[2*n-1-j-i] <<endl;
			// cout<< "#" << t[2*n-1-j-tmp*n] <<endl;
			// cout<< "#" << t[n+j-i] <<endl;
			if(t[j]!=t[2*n-1-j-i] || t[2*n-1-j-tmp*n]!=t[n+j-i]){
				i+=max(j-1, 0);
				flag=0;
				break;
			}
		}
		if(flag){
			rep(j, 2*n){
				if(n-i==j) j+=n;
				ans+=t[j];
			}
			cout<< ans <<endl;
			cout<< n-i <<endl;
			return 0;
		}
	}

	cout<< -1 << endl;
 
	return 0;
}