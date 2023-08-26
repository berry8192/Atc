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

	int h, w, any=0, ans=0;
	cin>> h >> w;
	vector<vector<int>> a(h, vector<int>(w)), b(h, vector<int>(w));

	rep(i, h){
		rep(j, w){
			cin >> a[i][j];
		}
	}
	rep(i, h){
		rep(j, w){
			cin >> b[i][j];
			if(b[i][j]==-1) any++;
		}
	}
	if(any){
		cout<< "Yes" <<endl;
		return 0;
	}

	rep(bit, 31){
		rep(i, w){
			if((1<<bit)&(a[0][i]^b[0][i])){
				rep(j, h) a[j][i]=(1<<bit)^a[j][i];
			}
		}
		rep3(i, h, 1){
			if((1<<bit)&(a[i][0]^b[i][0])){
				rep(j, w) a[i][j]=(1<<bit)^a[i][j];
			}
		}
	}

	if(a==b) cout<< "Yes" <<endl;
	else cout<< "No" <<endl;
 
	return 0;
}