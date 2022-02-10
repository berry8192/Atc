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

	int n, ans=0, flag;
	string s, t, c="RGB";
	vector< vector<char> > v;

	// char p;
	// cin>> p;
	// cout<< int(p) <<endl;
	// return 0;

	cin>> n >> s >> t;
	v.resize(n);
	rep(i, n) v[i].resize(n);

	rep(i, n) {
		rep(j, n){
			if(s[i]==t[j]) v[i][j]=s[i];
			else v[i][j]=c[2-int(s[i]+t[j])%3];
		}
	}
	//PVV(v);
	rep(i, n){
		flag=1;
		rep(j, n-i-1){
			//cout<< j << " " << j+i <<endl;
			if(v[j][j+i]!=v[j+1][j+i+1]){
				flag=0;
				//cout<< "break" <<endl;
				break;
			}
		}
		ans+=flag;
		if(i==0) continue;
		flag=1;
		rep(j, n-i-1){
			if(v[j+i][j]!=v[j+i+1][j+1]){
				flag=0;
				break;
			}
		}
		ans+=flag;
	}

	cout<< ans << endl;
 
	return 0;
}