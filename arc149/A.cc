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

	ll n, m, k=-1, sz, siz, msiz=0, mc=0;
	cin>> n >> m;
	string ans;

	rep3(i, 1000011, 1){
		ll tmp=m*i;
		sz=to_string(tmp).size();
		if(sz>n) break;
		ll one=0;
		rep(j, sz) one=one*10+1;
		// cout<< tmp SP << one <<endl;
		if(tmp%one==0){
			k=tmp;
			siz=sz;
			siz=n/siz*siz;
			// cout<< k SP << siz <<endl;
			k=k%10;
			if(k==2 || k==4) k=8;
			if(k==1 || k==3) k=9;

			if(msiz<siz){
				msiz=siz;
				mc=k;
			}else if(msiz==siz && mc<k){
				msiz=siz;
				mc=k;
			}
		}
	}

	if(k==-1){
		cout<< k <<endl;
		return 0;
	}

	string c=to_string(mc);
	rep(i, msiz) ans+=c;

	cout<< ans <<endl;
 
	return 0;
}