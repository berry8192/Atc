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

int main(){

	int n, k, ans=0;
	vector<int> v;

	cin>> n >> k;
	v.resize(n);

	rep(i, n) cin >> v[i];
	
	set<ll> st;
	priority_queue<
      ll,                // 要素の型はint
      std::vector<ll>,   // 内部コンテナはstd::vector (デフォルトのまま)
      std::greater<ll>   // 昇順 (デフォルトはstd::less<T>)
    > pq;
	st.insert(0);
	pq.push(0);

	rep(i, 2*k) {
		ll tmp=pq.top();
		// cout<< "tmp: " << tmp <<endl;
		pq.pop();
		rep(j, n){
			ll w=tmp+v[j];
			if(st.find(w)==st.end()){
				// cout<< "w: " << w <<endl;
				st.insert(w);
				pq.push(w);
			}
		}
	}
	auto itr=st.begin();
	rep(i, k){
		// cout<< *itr <<endl;
		itr++;
	}

	cout<< *itr << endl;
 
	return 0;
}