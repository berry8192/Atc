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

int max_o_count(string s) {
    int max_count = 0, count = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'o') {
            count++;
            max_count = max(max_count, count);
        } else {
            count = 0;
        }
    }
    return max_count;
}

int main(){

	int n, ans=0;
	string s;

	cin>> n;
	cin>> s;

	ans=max_o_count(s);

	if(ans==n || ans==0) cout<< -1 << endl;
	else cout<< ans << endl;
 
	return 0;
}