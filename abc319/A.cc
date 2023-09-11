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

	map<string, int> mp;
	mp["tourist"]=3858;
	mp["ksun48"]=3679;
	mp["Benq"]=3658;
	mp["Um_nik"]=3648;
	mp["apiad"]=3638;
	mp["Stonefeang"]=3630;
	mp["ecnerwala"]=3613;
	mp["mnbvmar"]=3555;
	mp["newbiedmy"]=3516;
	mp["semiexp"]=3481;

	string s;
	cin>> s;
	cout<< mp[s] << endl;
 
	return 0;
}