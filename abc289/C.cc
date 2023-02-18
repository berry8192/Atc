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

	int n, m, ans=0, c, tmp;
	cin>> n >> m;
	vector<int> a(m);

	rep(i, m){
		cin>> c;
		rep(j, c){
			cin>> tmp;
			tmp--;
			a[i]+=(1<<tmp);
		}
	}
	// PV(a);
	// cout<< "#" << ((1<<n)-1) <<endl;
	
	for (int bit = 0; bit < (1<<m); ++bit) {
		tmp=0;
		//全ての桁に対する処理
        for (int i = 0; i < m; ++i) {
			//探索対象となっているbitかどうかを判定
            if(bit & (1<<i)) tmp=(tmp | a[i]);
        }
		//cout<< bit SP << tmp <<endl;
		if(tmp==(1<<n)-1){
			//第二引数は0のビットの個数
			ans++;
		}
    }

	cout<< ans << endl;
 
	return 0;
}