#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
using mint = modint998244353;

int main() {
    ll n;
    cin >> n;

    map<ll, ll> freq; // xの取りうる値と出現回数を管理するmap
    freq[1] = 1; // 初期値の1を設定

	while(1){
		auto it = freq.begin(); // 最小のキーを指すイテレータを取得
		int min_key = it->first; // 最小のキーを取得
		int min_value = it->second; // 最小のvalueを取得
		cout << "min key: " << min_key << ", min value: " << min_value << endl;
		if(min_key==n){
			cout<< min_value <<endl;
			return 0;
		}else if(min_key>n){
			cout<< 0 <<endl;
			return 0;
		}
		rep3(i, 7, 2){
			int new_key=min_key*i;
			freq[new_key]+=min_value;
		}

		freq.erase(it); // 最小のキーを削除
	}

    return 0;
}
