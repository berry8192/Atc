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

int n, m, ans=0;
string tmp;
vector<int> w;
vector<string> s;
set<string> t;

void dfs(vector<int> x){
	string ss;
	rep(i, n-1){
		ss+=s[w[i]]+"_";
		rep(j, x[i]) ss+="_";
	}
	ss+=s[w[n-1]];
	if(ss.size()>16) return;
	if(ss.size()>=3 && t.find(ss)==t.end()){
		cout<< ss <<endl;
		exit(0);
	}
	if(ss.size()==16) return;
	rep(i, n-1){
		vector<int> y=x;
		y[i]++;
		dfs(y);
	}
}

int main(){

	cin>> n >> m;
	s.resize(n);

	rep(i, n) cin >> s[i];
	rep(i, m){
		cin >> tmp;
		t.insert(tmp);
	}
	rep(i, n) w.push_back(i);
	vector<int> z(n);

	do {
		//PV(w);
		dfs(z);
	} while (next_permutation(all(w)));

	cout<< -1 << endl;
 
	return 0;
}