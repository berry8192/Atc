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

	int n, tmp, ans=0, pool, pos=0;
	vector<int> v;
	set<int> st;

	cin>> n;

	rep(i, n){
		cin >> tmp;
		if(st.find(tmp)==st.end()) v.push_back(tmp);
		st.insert(tmp);
	}
	sort(all(v));
	// PV(v);
	pool=n-st.size();
	// cout<< pool SP << st.size() <<endl;

	rep3(i, n+1, 1){
		// cout<< pos SP << i SP << v.size() SP << pool <<endl;
		if (v[pos]==i){
			ans++;
			pos++;
		}else{
			if(pool+v.size()-pos>=2){
				ans++;
				rep(j, 2-pool) v.pop_back();
				pool=max(0, pool-2);
				if(pos>=pool+v.size()-1) break;
			}else break;
		}
	}

	cout<< ans << endl;
 
	return 0;
}