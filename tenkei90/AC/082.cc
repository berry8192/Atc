#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	long long l, r, ans=0, tmp, tl, tr, ad;

	cin>> l >> r;
	
	if(r==1000000000000000000){
		ans+=(r%mod)*19;
		ans%=mod;
	}
	
	for(long long i=1;i<=100000000000000000;i*=10){
		tr=min(i*10-1, r);
		tl=max(i, l);
		if(tl>tr) continue;
		tr%=mod;
		tl%=mod;
		//tr=min(i*10-1, r)%mod;
		//cout<< tl << " " << tr <<endl;
		ad=tr*(tr+1);
		ad%=mod;
		ad*=(mod+1)/2;
		ad%=mod;
		tmp=tl*(tl-1);
		tmp%=mod;
		tmp*=(mod+1)/2;
		tmp%=mod;
		//cout<< ad << " " << tmp <<endl;
		ad=ad-tmp+2*mod;
		ad%=mod;
		ad*=to_string(i).size();
		ad%=mod;
		ans+=ad;
		ans%=mod;
		//cout<< ans <<endl;
	}
	
	cout<< ans <<endl;
 
	return 0;
}
