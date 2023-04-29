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

	int h;
	cin>> h;
	int w;
	cin>> w;
	vector<string> a(h), b(h);

	rep(i, h) cin>> a[i];
	rep(i, h) cin>> b[i];

	rep(i, h){
		rep(j, w){
			if(a==b){
				cout<< "Yes" <<endl;
				return 0;
			}
			rep(k, h){
				rep(l, w-1){
					swap(a[k][l], a[k][l+1]);
				}
			}
		}
		rep(k, h-1){
			swap(a[k], a[k+1]);
		}
	}

	cout<< "No" <<endl;
 
	return 0;
}