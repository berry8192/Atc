#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
LLi llimax=9223372036854775807;
LLi mod=1000000007;

int main(){

	int n, k, ans;
	cin>> n >> k;
	string s;
	cin>> s;

	rep3(i, n+1, 1){
		if(n%i) continue;
		vector<vector<char>> t(n);
		rep(j, n){
			t[j%i].push_back(s[j]);
		}
		int cnt=0;
		rep(j, i){
			vector<int> d(26);
			rep(l, t[j].size()){
				d[int(t[j][l]-'a')]++;
			}
			int ma=0;
			rep(l, 26){
				ma=max(ma, d[l]);
			}
			cnt+=t[j].size()-ma;
		}
		if(cnt<=k){
			cout<< i <<endl;
			return 0;
		}
	}
 
	return 0;
}