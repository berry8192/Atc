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

	int h, w, x=0, y=0;
	vector<string> g;

	cin>> h >> w;
	g.resize(h);

	rep(i, h) cin >> g[i];

	while(1){
		if(g[x][y]=='U'){
			if(x==0){
				break;
			}
			g[x][y]='x';
			x--;
		}else if(g[x][y]=='D'){
			if(x==h-1){
				break;
			}
			g[x][y]='x';
			x++;
		}else if(g[x][y]=='L'){
			if(y==0){
				break;
			}
			g[x][y]='x';
			y--;
		}else if(g[x][y]=='R'){
			if(y==w-1){
				break;
			}
			g[x][y]='x';
			y++;
		}else{
			cout<< -1 <<endl;
			return 0;
		}
	}

	cout<< x+1 SP << y+1 << endl;
 
	return 0;
}