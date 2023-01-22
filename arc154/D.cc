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

int n;

bool ask(int x, int y){
	cout<< "? " << x SP << x SP << y <<endl;
	string s;
	cin>> s;
	if(s=="-1") exit(1);
	return s[0]=='Y';
}

vector<int> dfs(vector<int> v, int l, int r){
	int hal;
	rep3(i, r+1, l) {
		if(!ask(i, i+1)){
			hal=i;
			break;
		}else{
			if(!ask(i+1, i)){
				hal=i+1;
				break;
			}
		}
	}
	rep()
	vector<int> le, ri;
	le.push_back(hal);
	rep(i, ri.size()) le.push_back(ri[i]);
	return le;
}

int main(){

	cin>> n;

	vector<int> tmp;
	rep(i, n) tmp.push_back(i+1);

	vector<int> ans=dfs(tmp, 1, n);

	cout<< "! ";
	PV(ans);
 
	return 0;
}