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

mint dfs(vector<int> ss){
	// cout<< ss.size() << " ";
	// PV(ss);
	int one=0;
	rep(i, ss.size()){
		if(ss[i]) one++;
	}
	mint rtn=mint(2).pow(one);
	// cout<< "rtn: " << rtn.val() <<endl;
	// int flag=1;
	for(int i=2;i<ss.size();i++){
		if(ss.size()%i==0){
			vector<int> w(i, 1);
			rep(j, ss.size()){
				if(ss[j]==0) w[j%i]=0;
			}
			rtn-=dfs(w);
			// cout<< "-rtn: " << rtn.val() <<endl;
		}
	}
	return rtn-1;
}

int main(){

	int n;
	string s;
	cin>> n;
	cin>> s;
	mint ans=0;

	int flag=1;
	rep(i, n){
		if(s[i]=='.'){
			flag=0;
			break;
		}
	}
	if(flag){
		rep3(i, n, 2){
			if(n%i==0){
				flag=0;
				break;
			}
		}
	}
	if(flag){
		cout<< 2 <<endl;
		return 0;
	}

	rep3(i, n, 2) {
		if(n%i==0){
			vector<int> v(i, 1);
			rep(j, n){
				if(s[j]=='.') v[j%i]=0;
			}
			ans+=dfs(v);
		}
	}

	cout<< ans.val()+1 << endl;
 
	return 0;
}