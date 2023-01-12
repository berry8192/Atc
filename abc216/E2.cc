#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

// 初項 a，公差 d，項数 n 
ll tousa(ll a, ll d, ll n){
	return (n*(2*a+(n-1)*d))/2;
}

int main(){

	int n, k;
	ll ans=0;
	vector<ll> v;

	cin>> n >> k;
	v.resize(n);

	rep(i, n) cin >> v[i];
	sort(all(v), greater<ll>());
	v.push_back(0);

	rep(i, n) {
		ll fig=min(k, i+1);
		if(k<=i+1){
			ans+=k*v[i];
			break;
		}else{
			if(k<(v[i]-v[i+1])*fig){
				ans+=tousa(v[i], -1, k/fig)*fig;
				ans+=(v[i]-k/fig)*(k%fig);
				break;
			}else{
				ans+=tousa(v[i], -1, v[i]-v[i+1])*fig;
				k-=(v[i]-v[i+1])*fig;
			}
		}
		// cout<< ans <<endl;
	}

	cout<< ans << endl;
 
	return 0;
}