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

	int t;
	cin>> t;
	rep(lp, t){
		int n;
		cin>> n;
		string s;
		cin>> s;

		if(n==4){
			if(s[0]==s[2] && s[1]==s[3] && s[0]>s[1]){
				cout<< "No" <<endl;
				continue;
			}
		}

		string tmp;
		int flg=1;
		rep(i, n){
			tmp+=s[i];
			rep(j, n){
				// cout<< i SP << j << endl;
				if(tmp[j]<s[i+1+j]){
					flg=0;
					cout<< "Yes" <<endl;
					i=n;
					break;
				}else if(tmp[j]>s[i+1+j]){
					break;
				}
				if(j==i && i+1<n/2){
					flg=0;
					cout<< "Yes" <<endl;
					i=n;
					break;
				}
			}
		}
		if(flg) cout<< "No" <<endl;
	}
 
	return 0;
}