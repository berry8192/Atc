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

	int n, m, ans=-1;
	string s, t;
	vector<int> ss(26), tt(26);
	cin>> n >> m;
	cin>> s;
	cin>> t;

	rep(i, n){
		ss[int(s[i]-'A')]++;
	}
	rep(i, m){
		tt[int(t[i]-'A')]++;
	}

	rep(i, 26){
		if(ss[i] && !tt[i]){
			cout<< -1 <<endl;
			return 0;
		}else{
			if(ss[i]) ans=max(ans, (ss[i]+tt[i]-1)/tt[i]);
		}
	}

	cout<< ans <<endl;
 
	return 0;
}