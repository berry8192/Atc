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
ll INF=9223372036854775807;
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

struct num{
	int a;
	int b;

	bool operator<(const num &in) const{
		return a<in.a;
	};
};

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

	int n, ma;
	vector<num> v;
	vector<int> c;

	cin>> n;
	v.resize(n);
	c.resize(n);

	rep(i, n) cin >> v[i].a;
	rep(i, n) cin >> v[i].b;
	sort(all(v));
	//rep(i, n) cout<< v[i].a SP << v[i].b <<endl;

	rep(i, n) {
		c[i]=v[i].b;
	}

	int ans = 0;
	ans=LIS(c);
	// cout<< ans <<endl;

	ma=ans;

	rep(i, n) swap(v[i].a, v[i].b);
	sort(all(v));

	rep(i, n) {
		c[i]=v[i].b;
	}

	// int flag=1;
	// rep(i, n){
	// 	if(v[i].a!=v[i].b){
	// 		flag=0;
	// 		break;
	// 	}
	// }
	// if(flag){
	// 	cout<< n*2 <<endl;
	// 	return 0;
	// }

	ans = 0;
	ans=LIS(c);
	// cout<< ans <<endl;

	ma=max(ma, ans+n);

	cout<< ma <<endl;
 
	return 0;
}