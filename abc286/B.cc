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
	string s;
	cin>> s;
	string t;

	rep(i, a){
		if(i<a-1 && s[i]=='n' && s[i+1]=='a'){
			t+="nya";
			i++;
		}else{
			t+=s[i];
		}
	}
	cout<< t <<endl;
 
	return 0;
}