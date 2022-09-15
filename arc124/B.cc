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
	vector<int> a, b;
	multiset<int> bst;
	set<int> ans;

	cin>> n;
	a.resize(n);
	b.resize(n);

	rep(i, n) cin >> a[i];
	rep(i, n){
		cin >> b[i];
		bst.insert(b[i]);
	}

	rep(i, n){
		int tmp=a[0]^b[i];
		int flag=1;
		multiset<int> st=bst;
		rep3(j, n, 1){
			auto itr=st.find(tmp^a[j]);
			if(itr==st.end()){
				flag=0;
				break;
			}
			st.erase(itr);
		}
		if(flag) ans.insert(tmp);
	}

	cout<< ans.size() <<endl;
	for(auto itr = ans.begin(); itr != ans.end(); ++itr) {
        std::cout << *itr << "\n";      // イテレータの指す先のデータを表示
    }
 
	return 0;
}