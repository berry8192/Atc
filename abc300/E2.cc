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
//using mint = modint1000000007;
using mint = modint998244353;

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

mint mpow(int x){
	mint rtn=1;
	rep3(i, x+1, 2) rtn*=i;
	return rtn;
}

int main(){

	ll n;
	mint ans=0;
	vector<int> v(7), p={2, 3, 5};

	cin>> n;

	rep(i, 3){
		while(n%p[i]==0){
			v[p[i]]++;
			n/=p[i];
		}
	}
	if(n!=1){
		cout<< 0 <<endl;
		return 0;
	}
	// PV(v);

	rep(i, 60){
		// i: 4の個数
		rep(j, 60){
			// j: 6の個数
			vector<int> w(7);
			w[2]=v[2]-i*2-j;
			w[4]=i;
			w[3]=v[3]-j;
			w[6]=j;
			w[5]=v[5];
			int flag=0;
			int su=0;
			rep3(k, 7, 2){
				if(w[k]<0) flag=1;
				su+=w[k];
			}
			if(flag) break;
			ans+=mpow(su)/mpow(w[2])/mpow(w[3])/mpow(w[4])/mpow(w[5])/mpow(w[6])/(mint(5).pow(su));
		}
	}

	cout<< ans.val() << endl;
 
	return 0;
}