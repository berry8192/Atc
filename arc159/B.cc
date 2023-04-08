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

vector<ll> ff(ll x){
	int fsz;
	vector<ll> f;
	for(ll i=1;i*i<x;i++){
		if(x%i==0) f.push_back(i);
	}
	fsz=f.size();
	if((int)sqrt(x)*(int)sqrt(x)==x) f.push_back((int)sqrt(x));//平方根が約数の場合
	rep(i, fsz) f.push_back(x/f[fsz-1-i]);
	return f;
}

ll exact(ll a, ll b){
	ll ans=0;
	while(a && b){
		ll c=__gcd(a, b);
		a-=c;
		b-=c;
		ans++;
		// cout<< a SP << b <<endl;
	}
	return ans;
}

int main(){

	ll a, b, ans=0;
	ll A, B;
	cin>> a >> b;
	A=a;
	B=b;
	// cout<< a-b << endl;
	if(a<b) swap(a, b);
	vector<ll> tmp=ff(a-b);
	// PV(tmp);
	while(a && b){
		// cout<< "###" << __gcd(a, b) <<endl;
		// rep(i, tmp.size()) cout<< tmp[i] SP << a%tmp[i] SP << b%tmp[i] << "###" <<endl;

		ll c=__gcd(a, b);
		if(b==c){
			ans++;
			break;
		}
		ll minturn=llimax, stp;
		// cout<< "###" << __gcd(a, b) <<endl;
		rep(i, tmp.size()){
			// cout<< a%tmp[i] <<endl;
			if((a%tmp[i])/c>0 && (a%tmp[i])%c==0 && minturn>=(a%tmp[i])/c){
				minturn=(a%tmp[i])/c;
				stp=a%tmp[i]/c;
			}
		}
		if(minturn==llimax){
			ans+=b/c;
			break;
		}
		// cout<< minturn <<endl;
		ans+=minturn;
		a-=c*minturn;
		b-=c*minturn;
		// cout<< "gcd: " << c <<endl;
		// cout<< a SP << b <<endl;
	}
	// assert(ans==exact(A, B));

	cout<< ans << endl;
 
	return 0;
}