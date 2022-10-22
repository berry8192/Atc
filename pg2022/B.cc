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

	ll w, h, t, sx, sy, tx, ty, ans=0;
	cin>> w >> h >> t;
	cin>> sx >> sy;
	cin>> tx >> ty;
	vector<ll> rx, ry;
	set<ll> st;
	for(ll i=0;i<=t;i++) st.insert(i*i);

	rx.push_back(sx-t);
	ry.push_back(sy);
	for(ll i=-t+1;i<=t-1;i++){
		ll tmp=t*t-i*i;
		ll sq=sqrt(tmp);
		// cout<< sq <<endl;
		if(st.find(tmp)!=st.end()){
			rx.push_back(sx+i);
			ry.push_back(sy+sq);
			rx.push_back(sx+i);
			ry.push_back(sy-sq);
		}
	}
	rx.push_back(sx+t);
	ry.push_back(sy);

	// rep(i, rx.size()) cout<< rx[i] SP << ry[i] <<endl;
	rep(i, rx.size()){
		// cout<< rx[i] SP << ry[i] SP;
		// cout<< rx[i]*rx[i] SP << ry[i]*ry[i] <<endl;
		rx[i]=((rx[i]%(2*w))+2*w)%(2*w);
		ry[i]=((ry[i]%(2*h))+2*h)%(2*h);
		ll x=(rx[i]/w)%2;
		ll y=(ry[i]/h)%2;
		// cout<< x SP << y SP;
		// cout<< rx[i] SP << ry[i] <<endl;
		if(x==0){
			if(rx[i]%w!=tx) continue;
		}else{
			if(rx[i]%w!=w-tx) continue;
		}
		if(y==0){
			if(ry[i]%h!=ty) continue;
		}else{
			if(ry[i]%h!=h-ty) continue;
		}
		// cout<< "OK" <<endl;
		ans++;
	}

	cout<< ans <<endl;
 
	return 0;
}