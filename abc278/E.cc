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

	int H, W, N, h, w;
	set<int> st;
	cin>> H >> W >> N >> h >> w;
	vector<vector<int>> v(H, vector<int>(W));

	rep(i, H){
		rep(j, W){
			cin>> v[i][j];
			st.insert(v[i][j]);
		}
	}
	vector<vector<int>> ans(H-h+1, vector<int>(W-w+1, st.size()));
	// PVV(v);

	rep(i, N){
	// rep3(i, 5, 4){
		int flag=1;
		int sq[4]={-1, 500, 500, -1};
		rep(j, H){
			rep(k, W){
				if(v[j][k]==i+1){
					sq[0]=max(sq[0], k);
					sq[1]=min(sq[1], j);
					sq[2]=min(sq[2], k);
					sq[3]=max(sq[3], j);
					flag=0;
				}
			}
		}
		if(flag) continue;
		if(sq[3]-sq[1]+1>h) continue;
		if(sq[0]-sq[2]+1>w) continue;
		// rep(j, 4) cout<< sq[j] <<endl;
		int hh[2], ww[2];
		hh[0]=max(0, min(H-h, sq[3]-(h-1)));
		hh[1]=max(0, min(H-h, sq[1]));
		ww[0]=max(0, min(W-w, sq[0]-(w-1)));
		ww[1]=max(0, min(W-w, sq[2]));
		// cout<< hh[1] SP << hh[0] <<endl;
		// cout<< ww[1] SP << ww[0] <<endl;
		rep3(j, hh[1]+1, hh[0]){
			rep3(k, ww[1]+1, ww[0]){
				// cout<< j SP << k <<endl;
				ans[j][k]--;
			}
		}
	}

	PVV(ans);
 
	return 0;
}