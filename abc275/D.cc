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

// vector<ll> mem(100010);
map<ll, ll> mp;

void ff(ll k){
	// if(k<100000 && mem[k]!=0) return mem[k];
	// return ff(k/2)+ff(k/3);
	ll tmp=mp[k];
	mp.erase(k);
	mp[k/2]+=tmp;
	mp[k/3]+=tmp;
}

int main(){

	ll n;
	cin>> n;
	if(n==0){
		cout<< 1 <<endl;
		return 0;
	}
	
	// mem[0]=1;
	// rep3(i, 100010, 1) mem[i]=ff(i);

	// rep(i, 20) cout<< mem[i] <<endl;
	// cout<< mem[100000] <<endl;

	mp[n]=1;
	ff(n);
	while(1){
		auto itr=mp.rbegin();
		// cout<< itr->first SP << itr->second <<endl;
		if(itr->first==0){
			cout<< itr->second <<endl;
			return 0;
		}
		ff(itr->first);
	}

	// cout<< ff(n) <<endl;
 
	return 0;
}