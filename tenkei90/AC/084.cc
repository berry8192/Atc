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
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
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

	LLi n, ans, str;
	string s;

	cin>> n;
	cin>> s;
	s+="1";
	ans=n*(n-1)/2;

	str=1;
	rep(i, n){
		if(s[i]==s[i+1]){
			str++;
		}else{
			ans-=str*(str-1)/2;
			str=1;
		}
		//cout<< str SP << ans << endl;
	}

	cout<< ans << endl;
 
	return 0;
}