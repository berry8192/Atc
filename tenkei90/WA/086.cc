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

	int n, q, flag;
	LLi tmp, ans=1;
	vector<LLi> x, y, z, w;
	vector<vector<int>> v;

	cin>> n >> q;
	x.resize(q);
	y.resize(q);
	z.resize(q);
	w.resize(q);
	// v.resize(n);
	// rep(i, n) v[i].resize(60);

	rep(i, q) cin >> x[i] >> y[i] >> z[i] >> w[i];

	// 各ビット
	rep(i, 60){
		tmp=0;
		// ビット全探索
		for (int bit = 0; bit < (1<<n); ++bit) {
			// 各条件
			flag=1;
			rep(j, q){
				//全ての桁に対する処理
				for (int k = 0; k < n; ++k) {
					//探索対象となっているbitかどうかを判定
					if(bit & (1<<k)){
						if(!i && !j) cout<< 1;
						if(x[j]!=k+1 && y[j]!=k+1 && z[j]!=k+1){
							flag=0;
							//break;
						}
					}else{
						if(!i && !j) cout<< 0;
						if(x[j]==k+1 || y[j]==k+1 || z[j]==k+1){
							flag=0;
							//break;
						}
					}
				}
				//if(flag) break;
			}
			tmp++;
			if(!i) cout<< endl;
		}
		ans*=tmp;
		ans%=mod;
	}

	cout<< ans << endl;
 
	return 0;
}