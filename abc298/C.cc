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

template <class T> void PS(T ps) {
    // cout<< "{";
	for(auto itr = ps.begin(); itr != ps.end(); ++itr) cout<< *itr SP;
	cout<<endl;
}

int main(){

	int n, q;
	vector<multiset<int>> mst(200010);
	vector<set<int>> st(200010);

	cin>> n >> q;

	rep(lp, q) {
		int type, i, j;
		cin>> type;
		if(type==1){
			cin>> i >> j;
			mst[j].insert(i);
			st[i].insert(j);
		}else if(type==2){
			cin>> i;
			PS(mst[i]);
		}else{
			cin>> i;
			PS(st[i]);
		}
	}
 
	return 0;
}