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

	int n, s, pos;
	string ans;
	vector<int> a, b;
	vector< vector<int> > dp;
	//ad i番の福袋をつかってる
	//ar 前のadのidx

	cin>> n >> s;
	a.resize(n);
	b.resize(n);
	dp.resize(n+1);
	rep(i, n+1) dp[i].resize(s+1);
	dp[0][0]=1;

	rep(i, n){
		cin >> a[i]>> b[i];
	}

	rep(i, n) {
		repr(j, s){
			if(dp[i][j]){
				if(j+a[i]<=s) dp[i+1][j+a[i]]=1;
				if(j+b[i]<=s) dp[i+1][j+b[i]]=1;
			}
		}
	}

	if(dp[n][s]==0){
		cout<< "Impossible" <<endl;
		return 0;
	}

	pos=s;
	repr(i, n){
		if(pos-a[i]>=0 && dp[i][pos-a[i]]){
			ans+="A";
			pos-=a[i];
		}else if(pos-b[i]>=0 && dp[i][pos-b[i]]){
			ans+="B";
			pos-=b[i];
		}else{
			cout<< "Impossible" <<endl;
			return 0;
		}
		//cout<< pos <<endl;
	}

	reverse(all(ans));
	cout<< ans << endl;
 
	return 0;
}