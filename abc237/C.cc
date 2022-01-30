#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int n, l=0, r=0, sz, lp, flag=1;
	string s;

	cin>> s;
	sz=s.size();

	rep(i, sz){
		if(s[i]=='a') l++;
		else break;
	}
	repr(i, sz){
		if(s[i]=='a') r++;
		else break;
	}
	lp=(sz-l-r)/2;

	if(l>r){
		cout<< "No" <<endl;
		return 0;
	}

	rep(i, lp){
		//cout<< s[l+i] SP << s[sz-r-1-i] <<endl;
		if(s[l+i]!=s[sz-r-1-i]) flag=0;
	}

	//cout<< l SP << r <<endl;

	if(flag) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}