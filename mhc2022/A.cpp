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

	int t, n, k;
	cin>> t;

	rep(lp, t){
		cin>> n >> k;
		vector<int> v(n);
		vector<int> w(110);
		int flag=1;

		rep(i, n){
			cin >> v[i];
			w[v[i]]++;
		}

		if(k*2<n) flag=0;

		rep(i, 110){
			//cout<< w[i] <<endl;
			if(w[i]>2){
				flag=0;
				break;
			}
		}

		if(flag) cout<< "Case #" << lp+1 << ": " << "YES" << endl;
		else cout<< "Case #" << lp+1 << ": " << "NO" << endl;
	}
 
	return 0;
}