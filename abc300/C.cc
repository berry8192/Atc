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

	int h;
	cin>> h;
	int w;
	cin>> w;
	vector<string> a(h+1);
	rep(i, h){
		cin>> a[i];
		a[i]+='.';
	}
	a[h]="..............................................................................................................";
	vector<int> ans(min(h, w));

	rep(i, h){
		rep(j, w){
			if(a[i][j]=='#'){
				int lp=0;
				while(a[i+lp][j+lp]=='#'){
					a[i+lp][j+lp]='.';
					lp++;
				}
				lp/=2;
				if(lp) ans[lp-1]++;
			}
		}
	}
	PV(ans);
 
	return 0;
}