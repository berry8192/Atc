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

	ll n, m, msiz=0, mc=0;
	cin>> n >> m;
	string ans;
	vector<ll> mo;

	for(ll i=1;i<10;i++){
		mo.clear();
		mo.resize(n+1);
		rep3(j, n+1, 1){
			mo[j]=mo[j-1]*10+i;
			mo[j]%=m;
			if(mo[j]==0){
				int sz=j;
				int siz=n/sz*sz;
				if(msiz<=siz){
					msiz=siz;
					mc=i;
				}
			}
		}
	}

	if(mc==0){
		cout<< -1 <<endl;
		return 0;
	}

	string c=to_string(mc);
	rep(i, msiz) ans+=c;

	cout<< ans <<endl;
 
	return 0;
}