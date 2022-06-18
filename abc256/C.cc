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

	ll ans=0;
	vector<int> h(3), w(3);
	vector<vector<int>> bo(3);
	rep(i, 3) bo[i].resize(3);

	rep(i, 3) cin >> h[i];
	rep(i, 3) cin >> w[i];

	rep3(i, 30, 1){
		bo[0][0]=i;
		rep3(j, 30, 1){
			bo[0][1]=j;
			rep3(k, 30, 1){
				bo[1][0]=k;
				rep3(l, 30, 1){
					bo[1][1]=l;
					bo[0][2]=h[0]-i-j;
					bo[1][2]=h[1]-k-l;
					bo[2][0]=w[0]-i-k;
					bo[2][1]=w[1]-j-l;
					if(w[2]-bo[0][2]-bo[1][2]==h[2]-bo[2][0]-bo[2][1]){
						bo[2][2]=w[2]-bo[0][2]-bo[1][2];
					}
					int flag=1;
					rep(x, 3){
						rep(y, 3){
							if(bo[x][y]<=0){
								flag=0;
								break;
							}
						}
					}
					if(flag) ans++;
				}
			}
		}
	}

	cout<< ans << endl;
 
	return 0;
}