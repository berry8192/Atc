#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;
ll mod=1000000007;

int main(){

	int ma=0;
	string s;
	cin>> s;

	rep(i, s.size()){
		rep3(j, s.size(), i){
			string t;
			rep3(k, j+1, i) t+=s[k];
			int flg=1;
			rep(k, t.size()/2){
				if(t[k]!=t[t.size()-1-k]){
					flg=0;
					break;
				}
			}
			if(flg) ma=max(ma, j-i+1);
		}
	}
	cout<< ma <<endl;
 
	return 0;
}