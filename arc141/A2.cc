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
ll lmax=9223372036854775807;

int main(){

	int t;
	cin>> t;

	rep(i, t){
		ll n;
		cin>> n;
		ll ma=11;
		string s=to_string(n);
	
		string nine;
		rep(i, s.size()-1) nine+="9";
		ma=max(ma, stoll(nine));
	
		rep3(j, s.size(), 1){
			if(s.size()%j!=0) continue;
			string tmp;
			rep(l, s.size()/j){
				rep(k, j-1) tmp+='0';
				tmp+='1';
			}
			//cout<< "tmp=" << tmp <<endl;
			ll di=stoll(tmp);
			ma=max(ma, (n/di)*di);
		}
		
		cout<< ma <<endl;
	}
 
	return 0;
}