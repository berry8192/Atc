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

	int t;
	cin>> t;
	rep(lp, t){
		vector<int> a(3);
		cin>> a[0] >> a[1] >> a[2];
		sort(all(a));
		if(a[0]%2!=a[1]%2 || a[2]%2!=a[1]%2){
			cout<< -1 <<endl;
			continue;
		}
		int del1=a[2]-a[0]+a[2]-a[1];
		int del2=a[2]-a[0]+a[1]-a[0];
		int del=max(del1, del2);
		if(del%6){
			cout<< -1 <<endl;
			continue;
		}
		cout<< del/6 <<endl;
	}
 
	return 0;
}