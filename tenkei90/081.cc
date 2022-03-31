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
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int n, k, a, b, ans=0;
	vector< vector<int> > bo;

	cin>> n >> k;
	bo.resize(5010);
	rep(i, 5010) bo[i].resize(5010);

	rep(i, n){
		cin >> a >> b;
		bo[a][b]++;
	}

	// 横方向への累積和 (図 4, 5)
	for (int y = 1; y < 5010; y++) {
		for (int x = 1; x < 5010; x++) {
			bo[y][x] += bo[y][x - 1];
		}
	}
	// 縦方向の累積和 (図 6, 7)
	for (int y = 1; y < 5010; y++) {
		for (int x = 1; x < 5010; x++) {
			bo[y][x] += bo[y - 1][x];
		}
	}

	rep3(i, 5001-k, 0) {
		rep3(j, 5001-k, 0){
			ans=max(ans, bo[i+k+1][j+k+1]+bo[i][j]-bo[i+k+1][j]-bo[i][j+k+1]);
		}
	}

	// rep(i, 10) {
	// 	rep(j, 10){
	// 		cout<< bo[i][j] <<" ";
	// 	}
	// 	cout<< endl;
	// }

	cout<< ans << endl;
 
	return 0;
}