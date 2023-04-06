#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

template <class T> void PM(T pm) {
    // cout<< "{";
	for(auto m : pm){
		cout<< "(" << m.first << "->" << m.second << "), ";
	}
	// cout<< "}";
	cout<<endl;
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
};

int main(){

	int n, m;
	cin>> n >> m;

	Prime prime(n);

	cout<< "eratos" <<endl;
	PV(prime.eratos);
	cout<< "prime_number" <<endl;
	PV(prime.prime_number);
	cout<< "prime_factorization: " << m << endl;
	PM(prime.prime_factorization(m));

	return 0;
}

//0と1のコーナーケースに気をつける