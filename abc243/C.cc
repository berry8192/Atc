#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

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

	int n, ans=0;
	vector<int> x, y;
	string s;
	map<int, int> l, r;

	cin>> n;
	x.resize(n);
	y.resize(n);

	rep(i, n){
		cin >> x[i] >> y[i];
		//x[i]+=10;
	}
	cin>> s;

	rep(i, n) {
		if(s[i]=='L'){
			l[y[i]]=max(l[y[i]], x[i]);
		}else{
			if(r.find(y[i])!=r.end()){
				r[y[i]]=min(r[y[i]], x[i]);
			}else{
				r[y[i]]=x[i];
			}
		}
	}

	// cout<< "L" <<endl;
	// for (auto p : l) {
  	// 	auto key = p.first;
  	// 	auto val = p.second;
	// 	cout<< key << " " << val <<endl;
	// }
	// cout<< "R" <<endl;
	// for (auto p : r) {
  	// 	auto key = p.first;
  	// 	auto val = p.second;
	// 	cout<< key << " " << val <<endl;
	// }

	for (auto p : l) {
  		auto key = p.first;
  		auto val = p.second;
  		// key, valを使う
		if(r.find(key)!=r.end() && val>r[key]){
			cout<< "Yes" <<endl;
			return 0;
		}
	}

	cout<< "No" << endl;
 
	return 0;
}