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

	int n, m;
	cin>> n >> m;

	vector<int> a(m), v;
	rep(i, m) cin>> a[i];

	rep3(i, n+1, 1){
		int flag=1;
		rep(j, m){
			if(i==a[j]){
				flag=0;
				break;
			}
		}
		if(flag){
			cout<< i SP;
			repr(j, v.size()) cout<< v[j] SP;
			v.clear();
		}else{
			v.push_back(i);
		}
	}

	cout<< endl;
 
	return 0;
}