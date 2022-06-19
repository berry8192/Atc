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

	ll n, kr, k, ans=0;
	string s;
	cin>> n >> k;
	s=to_string(k);
	reverse(all(s));
	kr=stoll(s);

	if(k%10==0 || k>kr){
		// if(k<=n){
		// 	cout<< 1 << endl;
		// }else{
		// 	cout<< 0 <<endl;
		// }
		cout<< 0 <<endl;
		return 0;
	}

	if(k!=kr){
		while(k<=n){
			k*=10;
			ans++;
		}
	}
	while(kr<=n){
		kr*=10;
		ans++;
	}

	cout<< ans <<endl;
 
	return 0;
}