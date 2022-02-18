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

//違法改造してる
vector<long long> LIS(const vector<int> &a) {
    int N = (int)a.size();
    vector<long long> dp(N, llimax), ans(N);
    for (int i = 0; i < N; ++i) {
        // dp[k] >= a[i] となる最小のイテレータを見つける
        auto it = lower_bound(dp.begin(), dp.end(), a[i]);

        // そこを a[i] で書き換える
        *it = a[i];
		ans[i]=lower_bound(dp.begin(), dp.end(), llimax) - dp.begin();
    }

    // dp[k] < INF となる最大の k に対して k+1 が答え
    // それは dp[k] >= INF となる最小の k に一致する
	return ans;
}

int main(){

	int n;
	LLi ans=0;
	vector<int> v;
	vector<long long> a, b;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];

	a=LIS(v);
	reverse(all(v));
	b=LIS(v);
	//PV(a);
	//PV(b);

	rep(i, n) ans=max(ans, a[i]+b[n-1-i]-1);
	cout<< ans <<endl;
 
	return 0;
}