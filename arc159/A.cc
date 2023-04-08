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

template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int n, k, q;
	cin>> n >> k;
	vector<vector<ll>> dist(n, vector<ll>(n, imax));
	rep(i, n){
		rep(j, n){
			cin>> dist[i][j];
			if(dist[i][j]==0) dist[i][j]=imax;
		}
	}
	cin>> q;
	vector<ll> s(q), t(q);
	rep(i, q) cin>> s[i] >> t[i];

	for (int l = 0; l < n; l++){       // 経由する頂点
		for (int i = 0; i < n; i++) {    // 始点
			for (int j = 0; j < n; j++) {  // 終点
				dist[i][j] = min(dist[i][j], dist[i][l] + dist[l][j]);
			}
		}
	}

	// PVV(dist);

	rep(i, q){
		s[i]--;
		s[i]%=n;
		t[i]--;
		t[i]%=n;
		// cout<< s[i] SP << t[i] <<endl;
		if(dist[s[i]][t[i]]==imax) cout<< -1 <<endl;
		else cout<< dist[s[i]][t[i]] <<endl;
	}
 
	return 0;
}