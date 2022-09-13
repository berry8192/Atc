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

class Prime {
// n以下の素数を列挙する
public:
  const int n;
  vector<bool> is_prime;
  vector<int> primes;
  Prime(int size) : n(size), is_prime(n+1, true) {
    is_prime[0] = false;
    is_prime[1] = false;
    for (int i = 2; i <= n; ++i) {
      if (!is_prime[i]) continue;
      primes.push_back(i);
      int tmp = 2*i;
      while (tmp <= n) {
        is_prime[tmp] = false;
        tmp += i;
      }
    }
  }

  bool check(int x) { return is_prime[x]; }
};

int main(){

	int n, ans=0;
	vector<int> v;

	cin>> n;
	v.resize(n);

	Prime p(32000);

	rep(i, n) cin >> v[i];

	rep3(i, 32000, 2) {
		//if (p.is_prime[i]){
			//cout<< i <<endl;
			int flag=1;
			int pre=-1;
			rep(j, n){
				if(pre!=-1 && v[j]%i!=pre){
					flag=0;
					break;
				}
				pre=v[j]%i;
			}
			if(flag){
				cout<< 1 <<endl;
				return 0;
			}
		//}
	}

	cout<< 2 << endl;
 
	return 0;
}