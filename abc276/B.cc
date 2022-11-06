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

template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

int main(){

	int n;
	cin>> n;
	int m;
	cin>> m;
	int a, b;
	vector<vector<int>> v(n);

	rep(i, m){
		cin>> a >> b;
		a--;
		b--;
		v[a].push_back(b+1);
		v[b].push_back(a+1);
	}

	rep(i, n){
		sort(all(v[i]));
		cout<< v[i].size() SP;
		PV(v[i]);
	}
 
	return 0;
}