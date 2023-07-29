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

	int a;
	cin>> a;
	int b;
	cin>> b;
	vector<string> s(a);
	rep(i, a) cin>> s[i];

	rep(i, a-8){
		rep(j, b-8){
			int flg=1;
			if(s[i].substr(j, 4)!="###.") flg=0;
			if(s[i+1].substr(j, 4)!="###.") flg=0;
			if(s[i+2].substr(j, 4)!="###.") flg=0;
			if(s[i+3].substr(j, 4)!="....") flg=0;
			if(s[i+5].substr(5+j, 4)!="....") flg=0;
			if(s[i+6].substr(5+j, 4)!=".###") flg=0;
			if(s[i+7].substr(5+j, 4)!=".###") flg=0;
			if(s[i+8].substr(5+j, 4)!=".###") flg=0;
			if(flg){
				cout<< i+1 SP << j+1 << endl;
			}
		}
	}

	cout<< endl;
 
	return 0;
}