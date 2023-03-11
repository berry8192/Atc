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

int h, w;
int v[11][11];
int ans=0;

void dfs(int x, int y, vector<int> z){
	z.push_back(v[x][y]);
	if(x==h-1 && y==w-1){
		rep(i, z.size()){
			rep3(j, z.size(), i+1){
				if(z[i]==z[j]){
					return;
				}
			}
		}
		ans++;
		return;
	}
	if(x<h-1) dfs(x+1, y, z);
	if(y<w-1) dfs(x, y+1, z);
}

int main(){


	cin>> h >> w;

	rep(i, h){
		rep(j, w){
			cin >> v[i][j];
		}
	}

	vector<int> emp;
	dfs(0, 0, emp);

	cout<< ans << endl;
 
	return 0;
}