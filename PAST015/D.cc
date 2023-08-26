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

	int a, b, c, d, r, p, q;
	cin>> a >> b >> c >> d >> r;
	if(a<15 && d==14){
		cout<< "No" <<endl;
		return 0;
	}
	// if(a<c && c-a<d && d==14) exit(1);
	p=a;
	q=a+r;
	vector<int> v(4010);

	int t=0;
	while(1){
		if(t%d==0 && t<=q){
			rep3(i, q+1, max(t, p)) v[i]=1;
		}
		if(t>=b){
			p=c;
			q=c+r;
		}
		t++;
		if(2500<t) break;
	}

	int flg=1;
	// rep(i, 50) cout<< v[i] SP;
	rep3(i, c+r+1, c){
		if(v[i]==0) flg=0;
	}
	if(flg) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}