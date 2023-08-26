#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
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

struct Prime{
	vector<int> eratos;
	vector<ll> prime_number; // i番目の素数が入る

	Prime(int sz, bool include1=true){
		// sz以下の素数をprime_numberに入れる
		eratos.resize(sz+1);
		for(int i=1;i<=sz;i++){
			for(int j=i;j<=sz;j+=i){
				eratos[j]++;
			}
		}

		if(include1) prime_number.push_back(1);
		rep(i, sz+1){
			if(eratos[i]==2){
				prime_number.push_back(i);
			}
		}
	}

	// 素因数分解
	map<ll, int> prime_factorization(ll x){
		map<ll, int> rtn;
		ll max_prime=prime_number[prime_number.size()-1];
		assert(x<=max_prime*max_prime);

		for(int i=1;prime_number[i]*prime_number[i]<=x;i++){
			while(x%prime_number[i]==0){
				x/=prime_number[i];
				rtn[prime_number[i]]++;
			}
			if(x==1) break;
		}
		if(x!=1) rtn[x]++;
		return rtn;
	}
	// 約数列挙
	vector<ll> map_divisor_enumeration(map<ll, int> mp){
		vector<ll> tmp={1}, ad;
		ll mul;
		
		for (auto p : mp) {
			mul=1;
			ad.clear();
			ll key = p.first;
			int value = p.second;
			
			rep(j, value){
				mul*=key;
				rep(k, tmp.size()) ad.push_back(tmp[k]*mul);
			}
			rep(j, ad.size()) tmp.push_back(ad[j]);
		}
		sort(all(tmp));
		return tmp;
	}
};

int main(){

	int n, k;
	vector<int> v;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];
	
	Prime prime(n+100);

	rep(i, n) {
		if (v[i]) ans++;
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}