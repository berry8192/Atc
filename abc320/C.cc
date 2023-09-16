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

	int m, ans=imax;
	vector<string> s(3);

	cin>> m;

	rep(i, 3){
		cin >> s[i];
		s[i]=s[i]+s[i]+s[i];
	}
	
	// cout<< s[0] <<endl;
	// cout<< s[1] <<endl;
	// cout<< s[2] <<endl;
	vector<int> perm={0, 1, 2};

	do {
		// PV(perm);
		rep(i, 10){
			int ma=0;
			set<int> st;
			rep(j, 3) {
				rep(k, 3*m){
					if(st.find(k)!=st.end()) continue;
					if(i==int(s[perm[j]][k]-'0')){
						ma=max(ma, k);
						st.insert(k);
						break;
					}
					if(k==3*m-1) ma=imax;
				}
			}
			ans=min(ans, ma);
			// cout<< i SP << ans <<endl;
		}
		// break;
	} while (next_permutation(all(perm)));
	
	if(ans==imax) cout<< -1 << endl;
	else cout<< ans << endl;
 
	return 0;
}