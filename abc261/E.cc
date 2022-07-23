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

	int n, c, ans=0;
	vector<vector<int>> v(32);
	vector<int> t, a;

	cin>> n >> c;
	rep(i, 32) v[i].resize(n+1);
	t.resize(n);
	a.resize(n);

	rep(i, n) cin >> t[i] >> a[i];

	rep(i, 31){
		//cout<< "i=" << i <<endl;
		v[i][0]=bool(c&(1<<i));
		//cout<< v[i][0] <<endl;
		int xr=0;
		int ke=-1, va;
		rep(j, n){
			//cout<< "j=" << j <<endl;
			if(t[j]==1 && !(a[j]&(1<<i))){
				// 0になる
				ke=j;
				va=0;
				xr=0;
			}else if(t[j]==2 && (a[j]&(1<<i))){
				// 1になる
				ke=j;
				va=1;
				xr=0;
			}else if(t[j]==3 && (a[j]&(1<<i))){
				xr++;
			}

			if(ke==-1){
				v[i][j+1]=v[i][j];
			}else{
				v[i][j+1]=va;
			}
			v[i][j+1]=(xr%2)^v[i][j+1];
			//cout<< v[i][j+1] <<endl;
		}
	}

	rep(i, n){
		ans=0;
		rep(j, 31){
			ans+=v[j][i+1]*(1<<j);
		}
		cout<< ans <<endl;
	}
 
	return 0;
}