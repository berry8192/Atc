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
ll lmax=9223372036854775807;
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

struct s_edge{
	int to;
	int from;
	int co;

	bool operator<(const s_edge &in) const{
		return co!=in.co ? co>in.co : to<in.to ? to<in.to : from<in.from;
	};
};

int main(){

	int n, a, b, c;
	ll ans=0;
	vector<int> d;
	vector<s_edge> v;

	cin>> n;
	d.resize(n);

	rep(i, n) cin>> d[i];

	rep(i, n-1){
	    cin >> a >> b >> c;

        s_edge tmps;
        tmps.from=a-1;
        tmps.to=b-1;
        tmps.co=c;
        v.push_back(tmps);
    }

    sort(all(v));

	rep(i, n-1) {
		if (v[i].co<0) break;
		if(d[v[i].from]>0 && d[v[i].to]>0){
			d[v[i].from]--;
			d[v[i].to]--;
			ans+=v[i].co;
		}
	}

	cout<< ans << endl;
 
	return 0;
}