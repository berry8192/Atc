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

	string s;
	int lv=0;
	vector<vector<int>> v(26, vector<int>());

	cin>> s;

	rep(i, s.size()) {
		if(s[i]=='('){
			lv++;
		}else if(s[i]==')'){
			rep(j, 26){
				int idx=v[j].size()-1;
				if(v[j].size()==0) continue;
				if(v[j][idx]==lv){
					v[j].pop_back();
				}
			}
			lv--;
		}else{
			int tmp=int(s[i]-'a');
			if(v[tmp].size()!=0){
				cout<< "No" <<endl;
				return 0;
			}
			v[tmp].push_back(lv);
		}
	}

	cout<< "Yes" << endl;
 
	return 0;
}