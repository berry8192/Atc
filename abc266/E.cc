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

int main(){

	int n;
	double ans=0.0;
	vector<double> v(6, 1.0/6.0);

	cin>> n;

	rep(i, n-1) {
		vector<double> w(6);
		rep(j, 6){
			if(j==3 && i>=n-2){
				w[j]+=v[j];
				continue;
			}
			if(j==4 && i>=n-5){
				w[j]+=v[j];
				continue;
			}
			if(j==5){
				w[j]+=v[j];
				continue;
			}
			rep(k, 6){
				w[k]+=v[j]/6.0;
			}
		}
		rep(j, 6) v[j]=w[j];
		//PV(v);
	}

	rep(i, 6) ans+=(i+1)*v[i];

	printf("%.12lf\n", ans);
 
	return 0;
}