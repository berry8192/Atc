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

    int N;
    vector<ll> P, l, r;
    cin>> N;
    P.resize(N);
    l.resize(N+1);
    r.resize(N+1);
    rep(i, N) cin>> P[i];

    assert(1<=N && N<=100000);
    rep(i, N) assert(1<=P[i] && P[i]<=1000000000);

    l[0]=1;
    r[0]=1;

    rep(i, N){
        l[i+1]=l[i]*P[i];
        l[i+1]%=mod;
    }
    reverse(all(P));
    rep(i, N){
        r[i+1]=r[i]*P[i];
        r[i+1]%=mod;
    }
    reverse(all(P));
    // PV(l);
    // PV(r);

    ll ans=0;
    rep(i, N){
        ll cases=(l[i]*r[N-i-1])%mod;
        ll psum=(P[i]*(P[i]+1)/2LL)%mod;
        //cout<< l[i] SP << r[N-i] SP << psum <<endl;
        ans+=(cases*psum)%mod;
        ans%=mod;
    }

    cout<< ans <<endl;

	return 0;
}