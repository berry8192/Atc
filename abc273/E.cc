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

	int q;
	vector<string> s;
	vector<int> x, a;
	map<int, vector<int>> v;
	map<int, int> ref;

	cin>> q;
	s.resize(q);
	x.resize(q, -1);

	rep(i, q){
		cin >> s[i];
		if(s[i]!="DELETE" ) cin >> x[i];
	}
	s.push_back("DELETE");

	// rep(i, q) cout<< s[i] SP << x[i] <<endl;

	int del=0, pos=-1, ma=0;
	rep(i, q+1){
		if(s[i]=="ADD"){
			del--;
		}else if(s[i]=="DELETE"){
			del++;
			ma=(ma, del);
		}else if(s[i]=="SAVE"){
		}else if(s[i]=="LOAD"){
			if(pos!=-1) ref[pos]=ma;
			if(i==q) break;
			ma=0;
			pos=x[i];
			del=0;
		}else{
			assert(0);
		}
	}

	// for (auto p : ref) {
  	// 	auto key = p.first;
  	// 	auto val = p.second;
  	// 	// key, valを使う
	// 	cout<< key << " " << val <<endl;
	// }

	rep(i, q){
		if(s[i]=="ADD"){
			a.push_back(x[i]);
		}else if(s[i]=="DELETE"){
			// cout<< "delete" <<endl;
			if(a.size()) a.pop_back();
			// cout<< "deleted" <<endl;
		}else if(s[i]=="SAVE"){
			v[x[i]].clear();
			int sz=min(min(100, ref[x[i]]+1), int(a.size()));
			repr(j, sz){
				v[x[i]].push_back(a[a.size()-1-j]);
			}
			reverse(all(v[x[i]]));
			// PV(v[x[i]]);
		}else if(s[i]=="LOAD"){
			a.clear();
			rep(j, v[x[i]].size()) a.push_back(v[x[i]][j]);
		}else{
			assert(0);
		}
		if(a.size()) cout<< a[a.size()-1] SP;
		else cout<< -1 SP;
		// if(a.size()) PV(a);
		// else cout<< endl;
	}
	cout<< endl;
 
	return 0;
}