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

string tob(LLi n, int lng=0, string fil="0")
{
    string r, rtn="";
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "2" );
        n /= 2;
    }
	while(lng>r.size()) r+=fil;
    return r;
}

int main(){

	LLi n;
	string ans;

	cin>> n;

	ans=tob(n);
	reverse(all(ans));

	cout<< ans <<endl;
 
	return 0;
}