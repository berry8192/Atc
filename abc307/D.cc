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

	int n;
	string s;
	vector<int> op, d;

	cin>> n;
	d.resize(n);
	cin>> s;

	rep(i, n) {
		if(s[i]=='('){
			op.push_back(i);
		}else if(s[i]==')' && op.size()){
			// dl.push_back(op[op.size()-1]);
			// dr.push_back(i);
			rep3(j, i+1, op[op.size()-1]){
				s[j]='.';
				if(d[j]) j=d[j];
			}
			d[op[op.size()-1]]=i;
			op.pop_back();
			// cout<< s <<endl;
		}
	}

	rep(i, n){
		if(s[i]!='.') cout<< s[i];
	}
	cout<<endl;
 
	return 0;
}