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

	int n, m, tmp;
	vector<vector<int>> v;
	vector<set<int>> st;

	cin>> n >> m;
	v.resize(n, vector<int>(2));
	st.resize(n);

	rep(i, n){
		cin>> v[i][0] >> v[i][1];
		rep(j, v[i][1]){
			cin>> tmp;
			st[i].insert(tmp);
		}
	}

	rep(i, n) {
		rep(j, n){
			if(v[i][0]<v[j][0]) continue;
			int flg=0;
			for(auto s : st[i]){
				if(st[j].find(s)==st[j].end()){
					flg=1;
					break;
				}
			}
			if(flg) continue;
			if(v[i][0]>v[j][0] || st[i].size()<st[j].size()){
				// cout<< i SP << j <<endl;
				cout<< "Yes" <<endl;
				return 0;
			}
		}
	}

	cout<< "No" << endl;
 
	return 0;
}