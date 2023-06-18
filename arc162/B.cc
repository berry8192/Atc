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

vector<int> v, ai, aj;

void swp(int ii, int jj){
	int a=v[ii];
	int b=v[ii+1];
	v.erase(v.begin()+ii, min(v.begin()+ii+2, v.end()));
	v.insert(v.begin()+jj, a);
	v.insert(v.begin()+jj+1, b);
	ai.push_back(ii+1);
	aj.push_back(jj);
}

int main(){

	int n, ans=0;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		v[i]--;
	}

	rep(i, n) {
		if(v[i]==i) continue;
		int idx;
		rep(j, n){
			if(v[j]==i){
				idx=j;
			}
		}
		if(idx==n-1){
			if(i==n-2){
				cout<< "No" <<endl;
				return 0;
			}else{
				swp(n-2, n-3);
			}
		}
		swp(idx, i);

		if(ai.size()>2000){
			cout<< "No" <<endl;
			return 0;
		}
		// PV(v);
	}

	cout<< "Yes" << endl;
	cout<< ai.size() <<endl;
	rep(i, ai.size()) cout<< ai[i] SP << aj[i] <<endl;
 
	return 0;
}