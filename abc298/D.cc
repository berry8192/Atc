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

int main(){

	int q, sz=1;
	mint ans=1;
	vector<mint> ten(600010);
	queue<int> que;
	que.push(1);

	cin>> q;
	ten[0]=1;
	rep3(i, q, 1) ten[i]=ten[i-1]*10;

	rep(lp, q) {
		int type;
		cin>> type;
		if(type==1){
			int x;
			cin>> x;
			que.push(x);
			ans*=10;
			ans+=x;
			sz++;
		}else if(type==2){
			mint tmp=que.front();
			que.pop();
			sz--;
			tmp*=ten[sz];
			ans-=tmp;
		}else{
			cout<< ans.val() <<endl;
		}
	}
 
	return 0;
}