#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

//定数周り
int imax=2147483647;
ll lmax=9223372036854775807;
ll mod=1000000007;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

int main(){
    
	FILE* in = freopen("../testcases/in/hand-08.txt", "r", stdin);
	FILE* out = freopen("../testcases/out/hand-08.txt", "w", stdout);

    int N;
    vector<int> P;
    cin>> N;
    P.resize(N);
    rep(i, N) cin>> P[i];

    ll ans=1;
    rep(i, N){
        ans*=P[i];
        ans%=mod;
    }

    cout<< ans <<endl;

	return 0;
}