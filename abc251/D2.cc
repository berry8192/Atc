#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

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

	ll w, lp=1;
	vector<int> v;

	cin>> w;

	rep(i, 2) v.push_back(i+1);
	rep(i, 298){
		vector<int> x(w+1);
		rep(j, v.size()){
			if(v[j]>w) continue;
			x[v[j]]=1;
			rep3(k, v.size(), j+1){
				if(v[j]+v[k]>w) continue;
				x[v[j]+v[k]]=1;
				rep3(l, v.size(), k+1){
					if(v[j]+v[k]+v[l]>w) continue;
					x[v[j]+v[k]+v[l]]=1;
				}
			}
		}
		// PV(x);
		int flag=1;
		rep3(j, w+1, 1){
			if(x[j]==0){
				v.push_back(j);
				flag=0;
				break;
			}
		}
		if(flag) break;
	}

	cout<< v.size() << endl;
	PV(v);
 
	return 0;
}