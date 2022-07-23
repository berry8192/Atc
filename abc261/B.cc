#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

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

	int n, flag=1;
	vector<vector<int>> v;

	cin>> n;
	v.resize(n);
	rep(i, n) v[i].resize(n);

	rep(i, n){
		rep(j, n){
			char tmp;
			cin>> tmp;
			if(tmp=='W') v[i][j]=3;
			if(tmp=='D') v[i][j]=2;
			if(tmp=='L') v[i][j]=1;
		}
	}

	rep(i, n){
		rep3(j, n, i+1){
			if(v[i][j]+v[j][i]!=4){
				flag=0;
				break;
			}
		}
	}

	if(flag) cout<< "correct" << endl;
	else cout<< "incorrect" << endl;
 
	return 0;
}