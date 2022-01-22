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
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const long long INF = 1LL<<60;

// 最長増加部分列の長さを求める
int LIS(const vector<int> &a) {
    int N = (int)a.size();
    vector<long long> dp(N, INF);
    for (int i = 0; i < N; ++i) {
        // dp[k] >= a[i] となる最小のイテレータを見つける
        auto it = lower_bound(dp.begin(), dp.end(), a[i]);

        // そこを a[i] で書き換える
        *it = a[i];
    }

    // dp[k] < INF となる最大の k に対して k+1 が答え
    // それは dp[k] >= INF となる最小の k に一致する
    return lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
}

int main(){

	int n, x, mi;
	vector<int> p, q, qinv, lis, tmp;

	cin>> n;
	p.resize(n);
	q.resize(n);
	qinv.resize(n+1);
	//lis.resize(n);

	rep(i, n) cin >> p[i];
	rep(i, n){
		cin >> q[i];
		qinv[q[i]]=i;
	}

	rep(i, n) {
		x=p[i];
		//cout<< "x" SP << x <<endl;
		for(int j=x;j<=n;j+=x){
			//mi=min(mi, qinv[j]);
			tmp.push_back(qinv[j]);
			sort(all(tmp));
		}
		repr(i, tmp.size()) lis.push_back(tmp[i]);
	//PV(lis);
	}

	int N = (int)lis.size();
    vector<long long> dp(N, INF);
    for (int i = 0; i < N; ++i) {
        // dp[k] >= a[i] となる最小のイテレータを見つける
        auto it = lower_bound(dp.begin(), dp.end(), lis[i]);

        // そこを a[i] で書き換える
        *it = lis[i];
    }

    // dp[k] < INF となる最大の k に対して k+1 が答え
    // それは dp[k] >= INF となる最小の k に一致する
    cout<< lower_bound(dp.begin(), dp.end(), INF) - dp.begin() <<endl;
	return 0;
}