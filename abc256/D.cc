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
	rep(i, 60) cout << pvv[i] SP;
	cout<< pvv[60] <<endl;
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
	vector<int> l, r, ims(200010), al, ar;

	cin>> n;
	l.resize(n);
	r.resize(n);

	rep(i, n) cin >> l[i] >> r[i];

	rep(i, n) {
		ims[l[i]]++;
		ims[r[i]]--;
	}
	rep3(i, 200005, 1){
		ims[i]+=ims[i-1];
	}

	int str=0;
	//PV(ims);
	rep(i, 200010){
		if(str){
			if(ims[i]==0){
				str=0;
				ar.push_back(i);
			}
		}else{
			if(ims[i]){
				str=1;
				al.push_back(i);
			}
		}
	}

	rep(i, al.size()) cout<< al[i] SP << ar[i] <<endl;
 
	return 0;
}