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
	string ans;
	vector<int> v;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		//while(v[i].size()<7) v[i]+='!';
	}
	sort(all(v), greater<int>());
	
	ll ma=0;
	rep(j, 3){
		ans="";
		rep(i, 3){
			// while(1){
			// 	int sz=v[(i+j)%3].size();
			// 	if(v[(i+j)%3][sz-1]=='!') v[i].pop_back();
			// 	else break;
			// }
			ans+=to_string(v[(i+j)%3]);
		}
		ma=max(ma, stoll(ans));
	}
	rep(j, 3){
		ans="";
		repr(i, 3){
			// while(1){
			// 	int sz=v[(i-j+3)%3].size();
			// 	if(v[(i-j+3)%3][sz-1]=='!') v[i].pop_back();
			// 	else break;
			// }
			ans+=to_string(v[(i+j)%3]);
		}
		ma=max(ma, stoll(ans));
	}

	cout<< ma <<endl;
 
	return 0;
}