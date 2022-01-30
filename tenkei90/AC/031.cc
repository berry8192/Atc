#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, 10){
		rep(j, 10){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

// setでmexはよくない
// int mex(set<int> x){
// 	int ans=0;
// 	rep(i, x.size()+1){
// 		auto itr=x.find(i);
// 		if(itr==x.end()) return i;
// 	}
// }

int main(){

	int n;
	LLi ans=0;
	vector<int> w, b;
	vector< vector<int> > bo;
	// bo[i][j]=x 白i個、青j個のとき
	// x=1: 

	cin>> n;
	w.resize(n);
	b.resize(n);
	bo.resize(51);
	rep(i, 51) bo[i].resize(1500);

	rep(i, n) cin >> w[i];
	rep(i, n) cin >> b[i];

	bo[0][1]=0;

	// いい感じにgrundy数がつかえてる
	rep(i, 51) {
		rep(j, 1500){
			int lp=j/2;
			vector<int> tmp(1500);
			rep(k, lp){
				tmp[bo[i][j-k-1]]=1;
			}
			if(i && j+i<1500) tmp[bo[i-1][i+j]]=1;
			for(int k=0;k<1500;k++){
				if(!tmp[k]){
					bo[i][j]=k;
					break;
				}
			}
		}
	}

	//PVV(bo);

	rep(i, n){
		ans=ans^(bo[w[i]][b[i]]);
	}

	if(ans) cout<< "First" << endl;
	else cout<< "Second" << endl;
 
	return 0;
}