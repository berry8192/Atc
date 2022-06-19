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

vector<vector<int>> v;

template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int n, cnt=1, h, w, d=2;

	cin>> n;
	v.resize(n);
	rep(i, n) v[i].resize(n);

	for(int i=0;i<n;i+=2){
		for(int j=0;j<n;j+=2){
			v[i][j]=cnt;
			cnt++;
		}
		for(int j=1;j<n;j+=2){
			v[i][j]=cnt;
			cnt++;
		}
	}
	for(int i=1;i<n;i+=2){
		for(int j=0;j<n;j+=2){
			v[i][j]=cnt;
			cnt++;
		}
		for(int j=1;j<n;j+=2){
			v[i][j]=cnt;
			cnt++;
		}
	}

	PVV(v);
 
	return 0;
}