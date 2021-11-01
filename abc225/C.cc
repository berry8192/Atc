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

	int n, m, ans=0;
	vector< vector<int> > v;

	cin>> n >> m;
	v.resize(n);
	rep(i, n) v[i].resize(m);

	rep(i, n){
		rep(j, m){
			cin >> v[i][j];
		}
	}

	rep(i, n){
		rep(j, m-1){
			if(v[i][j]!=v[i][j+1]-1 || v[i][j]%7==0){
				cout<< "No" << endl;
				return 0;
			}
		}
	}

	rep(i, m){
		rep(j, n-1){
			if(v[j][i]!=v[j+1][i]-7){
				cout<< "No" << endl;
				return 0;
			}
		}
	}

	cout<< "Yes" << endl;
 
	return 0;
}