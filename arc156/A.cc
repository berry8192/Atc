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

		int ans=0;
		int cnt=0;
		rep(i, n){
			if(s[i]=='1') cnt++;
		}
		if(cnt%2){
			cout<< -1 <<endl;
			continue;
		}
		if(s=="110" || s=="011"){
			cout<< -1 <<endl;
			continue;
		}
		if(s=="0110"){
			cout<< 3 <<endl;
			continue;
		}
		if(cnt==2){
			rep(i, n-1){
				if(s[i]=='1' && s[i+1]=='1'){
					ans=1;
					break;
				}
			}
		}
		cout<< cnt/2+ans <<endl;
	}
 
	return 0;
}