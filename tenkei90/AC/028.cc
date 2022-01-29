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

	int n, a, b, c, d;
	vector<int> ans;
	vector< vector<int> > bo;

	cin>> n;
	bo.resize(1010);
	ans.resize(n+1);
	rep(i, 1010) bo[i].resize(1010);

	rep(i, n){
		cin >> a >> b >> c >> d;
		bo[a][d]--;
		bo[c][d]++;
		bo[a][b]++;
		bo[c][b]--;
	}
	for (int y = 0; y < 1010; y++) {
		for (int x = 1; x < 1010; x++) {
			bo[y][x] += bo[y][x - 1];
		}
	}
	// 縦方向の累積和 (図 6, 7)
	for (int y = 1; y < 1010; y++) {
		for (int x = 0; x < 1010; x++) {
			bo[y][x] += bo[y - 1][x];
		}
	}

	for(int i=0;i<=1000;i++){
		for(int j=0;j<=1000;j++){
			//cout<< bo[i][j] <<" ";
			//if(bo[i][j]>n) cout<< bo[i][j] <<endl;
			ans[bo[i][j]]++;
		}
		//cout<< endl;
	}

	for(int i=1;i<=n;i++) cout<< ans[i] <<endl;
 
	return 0;
}