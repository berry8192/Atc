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

	int n;
	cin>> n;
	string s;
	cin>> s;
	string t;
	cin>> t;
	vector<int> ss(26), tt(26);

	rep(i, n){
		ss[s[i]-'a']++;
		tt[t[i]-'a']++;
	}
	rep(i, 26){
		if(ss[i]!=tt[i]){
			cout<< -1 <<endl;
			return 0;
		}
	}
	reverse(all(s));
	reverse(all(t));

	int pos=0, flag;
	rep(i, n){
		while(pos<n){
			flag=0;
			// cout<< s[i] SP << t[pos] <<endl;
			if(s[i]==t[pos]){
				pos++;
				break;
			}else{
				flag=1;
				pos++;
			}
		}
		if(pos==n){
			// cout<< i <<endl;
			cout<< n-i-1+flag <<endl;
			return 0;
		}
	}
 
	return 0;
}