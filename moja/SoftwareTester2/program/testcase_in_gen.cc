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

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

int main(){
    FILE *in = freopen("../testcases/in/hand-08.txt", "w", stdout);

    // int seed=10000;
    auto seed=(unsigned)time(NULL);
    mt19937 mt(seed);

    int N;
    vector<int> P;
    N=mt()%3+1;
    // N=1;
    P.resize(N);
    rep(i, N) P[i]=mt()%1000000000+1;
    // rep(i, N) P[i]=1;

    cout<< N <<endl;
    PV(P);

	return 0;
}