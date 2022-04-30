#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
ll mod=1000000007;
//using mint = modint=998244353;

//Nは桁数が大きい場合があるので文字列として受け取る
string N;
ll D;
vector<int> n;  //Nの各桁の数字を格納するベクター
ll dp[10010][2][110];
ll ans=0;

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

//桁DP
int main(){
	cin>>N >> D;

	//ベクターnを構成
	for(auto a : N){
		n.push_back(a-'0');
	}
	int l = N.size();  //nの長さ

	dp[0][0][0] = 1;  //初期条件。他は0で初期化されている
	for(int i = 0; i < l; i++){
		for(int smaller = 0; smaller < 2; smaller++){
			for(int modD = 0; modD < D; modD++){
				int lim = (smaller ? 9 : n[i]);
				for(int x = 0; x <= lim; x++){
					int nSmaller = smaller || (x < lim);
        			if (smaller == 1 && nSmaller == 0) continue;
					dp[i+1][nSmaller][(modD + x) % D]+=dp[i][smaller][modD];
					dp[i+1][nSmaller][(modD + x) % D]%=mod;      
				}
			}
		}
	}

	ans=dp[l][0][0]+dp[l][1][0];

	cout << (ans-1+mod)%mod << endl;
 
	return 0;
}