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
			// j文字のかたまりをつくる
			ll blo=lmax;
			string dwn;
			dwn+=s[0]-1;
			rep(l, j-1) dwn+="9";
			ll tmp=stoll(dwn);
			blo=min(blo, tmp);
			// if(stoll(s.substr(0, j))!=blo){
			// 	if(to_string(blo).size()!=to_string(blo-1).size()) continue;
			// 	else blo=stoll(s.substr(0, j))-1;
			// }
			string str;
			rep(k, s.size()/j) str+=to_string(blo);
			//cout<< "j=" << j SP << stoll(str) <<endl;
			ma=max(ma, stoll(str));
		}
	
		rep3(j, s.size(), 1){
			if(s.size()%j!=0) continue;
			// j文字のかたまりをつくる
			ll blo=lmax;
			for(int k=0;k<s.size();k+=j){
				// 始点の位置
				ll tmp=stoll(s.substr(k, j));
				//if(j==6) cout<< tmp <<endl;
				blo=min(blo, tmp);
			}
			if(stoll(s.substr(0, j))!=blo){
				if(to_string(blo).size()!=to_string(blo-1).size()) continue;
				else blo=stoll(s.substr(0, j))-1;
			}
			string str;
			rep(k, s.size()/j) str+=to_string(blo);
			//cout<< "j=" << j SP << stoll(str) <<endl;
			ma=max(ma, stoll(str));
		}
		cout<< ma <<endl;
	}
 
	return 0;
}