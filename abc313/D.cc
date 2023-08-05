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

int askj(vector<int> vv){
	cout<< "? ";
	rep(i, vv.size()){
		if(vv[i]) cout<< i+1 SP;
	}
	cout<< endl;
	int tmp;
	cin>> tmp;
	return tmp;
}

int main(){

	int n, k;
	cin>> n >> k;
	vector<int> v(n), ans(n), rtn(n);
	vector<vector<int>> g(n);

	if(k==1){
		rep(i, n){
			cout<< "? " << i+1 <<endl;
			cin>> ans[i];
		}
		cout<< "! ";
		PV(ans);
		return 0;
	}

	rep(i, n-k+1){
		vector<int> ask(n);
		rep(j, k-1) ask[j]=1;
		ask[n-1-i]=1;
		rtn[i]=askj(ask);
	}
	rep(i, k-1){
		int x=k-1-i;
		vector<int> ask(n);
		rep(j, k-1) ask[j]=1;
		ask[x]=0;
		rtn[x]=askj(ask);
	}
	PV(rtn);
	cout<< "No" << endl;
 
	return 0;
}