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

	int n, t, x, c;
	multiset<int> st;

	cin>> n;

	rep(i, n) {
		cin>> t;
		if(t==1){
			cin>> x;
			st.insert(x);
		}else if(t==2){
			cin>> x >> c;
			rep(j, c){
				auto itr=st.find(x);
				if(itr!=st.end()){
					st.erase(itr);
				}else{
					break;
				}
			}
		}else{
			auto itr1=st.rbegin();
			auto itr2=st.begin();
			cout<< *itr1-*itr2 <<endl;
		}
	}
 
	return 0;
}